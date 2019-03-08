import speech_recognition as sr


def listen_symbol():
    """
    Recognizes letters spoken aloud.
    """
    rec = sr.Recognizer()
    microphone = sr.Microphone()
    with microphone as sourse:
        rec.adjust_for_ambient_noise(sourse)
        print('Say something')
        audio = rec.listen(sourse, timeout=3, phrase_time_limit=2)
        print('Recognizing')
        try: #res = rec.recognize_sphinx(audio, language = ('model/zero_ru.cd_cont_4000','model/ru.lm','model/alf.dic') )
            res = rec.recognize_google(audio, language="ru_RU")
            res = res.lower()
        except sr.UnknownValueError:
            return ''
        if res == '':
            return res
        else:
            return res[0]


if __name__ == '__main__':
    while True:
        print(listen_symbol())
