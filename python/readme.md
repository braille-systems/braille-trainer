Для работы распознования аудио понадобится:
1. ``pip install pyaudio``
1. ``pip install speechrecognition``
1. ``pip install pocketsphinx``

Для установки pocketsphinx потребуется установленный swig:
инструкция: http://www.swig.org/download.html

Для работы с Serial используется библиотека pySerial<br>
https://github.com/pyserial/pyserial
https://pythonhosted.org/pyserial/
Для установки ``pip install pyserial``

Для работы listen необходимо добавить в папку python'a:
~\Lib\site-packages\pocketsphinx\model
файлы: (содержимое папки "everything to working pocketsphinx")
ru.Im
my_dicy_out.dic
всю папку zero_ru.cd_cont_4000


Эталонные версии пакетов, с которыми проверена работа:
1. Python 3.7.2
1. PyAudion 0.2.11
1. PyQt5 5.12
1. PyQt5-sip 4.19.14
1. pyserial 3.4
1. SpeechRecognition 3.8.1
1. pocketsphinx 0.1.15

**alphabet.py** - приложение - азбука<br>
**audio.py** отвечает за проигрывание буквы в .wav из папки 
"audio" и вывод остальных фраз; только для Windows<br>
**clock.py** - приложение - часы<br>**
**edu.py, edu_app.py** - обучающее приложение<br>
**joystick.py** - обработка нажатий джойстика, 
пришедших по Serial<br>
**letter.py** - вывод буквы на экран в PyQT5<br>
**listen.py** - распознавание произнесённой буквы 
(вариант с сервисом google, если не получается, вызывает pocketsphinx распознование)<br>
**main.py** - **запуск всего (меню 
приложений)**<br>
**notes.py** - приложение - заметки (в 
разработке)<br>
**serial_get_name.py** - автоопределение 
COM-порта, к которому подключён тренажёр<br>
**serial_hex.py** выводит строку (алфавит) в Serial. Соответствует скетчу print_letters в 
папке arduino. Также проигрывает буквы вслух (только на Windows) <br>
**ui_letter.py** - наполнение (дизайн) для 
вывода буквы на экран средствами PyQT5. Логика 
в letter.py<br>

**alphabet.py** - приложение - азбука<br> **audio.py** отвечает за 
проигрывание буквы в .wav из папки "audio" и вывод остальных фраз; 
только для Windows<br> **clock.py** - приложение - часы<br>** **edu.py, 
edu_app.py** - обучающее приложение<br> **joystick.py** - обработка 
нажатий джойстика, пришедших по Serial<br> **letter.py** - вывод буквы 
на экран в PyQT5<br> **listen.py** - распознавание произнесённой буквы 
(вариант с сервисом google)<br> **main.py** - **запуск всего (меню 
приложений)**<br> **notes.py** - приложение - заметки (в разработке)<br> 
**serial_get_name.py** - автоопределение COM-порта, к которому подключён 
тренажёр<br> **serial_hex.py** выводит строку (алфавит) в Serial. 
Соответствует скетчу print_letters в папке arduino. Также проигрывает 
буквы вслух (только на Windows) <br> **ui_letter.py** - наполнение 
(дизайн) для вывода буквы на экран средствами PyQT5. Логика в 
letter.py<br>

Ссылка на описание аудифайлов
https://docs.google.com/spreadsheets/d/1J9BtCmSqfUPkXovssfOHMlftX5HE0grbqLEqsHJY1Zc/edit#gid=0
