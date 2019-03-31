import os
import speech_recognition as sr
from pocketsphinx import LiveSpeech, get_model_path

def listen_symbol():
    """
    Recognizes letters spoken aloud.
    """
    rec = sr.Recognizer()
    microphone = sr.Microphone()
    with microphone as sourse:
        rec.adjust_for_ambient_noise(sourse)
        print('Say something')
        logic_flag = True
        while logic_flag:
            try:
                audio = rec.listen(sourse, timeout=3, phrase_time_limit=2)
            except sr.WaitTimeoutError:
                print("Please, say")
            else:
                logic_flag = False
        print('Recognizing')
        try:
            #res = rec.recognize_sphinx(audio, language = ('model/zero_ru.cd_cont_4000','model/ru.lm','model/alf.dic') )
            res = rec.recognize_google(audio, language="ru_RU")
            res = res.lower()
        except (sr.UnknownValueError, sr.RequestError):
            return listen_sphinx()
        if res == '':
            return res
        else:
            return res[0]


def listen_sphinx():
    model_path = get_model_path()

    speech = LiveSpeech(
        verbose=False,
        sampling_rate=8000,
        buffer_size=2048,
        no_search=False,
        full_utt=False,
        hmm=os.path.join(model_path, 'zero_ru.cd_cont_4000'),
        lm=os.path.join(model_path, 'ru.lm'),
        dic=os.path.join(model_path, 'my_dict_out.dic')
    )

    print("Say something!")
    for phrase in speech:
        return phrase



if __name__ == '__main__':
    while True:
        print(listen_symbol())
