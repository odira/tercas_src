import telebot
import re
from telebot import types

from config import token

bot = telebot.TeleBot(token)

digits_pattern = re.compile(r'^[0-9]+ [0-9]+$', re.MULTILINE)

plus_icon = "https://pp.vk.me/c627626/v627626512/2a627/7d1h4RRh24.jpg"
minus_icon = "https://pp.vk.me/c627626/v627626512/2a635/ILYe7N2n8Zo.jpg"
divide_icon = "https://pp.vk.me/c627626/v627626512/2a620/oAvUk7Awps0.jpg"
multiply_icon = "https://pp.vk.me/c627626/v627626512/2a62e/xqnPMigaP5c.jpg"
error_icon = "https://pp.vk.me/c627626/v627626512/2a67a/ZvTeGq6Mf88.jpg"

@bot.inline_handler(func=lambda query: len(query.query) > 0)
def query_text(query):

	try:
		matches = re.match(digits_pattern, query.query)
	except AttributeError as ex:
		return
	
	num1, num2 = matches.group().split()
	try:
		m_sum = int(num1) + int(num2)
		r_sum = types.InlineQueryResultArticle(
			id='1',
			title="Сумма",
			description="Результат: {!s}".format(m_sum),
			input_message_content=types.InputTextMessageContent(
				message_text="{!s} + {!s} = {!s}".format(num1, num2, m_sum)
			),
			thumb_url=plus_icon, thumb_width=48, thumb_height=48
		)
	
		m_sub = int(num1) - int(num2)
		r_sub = types.InlineQueryResultArticle(
			id='2',
			title="Разность",
			description="Результат: {!s}".format(m_sub),
			input_message_content=types.InputTextMessageContent(
				message_text="{!s} - {!s} = {!s}".format(num1, num2, m_sub)
			),
			thumb_url=minus_icon, thumb_width=48, thumb_height=48
		)
	
		if num2 != 0:
			m_div = int(num1) / int(num2)
			r_div = types.InlineQueryResultArticle(
				id='3',
				title="Частное",
				description="Результат: {0:.2f}".format(m_div),
				input_message_content=types.InputTextMessageContent(
					message_text="{0!s} / {1!s} = {2:.2f}".format(num1, num2, m_div)
				),
				thumb_url=divide_icon, thumb_width=48, thumb_height=48
			)
		else:
			r_div = types.InlineQueryResultArticle(
				id='3',
				title="Частное",
				description="На ноль делить нельзя!",
				input_message_content=types.InputTextMessageContent(
					message_text="Я нехороший человек и делю на ноль!"
				),
				thumb_url=error_icon, thumb_width=48, thumb_height=48,
				url="https://ru.wikipedia.org/wiki/error",
				disable_web_page_preview=True,
				hide_url=True
			)
	
		m_mul = int(num1) * int(num2)
		r_mul = types.InlineQueryResultArticle(
			id='4',
			title="Произведение",
			description="Результат: {!s}".format(m_mul),
			input_message_content=types.InputTextMessageContent(
				message_text="{!s} * {!s} = {!s}".format(num1, num2, m_mul)
			),
			thumb_url=multiply_icon, thumb_width=48, thumb_height=48
		)
	
		bot.answer_inline_query(query.id, [r_sum, r_sub, r_div, r_mul], cache_time=300)
	
	except Exception as e:
		print("{!s}\n{!s}".format(type(e), str(e)))

@bot.inline_handler(func=lambda query: len(query.query) == 0)
def empty_query(query):
	hint = "Введите ровно 2 числа и получите результат!"
	try:
		r = types.InlineQueryResultArticle(
			id='1',
			title="Бот \"Математика\"",
			description=hint,
			input_message_content=types.InputTextMessageContent(
				message_text="Эх, зря я не ввёл 2 числа :("
			)
		)
		bot.answer_inline_query(query.id, [r])
	except Exception as e:
		print(e)

if __name__ == "__main__":
	bot.infinity_polling()
