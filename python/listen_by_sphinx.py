import os
from pocketsphinx import LiveSpeech, get_model_path


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
        print(listen_sphinx())
