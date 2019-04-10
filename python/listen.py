import os
import speech_recognition as sr
from pocketsphinx import LiveSpeech, get_model_path

def listen_symbol():
    """
    Recognizes letters spoken aloud.
    First tries to send reqest to Google;
    if offline, handles connection error and calls listen_by_sphinx
    (recognition with PocketSprinx works bad)
    :returns:
    a letter of russian (or not) alphabet - first letter of recognized word
    """
    rec = sr.Recognizer()
    microphone = sr.Microphone()
    with microphone as sourse:
        rec.adjust_for_ambient_noise(sourse)
        print('Say something! Google listening')
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
            res = rec.recognize_google(audio, language="ru_RU")
            res = res.lower()
            print("Google recognized successfully")
        except (sr.UnknownValueError, sr.RequestError):
            res = listen_sphinx()
            print(res)
            res = str(res)
        if (res == '') | (not len(res)):
            return res
        else:
            return res[0]


def listen_sphinx():
    """
    use only with listen()
    """
    model_path = get_model_path()

    speech = LiveSpeech(
        verbose=False,
        sampling_rate=16000,
        buffer_size=2048,
        no_search=False,
        full_utt=False,
        hmm=os.path.join(model_path, 'zero_ru.cd_cont_4000'),
        lm=False,
        jsgf=os.path.join(model_path, 'calc.jsgf'),
        dic=os.path.join(model_path, 'my_dict_out.dic')
    )

    print("Say something! Sphinx listening")
    for phrase in speech:
        return phrase



if __name__ == '__main__':
    while True:
        print(listen_symbol())
