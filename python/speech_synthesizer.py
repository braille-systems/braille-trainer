import pyttsx3

def text_to_speech(text):
    engine = pyttsx3.init()
    # Elena's voice
    ru_voice_id = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech\Voices\TokenEnums\RHVoice\Elena"
    engine.setProperty('voice', ru_voice_id)
    engine.say(text)
    engine.runAndWait()
