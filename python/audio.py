import winsound
import threading


def playSoundByFilename(filename):
    """
    plays .wav file on Windows
    """
    if filename == '':
        return
    winsound.PlaySound(filename, winsound.SND_FILENAME)


def pronounce(letter):
    """
    plays the letter of Russian alphabet aloud
    (assuming 33 letters from 'а' to 'я')
    using .wav files from 'audio' folder
    """
    n = ord(letter) - ord('б') + 2
    if n == 34:
        n = 7
    elif n > 6:
        n += 1
    no = str(n)
    playSoundByFilename('audio/{}.wav'.format(no))

#pronounce('а')
#pronounce('ё')
#playSoundByFilename('audio/lesson1v2/title.wav')
#print('a')
#pronounce('ж')
#print('b')
