from threading import Thread
import pyttsx3
import time
engine = None
thread = None

class Threader(Thread):
    def __init__(self, *args, **kwargs):
        Thread.__init__(self, *args, **kwargs)
        self.daemon = True
        self.start()

    def terminate(self):
        print("stop engine")
        global engine
        if engine != None:
            engine.stop()
        self._running = False;

    def run(self):
        global engine
        if engine == None:
            f = open('settings.ini', 'r')
            audiospeed = int(f.read(1))
            f.close()
            tts_engine = pyttsx3.init()
            # Elena's voice
            ru_voice_id = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech\Voices\TokenEnums\RHVoice\Elena"
            ru_voice_id = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech\Voices\TokenEnums\RHVoice\Irina"
            tts_engine.setProperty('voice', ru_voice_id)
            tts_engine.setProperty('rate', audiospeed*20+100)
            tts_engine.say(self._args)
            engine = tts_engine
            tts_engine.runAndWait()
            engine = None

#text_to_speech("а б в г д е ё ж з и й к л м н о п р с т у ф х ц ч")
  
def text_to_speech(text):
    if text == '.':
        text = 'точка'
    if text in '()':
        text = 'скобка'
    if text == '-':
        text = 'тире'
    if text == '!':
        text = 'восклицательный знак'
    if text == '?':
        text = 'вопросительный знак'
    if text == ':':
        text = 'двоеточие'
    global thread
    if thread != None:
        thread.terminate()
        time.sleep(0.15)
    my_thread = Threader(args=text)
    thread = my_thread
    
"""

def text_to_speech(text):
    engine = pyttsx3.init()
    # Elena's voice
    ru_voice_id = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech\Voices\TokenEnums\RHVoice\Elena"
    ru_voice_id = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech\Voices\TokenEnums\RHVoice\Irina"
    engine.setProperty('voice', ru_voice_id)
    engine.say(text)
    engine.runAndWait()
"""
