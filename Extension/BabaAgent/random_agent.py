import gym
import environment
from random import choice

env = gym.make('baba-10x10-v0')

env.reset()

current_reward = 0
step = 0
while not env.done:
    state, reward, done, _ = env.step(choice(env.action_space))

    current_reward += reward
    step += 1

print(f'Reward: {current_reward} Step: {step}')
