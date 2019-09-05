import pyBaba
import pygame
import gamedata

BLOCK_SIZE = gamedata.BLOCK_SIZE
screen_size = gamedata.Screen_size


class ImageLoader:
    def __init__(self):
        self.obj_images = {pyBaba.ObjectType.BABA: 'BABA', pyBaba.ObjectType.FLAG: 'FLAG', pyBaba.ObjectType.WALL: 'WALL'}
        for j in self.obj_images:
            temp = []
            for i in pyBaba.Direction.__members__:
                temp.append(pygame.transform.scale(pygame.image.load('./sprite/{}/{}.png'.format(self.obj_images[j], i)),
                                                   (BLOCK_SIZE, BLOCK_SIZE)))
            self.obj_images[j] = temp

        self.text_images = {pyBaba.ObjectType.BABA: 'BABA', pyBaba.ObjectType.FLAG:  'FLAG', pyBaba.ObjectType.IS: 'IS',
                       pyBaba.ObjectType.YOU:  'YOU', pyBaba.ObjectType.PUSH: 'PUSH', pyBaba.ObjectType.STOP: 'STOP',
                       pyBaba.ObjectType.WALL: 'WALL', pyBaba.ObjectType.WIN: 'WIN'}
        for i in self.text_images:
            self.text_images[i] = pygame.transform.scale(pygame.image.load('./sprite/text/{}.png'.format(self.text_images[i])),
                                                         (BLOCK_SIZE, BLOCK_SIZE))

imageLoader = ImageLoader()


class clearImage(pygame.sprite.Sprite):
    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.transform.scale(pygame.image.load('./sprite/clear.png'), (screen_size[0]//2, screen_size[1]//4))
        self.rect = self.image.get_rect()
        self.rect.center = (screen_size[0]//2, screen_size[1]//2)
    def update(self, status):
        if status == pyBaba.GameResult.DEFEAT:
            self.image = pygame.transform.scale(pygame.image.load('./sprite/defeat.png'), (screen_size[0]//2, screen_size[1]//4))

ClearImage = clearImage()
clearImage_Group = pygame.sprite.Group()
clearImage_Group.add(ClearImage)
