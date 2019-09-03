import pyBaba

game = pyBaba.Game(10, 10)

def setGame(game_):
    game_.Put(2, 1).SetType(pyBaba.ObjectType.BABA).SetText(True)
    game_.Put(3, 1).SetType(pyBaba.ObjectType.IS)
    game_.Put(4, 1).SetType(pyBaba.ObjectType.YOU)

    game_.Put(1, 4).SetType(pyBaba.ObjectType.BABA)

    game_.Put(7, 5).SetType(pyBaba.ObjectType.FLAG).SetText(True)
    game_.Put(7, 6).SetType(pyBaba.ObjectType.IS)
    game_.Put(7, 7).SetType(pyBaba.ObjectType.WIN)

    game_.Put(8, 6).SetType(pyBaba.ObjectType.FLAG)