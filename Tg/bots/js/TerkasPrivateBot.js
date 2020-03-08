var http = require('http');
var Bot = require('node-telegram-bot-api');
var Token = require('./tokens/token.TerkasPrivateBot.js');
var botOptions = {
    polling : true
};

var bot = new Bot(Token.token, botOptions);

var content = "";

bot.getMe().then(function(me)
{
    console.log('Hello! My name is %s!', me.first_name);
    console.log('My id is %s.', me.id);
    console.log('And my username is @%s.', me.username);
});

bot.onText(/^\/start/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
            'Курс обмена валюты\n\n' +
            'Выберите вылюту';
    $keyboard = [
        [{text: 'USD'}, {text: 'EUR'}]
    ];
    var messageOpts = {
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts);
});
