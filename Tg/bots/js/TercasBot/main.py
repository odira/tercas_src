#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Mar  6 22:03:38 2019

@author: mac
"""

import telebot
bot = telebot.TeleBot('408773131:AAHp4zD_P6IhObQi0JdNR5xfOAERc8hNEgA')

@bot.message_handler(content_types=['text'])
def get_text_messages(message):
    if message.text == "Привет":
        bot.send_message(message.from_user.id, "Привет, чем могу тебе помочь?")
        
bot.polling(none_stop=True, interval=0)