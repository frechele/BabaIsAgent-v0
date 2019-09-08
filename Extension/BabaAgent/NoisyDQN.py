import math, random
import numpy as np

from environment import BabaEnv10x10
import pyBaba

import torch
from torch import nn, optim
import torch.nn.functional as F

from replay_buffer import PrioritizedReplayBuffer

from tensorboardX import SummaryWriter

device = "cuda" if torch.cuda.is_available() else "cpu"

env = BabaEnv10x10()

class NoisyLinear(nn.Module):
    def __init__(self, in_features, out_features, std_init=0.4):
        super(NoisyLinear, self).__init__()
        
        self.in_features  = in_features
        self.out_features = out_features
        self.std_init     = std_init
        
        self.weight_mu    = nn.Parameter(torch.FloatTensor(out_features, in_features))
        self.weight_sigma = nn.Parameter(torch.FloatTensor(out_features, in_features))
        self.register_buffer('weight_epsilon', torch.FloatTensor(out_features, in_features))
        
        self.bias_mu    = nn.Parameter(torch.FloatTensor(out_features))
        self.bias_sigma = nn.Parameter(torch.FloatTensor(out_features))
        self.register_buffer('bias_epsilon', torch.FloatTensor(out_features))
        
        self.reset_parameters()
        self.reset_noise()
    
    def forward(self, x):
        if self.training: 
            weight = self.weight_mu + self.weight_sigma.mul(Variable(self.weight_epsilon))
            bias   = self.bias_mu   + self.bias_sigma.mul(Variable(self.bias_epsilon))
        else:
            weight = self.weight_mu
            bias   = self.bias_mu
        
        return F.linear(x, weight, bias)
    
    def reset_parameters(self):
        mu_range = 1 / math.sqrt(self.weight_mu.size(1))
        
        self.weight_mu.data.uniform_(-mu_range, mu_range)
        self.weight_sigma.data.fill_(self.std_init / math.sqrt(self.weight_sigma.size(1)))
        
        self.bias_mu.data.uniform_(-mu_range, mu_range)
        self.bias_sigma.data.fill_(self.std_init / math.sqrt(self.bias_sigma.size(0)))
    
    def reset_noise(self):
        epsilon_in  = self._scale_noise(self.in_features)
        epsilon_out = self._scale_noise(self.out_features)
        
        self.weight_epsilon.copy_(epsilon_out.ger(epsilon_in))
        self.bias_epsilon.copy_(self._scale_noise(self.out_features))
    
    def _scale_noise(self, size):
        x = torch.randn(size)
        x = x.sign().mul(x.abs().sqrt())
        return x

class DQN(nn.Module):
    def __init__(self):
        super(DQN, self).__init__()

        self.conv1 = nn.Conv2d(pyBaba.Preprocess.TENSOR_DIM, 64, 3, padding=1, bias=False)
        self.bn1 = nn.BatchNorm2d(64)
        self.conv2 = nn.Conv2d(64, 64, 3, padding=1, bias=False)
        self.bn2 = nn.BatchNorm2d(64)
        self.conv3 = nn.Conv2d(64, 64, 3, padding=1, bias=False)
        self.bn3 = nn.BatchNorm2d(64)
        self.conv4 = nn.Conv2d(64, 1, 1, padding=0, bias=False)
        self.bn4 = nn.BatchNorm2d(1)

        self.fc1 = NoisyLinear(100, 64)
        self.fc2 = NoisyLinear(64, 5)

    def forward(self, x):
        x = F.relu(self.bn1(self.conv1(x)))
        x = F.relu(self.bn2(self.conv2(x)))
        x = F.relu(self.bn3(self.conv3(x)))
        x = F.relu(self.bn4(self.conv4(x)))

        x = x.view(-1, 100)
        x = F.relu(self.fc1(x))
        return self.fc2(x)

    def act(self, state):
        qValue = self.forward(state)

        return qValue.max(1)[1].data[0]

    def reset_noise(self):
        self.fc1.reset_noise()
        self.fc2.reset_noise()

net = DQN().to(device)
target_net = DQN().to(device)

opt = optim.Adam(net.parameters(), lr=1e-3)
buffer = PrioritizedReplayBuffer(10000, .6)

BATCH_SIZE = 256
BETA_START = 0.4
BETA_FRAMES = 1000
BETA_BY_FRAMES = lambda frameIdx: min(1.0, BETA_START + frameIdx * (1.0 - BETA_START) / BETA_FRAMES)
GAMMA = .99
TARGET_UPDATE = 10

def update_target():
    global target_net

    target_net.load_state_dict(net.state_dict())

def train(beta):
    state, action, reward, next_state, done, weights, indices = buffer.sample(BATCH_SIZE, beta)

    opt.zero_grad()

    state = torch.FloatTensor(state).to(device)
    next_state = torch.FloatTensor(next_state).to(device)
    action = torch.LongTensor(action).to(device)
    reward = torch.FloatTensor(reward).to(device)
    done = torch.FloatTensor(done).to(device)
    weights = torch.FloatTensor(weights).to(device)

    qValues = net(state)
    nextQValues = target_net(next_state)

    qValue = qValues.gather(1, action.unsqueeze(1)).squeeze(1)
    nextQValue = nextQValues.max(1)[0]
    expectedQValue = reward + .99 * nextQValue * (1 - done)

    loss = (qValue - expectedQValue.detach()).pow(2) * weights
    priors = loss + 1e-5
    loss = loss

    loss.backward()
    opt.step()

    buffer.update_priorities(indices, priors.data.cpu().numpy())
    net.reset_noise()
    target_net.reset_noise()

if __name__ == '__main__':
    writer = SummaryWriter()

    global_step = 0

    scores = []
    for e in range(10000):
        score = 0

        state = env.reset().reshape(1, -1, 10, 10)
        state = torch.tensor(state).to(device)

        step = 0
        while step < 1000:
            global_step += 1

            action = net.act(state)

            next_state, reward, done, _ = env.step(action)
            next_state = next_state.reshape(1, -1, 10, 10)
            next_state = torch.tensor(next_state).to(device)

            buffer.push(state, action, reward, next_state, done)

            score += reward
            state = next_state
            
            step += 1

            if len(buffer) > BATCH_SIZE:
                beta = BETA_BY_FRAMES(global_step)
                train(beta)

            if done:
                break

        writer.add_scalar('Reward', score, e)
        writer.add_scalar('Step', step, e)

        scores.append(score)

        print(f'Episode {e}: score: {score:.3f} time_step: {global_step} step: {step} epsilon: {EPSILON}')

        if np.mean(scores[-min(50, len(scores)):]) > 180:
            print('Solved!')
            torch.save(net.state_dict(), 'noisy_dqn_agent.bin')
            break

        if e % TARGET_UPDATE == 0:
            update_target()