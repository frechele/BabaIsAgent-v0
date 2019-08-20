import pygame
import sys
import pyBaba

game = pyBaba.Game(10, 10)
#test
from pyBaba import Game, ObjectType

game = Game(10, 10)

game.Put(2, 1).SetType(ObjectType.BABA).SetText(True)
game.Put(3, 1).SetType(ObjectType.IS)
game.Put(4, 1).SetType(ObjectType.YOU)

game.Put(2, 5).SetType(ObjectType.BABA).SetText(True)
game.Put(3, 5).SetType(ObjectType.IS)
game.Put(4, 5).SetType(ObjectType.YOU)

for i in range(10):
    game.Put(6, i).SetType(ObjectType.WALL)

game.Put(1, 6).SetType(ObjectType.BABA)

game.Put(7, 3).SetType(ObjectType.FLAG).SetText(True)
game.Put(9, 5).SetType(ObjectType.WIN)

game.Put(8, 6).SetType(ObjectType.FLAG)

#pyBaba.ObjectType.BABA
# init
pygame.init()
pygame.font.init()
FPS = 30
BLOCK_SIZE = 24

clock = pygame.time.Clock()

# SCREEN
Screen_size = (game.GetWidth() * BLOCK_SIZE, game.GetHeight() * BLOCK_SIZE)
Screen = pygame.display.set_mode((Screen_size[0], Screen_size[1]), pygame.FULLSCREEN)

# color
COLOR_BLACK = pygame.Color(0, 0, 0)
COLOR_WHITE = pygame.Color(255, 255, 255)

# image
# 그냥 노가다로 다 로드해놓자
obj_images = {pyBaba.ObjectType.BABA : 'BABA', pyBaba.ObjectType.FLAG: 'FLAG', pyBaba.ObjectType.WALL: 'WALL'}
text_images = {pyBaba.ObjectType.BABA : 'BABA', pyBaba.ObjectType.FLAG:  'FLAG', pyBaba.ObjectType.IS: 'IS',
               pyBaba.ObjectType.YOU:  'YOU', pyBaba.ObjectType.PUSH: 'PUSH', pyBaba.ObjectType.STOP: 'STOP',
               pyBaba.ObjectType.WALL: 'WALL', pyBaba.ObjectType.WIN: 'WIN'}
for j in obj_images:
    temp = []
    for i in pyBaba.Action.__members__:
        if i == "COUNT":
            continue
        temp.append(pygame.transform.scale(pygame.image.load('./sprite/{}/{}.png'.format(obj_images[j], i)),
                                           (BLOCK_SIZE, BLOCK_SIZE)))
    print(temp)
    obj_images[j] = temp
    print(obj_images[j])

for i in text_images:
    text_images[i] = pygame.transform.scale(pygame.image.load('./sprite/text/{}.png'.format(text_images[i])), (BLOCK_SIZE, BLOCK_SIZE))
    print(text_images[i])
print(obj_images)

def DrawObject(obj, x_position, y_position):
    if obj.IsText():
        obj_image = text_images[obj.GetType()]
    else:
        print(obj.GetType())
        obj_image = obj_images[obj.GetType()][int(game.GetNowAction())]

    obj_rect = obj_image.get_rect()
    obj_rect.topleft = (x_position * BLOCK_SIZE, y_position * BLOCK_SIZE)

    Screen.blit(obj_image, obj_rect)


def IsObject(x_position, y_position):
    object_list = game.At(x_position, y_position)
    for obj in object_list:
        DrawObject(obj, x_position, y_position)


def Check():
    for y_position in range(game.GetHeight()):
        for x_position in range(game.GetWidth()):
            IsObject(x_position, y_position)


while True:
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                pygame.quit()
                sys.exit()

    Screen.fill(COLOR_WHITE)

    Check()
    pygame.display.flip()

    clock.tick(FPS)