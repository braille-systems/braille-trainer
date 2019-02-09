import winsound
import threading

def playSoundByFilename(filename):
    if filename == '':
        return
    thread = threading.Thread(target = winsound.PlaySound, args = (filename, winsound.SND_FILENAME))
    thread.start()

def pronounce(letter):
    n = ord(letter) - ord('б') + 2
    if n == 34:
        n = 7
    elif n > 6:
        n += 1
    no = str(n)
    thread = threading.Thread(target = winsound.PlaySound, args = ('audio/{}.wav'.format(no), winsound.SND_FILENAME))
    thread.start()
#pronounce('а')
#pronounce('ё')
#playSoundByFilename('audio/lesson1v2/title.wav')
#print('a')
#pronounce('ж')
#print('b')
