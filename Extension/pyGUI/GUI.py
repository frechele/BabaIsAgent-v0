import pygame
import sys
import pyBaba

# test
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
obj_images = {pyBaba.ObjectType.BABA: 'BABA', pyBaba.ObjectType.FLAG: 'FLAG', pyBaba.ObjectType.WALL: 'WALL'}
text_images = {pyBaba.ObjectType.BABA: 'BABA', pyBaba.ObjectType.FLAG:  'FLAG', pyBaba.ObjectType.IS: 'IS',
               pyBaba.ObjectType.YOU:  'YOU', pyBaba.ObjectType.PUSH: 'PUSH', pyBaba.ObjectType.STOP: 'STOP',
               pyBaba.ObjectType.WALL: 'WALL', pyBaba.ObjectType.WIN: 'WIN'}
for j in obj_images:
    temp = []
    for i in pyBaba.Action.__members__:
        if i == "COUNT":
            continue
        temp.append(pygame.transform.scale(pygame.image.load('./sprite/{}/{}.png'.format(obj_images[j], i)),
                                           (BLOCK_SIZE, BLOCK_SIZE)))
    obj_images[j] = temp

for i in text_images:
    text_images[i] = pygame.transform.scale(pygame.image.load('./sprite/text/{}.png'.format(text_images[i])), (BLOCK_SIZE, BLOCK_SIZE))


# object class
class TempObjectClass(pygame.sprite.Sprite):
    def __init__(self, obj):
        pygame.sprite.Sprite.__init__(self)
        self.obj = obj
        if obj.IsText():
            self.image = text_images[self.obj.GetType()]
        else:
            self.image = obj_images[self.obj.GetType()][int(game.GetNowAction())]
        self.rect = self.image.get_rect()
        self.rect.topleft = (game.GetPositionByObject(self.obj)[0] * BLOCK_SIZE, game.GetPositionByObject(self.obj)[1] * BLOCK_SIZE)

    def update(self):
        if self.obj.IsDestroyed():
            self.kill()
        if self.obj.IsText():
            self.image = text_images[self.obj.GetType()]
        else:
            self.image = obj_images[self.obj.GetType()][int(game.GetNowAction())]
        self.rect.topleft = (game.GetPositionByObject(self.obj)[0] * BLOCK_SIZE, game.GetPositionByObject(self.obj)[1] * BLOCK_SIZE)


object_group = pygame.sprite.Group()

def IsObject(x_position, y_position):
    object_list = game.At(x_position, y_position)
    for obj in object_list:
        object_group.add(TempObjectClass(obj))

def Check():
    for y_position in range(game.GetHeight()):
        for x_position in range(game.GetWidth()):
            IsObject(x_position, y_position)
Check()
gameover =False

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

    # update
    object_group.update()
    if game.GetGameResult() == pyBaba.GameResult.WIN or game.GetGameResult() == pyBaba.GameResult.DEFEAT:
        gameover = True

    # draw
    Screen.fill(COLOR_BLACK)
    object_group.draw(Screen)
    pygame.display.flip()

    clock.tick(FPS)