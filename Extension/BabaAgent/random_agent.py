import environment
from pyBaba import RandomAgent

env = environment.BabaEnv10x10()

env.reset()

agent = RandomAgent()

current_reward = 0
step = 0
while not env.done:
    state, reward, done, _ = env.step(agent.GetAction(env.game))

    current_reward += reward
    step += 1

print(f'Reward: {current_reward} Step: {step}')
