import gym
from gym.utils import seeding
from gym.envs.registration import register
import numpy as np

import pyBaba

class BabaEnv(gym.Env):
    metadata = { 'render.modes' : ['human'] }

    def __init__(self, width, height):
        super(BabaEnv, self).__init__()

        self.width = width
        self.height = height

        self.action_space = [
            pyBaba.Action.UP,
            pyBaba.Action.DOWN,
            pyBaba.Action.LEFT,
            pyBaba.Action.RIGHT,
            pyBaba.Action.STAY
        ]
        self.action_size = len(self.action_space)

        self.seed()

    def seed(self, seed=None):
        self.np_random, seed = seeding.np_random(seed)

        return [seed]

    def reset(self):
        self.game = pyBaba.Game(self.width, self.height)
        self.done = False

        self.game.Put(2, 1).SetType(pyBaba.ObjectType.BABA).SetText(True)
        self.game.Put(3, 1).SetType(pyBaba.ObjectType.IS)
        self.game.Put(4, 1).SetType(pyBaba.ObjectType.YOU)

        self.game.Put(2, 5).SetType(pyBaba.ObjectType.BABA).SetText(True)
        self.game.Put(3, 5).SetType(pyBaba.ObjectType.IS)
        self.game.Put(4, 5).SetType(pyBaba.ObjectType.YOU)

        for i in range(10):
            self.game.Put(6, i).SetType(pyBaba.ObjectType.WALL)

        self.game.Put(1, 6).SetType(pyBaba.ObjectType.BABA)

        self.game.Put(7, 3).SetType(pyBaba.ObjectType.FLAG).SetText(True)
        self.game.Put(9, 5).SetType(pyBaba.ObjectType.WIN)

        self.game.Put(8, 6).SetType(pyBaba.ObjectType.FLAG)

        return self._get_obs()

    def step(self, action):
        self.game.Update(action)

        result = self.game.GetGameResult()

        if result == pyBaba.GameResult.DEFEAT:
            self.done = True
            reward = -100
        elif result == pyBaba.GameResult.WIN:
            self.done = True
            reward = 200
        else:
            reward = -0.1

        return self._get_obs(), reward, self.done, {}

    def render(self, mode='human', close=False):
        pass

    def _get_obs(self):
        return np.array(
            pyBaba.Preprocess.StateToTensor(self.game)
            ).reshape(-1, self.height, self.width)

class BabaEnv10x10(BabaEnv):
    def __init__(self):
        super(BabaEnv10x10, self).__init__(10, 10)

register(
    id='baba-10x10-v0',
    entry_point='environment:BabaEnv10x10',
    max_episode_steps=1000,
    nondeterministic=True
)