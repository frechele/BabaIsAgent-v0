import pygame
import sys
import pyBaba
import gamemaker
import images
import gamedata

# testgame
game = gamemaker.game
gamemaker.setGame(game)

# init
pygame.init()
pygame.font.init()
FPS = gamedata.FPS
BLOCK_SIZE = gamedata.BLOCK_SIZE

clock = pygame.time.Clock()

# AI actions
action_dic = {"Action.RIGHT": pyBaba.Action.RIGHT, "Action.LEFT": pyBaba.Action.LEFT,
              "Action.UP": pyBaba.Action.UP, "Action.DOWN": pyBaba.Action.DOWN}
f = open("./AI_actions.txt", 'r')
actions = f.read().splitlines()
f.close()

# screen
Screen_size = gamedata.Screen_size
Screen = gamedata.Screen


# color
COLOR_BLACK = gamedata.COLOR_BLACK
COLOR_WHITE = gamedata.COLOR_WHITE
COLOR_BACKGROUND = gamedata.COLOR_BACKGROUND


# image
obj_images = images.imageLoader.obj_images
text_images = images.imageLoader.text_images


def IsObject(x_position, y_position):
    object_list = game.At(x_position, y_position)
    for obj in object_list:
        if obj.IsText():
            obj_image = text_images[obj.GetType()]
        else:
            obj_image = obj_images[obj.GetType()][int(obj.GetDirection())]
        obj_rect = obj_image.get_rect()
        obj_rect.topleft = (game.GetPositionByObject(obj)[0] * BLOCK_SIZE,
                            game.GetPositionByObject(obj)[1] * BLOCK_SIZE)
        Screen.blit(obj_image, obj_rect)


def Check():
    for y_position in range(game.GetHeight()):
        for x_position in range(game.GetWidth()):
            IsObject(x_position, y_position)

# loop
gameover = False
timer = 0
pygame.time.set_timer(pygame.USEREVENT, 200)
while True:
    if gameover:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.quit()
                    sys.exit()
        if game.GetGameResult() == pyBaba.GameResult.DEFEAT:
            images.clearImage_Group.update(pyBaba.GameResult.DEFEAT)
            images.clearImage_Group.draw(Screen)
        else:
            images.clearImage_Group.draw(Screen)
        pygame.display.flip()
        continue

    for event in pygame.event.get():
        if event.type == pygame.USEREVENT:
            game.Update(action_dic[actions[timer]])
            timer += 1
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                pygame.quit()
                sys.exit()

    # WIN
    if game.GetGameResult() == pyBaba.GameResult.WIN or game.GetGameResult() == pyBaba.GameResult.DEFEAT:
        gameover = True

    # draw
    Screen.fill(COLOR_BACKGROUND)
    Check()
    pygame.display.flip()

    clock.tick(FPS)
