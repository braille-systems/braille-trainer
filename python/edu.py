# -*- coding: cp1251 -*-
class Menu(list):
    """
    Main menu class
    """
    pass


class TestStep(object):
    """
    Test step class
    """

    def __init__(self, audio, bLine, comment=' '):
        """
        Constructor
        """
        self.audio = audio
        self.bLine = bLine
        self.__isRight = False
        self.comment = comment

    def __str__(self):
        if self.__isRight:
            res = 'correct'
        else:
            res = 'wrong'
        return self.audio + ' - ' + self.bLine + ' ' + '(' + res + ')' + '[' + self.comment + ']'

    def __repr__(self):
        return self.__str__()

    def setRight(self):
        self.__isRight = True

    def isRight():
        return self.__isRight


class LessonStep(object):
    """Lesson step class"""

    def __init__(self, audio, bLine, comment=' '):
        """Constructor"""
        self.comment = comment
        self.audio = audio
        self.bLine = bLine

    def __str__(self):
        return self.audio + ' - ' + self.bLine + ' ' + '[' + self.comment + ']'

    def __repr__(self):
        return self.__str__()


class Unit(list):
    """Unit class"""

    def __init__(self, name="Unknown", utype='unit', title=''):
        self.utype = utype
        self.title = title
        self.name = name

    def parseFrom(filename):
        """Parse Unit from file"""
        return

    def getResult(self):
        n = 0
        r = 0
        for stp in self:
            if isinstance(stp, TestStep):
                n = n + 1
                if (stp.isRight()):
                    r = r + 1
        return r / n

    def isLesson(self):
        return self.utype == 'lesson'

    def isTest(self):
        return self.utype == 'test'

    def __str__(self):
        return self.utype + ' ' + self.name + '[' + self.title + ']'

    def __repr__(self):
        return self.__str__() + ' ' + super(Unit, self).__repr__()
