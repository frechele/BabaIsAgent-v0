import pygame
import gamemaker

FPS = 30
BLOCK_SIZE = 24

# screen
Screen_size = (gamemaker.game.GetWidth() * BLOCK_SIZE, gamemaker.game.GetHeight() * BLOCK_SIZE)
Screen = pygame.display.set_mode((Screen_size[0], Screen_size[1]), pygame.FULLSCREEN)


# color
COLOR_BLACK = pygame.Color(0, 0, 0)
COLOR_WHITE = pygame.Color(255, 255, 255)
COLOR_BACKGROUND = pygame.Color(177, 216, 216)
