import pyttsx3
import os
import time
import datetime
import speech_recognition as sr
import random
import webbrowser
import sounddevice as sd

def command():
    r = sr.Recognizer()

    with sr.Microphone() as source:
        print('Говорите')
        r.pause_threshold = 1
        r.adjust_for_ambient_noise(source, duration=1)
        audio = r.listen(source)

    try:
        task = r.recognize_google(audio, language="ru_RU").lower()
        print("Вы сказали " + task)
    except:
        task = command()

    return task

def makeSomething(task):
    print(task)
    if "сайт" in task:
        print("hello")
    elif "питон" in task:
        print("Python <3")
    else:
        print("Скукота")

while True:
    makeSomething(command())