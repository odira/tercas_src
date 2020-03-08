var Bot = require('node-telegram-bot-api');
//var Token = require('./tokens/token.TerkasRDCBot.js');
var Token = '288096080:AAEwcm9kL63J_5Yvyk8KbClD47G8ytc8CJE';
var botOptions = {
    polling : true
};

//var bot = new Bot(Token.token, botOptions);
var bot = new Bot(Token, botOptions);

bot.getMe().then(function(me)
{
    console.log();
    console.log('Hello! My name is %s!', me.first_name);
    console.log('My id is %s.', me.id);
    console.log('And my username is @%s.', me.username);
    console.log();
});

bot.onText(/^\/start/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText = 'Выберите категорию';
    $keyboard = [
        [{text: 'Отгулы'}, {text: 'Отпуска'}]
    ];
    var messageOpts = {
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts);
});

//bot.onText(/Отгулы/, showVacations);

//function showVacations(msg)
bot.onText(/Отгул/, function(msg) {
    var msgChatId = msg.chat.id;
    var messageText = '🍭 Алеев 07-09.03 (март)\n' +
                                  '🍭 Береза 05-07.02 (февраль)\n' +
                                  '🍭 Волков 24-26.01 (январь)\n' +
                                  '🍭 Ильин 18-20.01 (январь)\n' +
                                  '🍭 Зыбина 11-13.02 (февраль)\n' +
                                  '🍭 Комаров 12-14.01 (январь)\n' +
                                  '🍭 Лисяк 17-19.02 (февраль)\n' +
                                  '🍭 Маркелов 25-27.03 (март)\n' +
                                  '🍭 Платонова 06-08.01 (январь)\n' +
                                  '🍭 Степанова 13-15.03 (март)\n' +
                                  '🍭 Степанов 23-25.02 (февраль)\n' +
                                  '🍭 Трунин 19-21.03 (март)\n' +
                                  '🍭 Юреня 06-08.01 (январь)';

    bot.sendMessage(msgChatId, messageText);
});
