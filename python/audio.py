import winsound
import threading

def playSoundByFilename(filename):
    if filename == '':
        return
    winsound.PlaySound(filename, winsound.SND_FILENAME)

def pronounce(letter):
    n = ord(letter) - ord('б') + 2
    if n == 34:
        n = 7
    elif n > 6:
        n += 1
    no = str(n)
    winsound.PlaySound('audio/{}.wav'.format(no), winsound.SND_FILENAME)
#pronounce('а')
#pronounce('ё')
#playSoundByFilename('audio/lesson1v2/title.wav')
#print('a')
#pronounce('ж')
#print('b')
