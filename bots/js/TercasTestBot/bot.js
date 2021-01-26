const TelegramBot = require('node-telegram-bot-api');

const token = '1113430903:AAHokCKvymVRH1aM9nmNViZLNeIlE20VrW0';
const bot = new TelegramBot(token, {polling: true})

bot.onText(/\/echo (.+)/, (msg, match) => {
	const chatId = msg.chat.id;
	const resp = match[1];

	bot.sendMessage(chatId, resp);
});
