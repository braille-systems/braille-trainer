import speech_recognition as sr
import requests as rq


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
        try:
            res = recognise_by_yandex(audio)
            res = res.lower()
        except sr.UnknownValueError:
            return ''
        if res == '':
            return res
        else:
            return res[0]


def getting_iam_by_request():
    try:
        oauth_token = "AQAAAAAQP_ACAATuwa1VkYFaGU8ds_s4BP3rwjI"
        tmp_d = """{"yandexPassportOauthToken":"AQAAAAAQP_ACAATuwa1VkYFaGU8ds_s4BP3rwjI"}"""
        # response = rq.get('https://iam.api.cloud.yandex.net/iam/v1/tokens', auth=("yandexPassportOauthToken", oauth_token), headers={"Content-Type": "application/json"})
        response = rq.get("https://iam.api.cloud.yandex.net/iam/v1/tokens", data=tmp_d, headers={"Content-Type": "application/json"})
        print(response.status_code)
        print(response.content)
    except rq.RequestException:
        print('can not get response')


if __name__ == '__main__':
    getting_iam_by_request()
