import pygame
import sys
import pyBaba

# testgame
from pyBaba import Game, ObjectType

game = Game(10, 10)

game.Put(2, 1).SetType(ObjectType.BABA).SetText(True)
game.Put(3, 1).SetType(ObjectType.IS)
game.Put(5, 1).SetType(ObjectType.IS)
game.Put(4, 1).SetType(ObjectType.YOU)

game.Put(2, 5).SetType(ObjectType.BABA).SetText(True)
game.Put(3, 5).SetType(ObjectType.IS)
game.Put(4, 5).SetType(ObjectType.YOU)

for i in range(10):
    game.Put(6, i).SetType(ObjectType.WALL)

game.Put(1, 6).SetType(ObjectType.BABA)

game.Put(7, 3).SetType(ObjectType.FLAG).SetText(True)
game.Put(6, 3).SetType(ObjectType.WALL).SetText(True)
game.Put(9, 5).SetType(ObjectType.WIN)

game.Put(8, 6).SetType(ObjectType.FLAG)

# init
pygame.init()
pygame.font.init()
FPS = 30
BLOCK_SIZE = 24

clock = pygame.time.Clock()

# screen
Screen_size = (game.GetWidth() * BLOCK_SIZE, game.GetHeight() * BLOCK_SIZE)
Screen = pygame.display.set_mode((Screen_size[0], Screen_size[1]), pygame.FULLSCREEN)

# color
COLOR_BLACK = pygame.Color(0, 0, 0)
COLOR_WHITE = pygame.Color(255, 255, 255)
COLOR_BACKGROUND = pygame.Color(177, 216, 216)

# image
# 그냥 노가다로 다 로드해놓자
obj_images = {pyBaba.ObjectType.BABA: 'BABA', pyBaba.ObjectType.FLAG: 'FLAG', pyBaba.ObjectType.WALL: 'WALL'}
text_images = {pyBaba.ObjectType.BABA: 'BABA', pyBaba.ObjectType.FLAG:  'FLAG', pyBaba.ObjectType.IS: 'IS',
               pyBaba.ObjectType.YOU:  'YOU', pyBaba.ObjectType.PUSH: 'PUSH', pyBaba.ObjectType.STOP: 'STOP',
               pyBaba.ObjectType.WALL: 'WALL', pyBaba.ObjectType.WIN: 'WIN'}
for j in obj_images:
    temp = []
    for i in pyBaba.Direction.__members__:
        temp.append(pygame.transform.scale(pygame.image.load('./sprite/{}/{}.png'.format(obj_images[j], i)),
                                           (BLOCK_SIZE, BLOCK_SIZE)))
    obj_images[j] = temp

for i in text_images:
    text_images[i] = pygame.transform.scale(pygame.image.load('./sprite/text/{}.png'.format(text_images[i])), (BLOCK_SIZE, BLOCK_SIZE))


def IsObject(x_position, y_position):
    object_list = game.At(x_position, y_position)
    for obj in object_list:
        if obj.IsText():
            obj_image = text_images[obj.GetType()]
        else:
            obj_image = obj_images[obj.GetType()][int(obj.GetDirection())]
        obj_rect = obj_image.get_rect()
        obj_rect.topleft = (
        game.GetPositionByObject(obj)[0] * BLOCK_SIZE, game.GetPositionByObject(obj)[1] * BLOCK_SIZE)
        Screen.blit(obj_image, obj_rect)

def Check():
    for y_position in range(game.GetHeight()):
        for x_position in range(game.GetWidth()):
            print(x_position, y_position)
            IsObject(x_position, y_position)

# loop
gameover = False
while True:
    if gameover:
        pygame.quit()
        sys.exit()

    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                pygame.quit()
                sys.exit()
            if event.key == pygame.K_SPACE:
                game.Update(pyBaba.Action.STAY)
            if event.key == pygame.K_UP:
                game.Update(pyBaba.Action.UP)
            if event.key == pygame.K_DOWN:
                game.Update(pyBaba.Action.DOWN)
            if event.key == pygame.K_RIGHT:
                game.Update(pyBaba.Action.RIGHT)
            if event.key == pygame.K_LEFT:
                game.Update(pyBaba.Action.LEFT)

    # WIN
    if game.GetGameResult() == pyBaba.GameResult.WIN:
        gameover = True

    # draw
    Screen.fill(COLOR_BACKGROUND)
    Check()
    pygame.display.flip()

    clock.tick(FPS)