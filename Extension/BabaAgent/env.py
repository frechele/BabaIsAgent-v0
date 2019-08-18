import gym
from gym.envs.registration import register

import pyBaba

class BabaEnv(gym.Env):
    metadata = { 'render.modes' : ['human'] }

    def __init__(self, width, height):
        super(BabaEnv, self).__init__()

        self.width = width
        self.height = height

    def _reset(self):
        self.game = pyBaba.Game(self.width, self.height)
        self.done = False

        return self._get_obs()

    def _step(self, action):
        reward = 0

        return self._get_obs(), reward, self.done

    def _render(self, mode='human', close=False):
        pass

    def _get_obs(self):
        return None

register(
    id='baba-20x20-v0',
    entry_point='BabaEnv',
    max_episode_steps=1000,
    nondeterministic=True
)