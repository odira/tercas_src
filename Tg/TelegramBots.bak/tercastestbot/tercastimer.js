var TelegramBot = require('node-telegram-bot-api');
const Token = "288096080:AAEwcm9kL63J_5Yvyk8KbClD47G8ytc8CJE";
var botOptions = {
    polling : true
};
var bot = new TelegramBot(Token, botOptions);


var gChatId;
var sectorLabel;
var startTime;


bot.getMe().then(function(me)
{
    console.log('Hello! My name is %s.%s!', me.first_name, me.last_name);
    console.log('My username is @%s.', me.username);
    console.log('My id is %s.', me.id);
});

//bot.on("message", function (msg) {
//    var chatId = msg.chat.id;
//    // do something
//    bot.sendMessage(chatId, "Received your message");
//});

// bot.onText(/^\/start (.+)/, function(msg, match)
bot.onText(/^\/start/, function(msg, match) {
    var chatId = msg.chat.id;
    var messageText =
            'Bot @TercasBot started';
    $keyboard = [
                [ 'Перейти в Главное Меню' ]
            ];
    var messageOpts = {
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(chatId, messageText, messageOpts);
});

bot.onText(/Главное Меню/, function(msg, match) {
    var chatId = msg.chat.id;
    var user = msg.from.first_name;
//    var pullups = parseInt(match[1]);
    var messageText =
            'Пользователь ' + user + '\n\n' +
            'Добро пожаловать!';
    $keyboard = [
            [ 'Выбрать сектор' ]
         ];
    var messageOpts = {
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(chatId, messageText, messageOpts);
});


bot.onText(/Выбрать сектор/, function (msg, match) {
    var chatId = msg.chat.id;
    var messageText =
            'Выберите сектор из списка:';
    $inline_keyboard = [
            [ {text: "П1", callback_data: "П1"}, {text: "В1П2", callback_data: "В1П2"} ]
        ];
    var messageOpts = {
        reply_markup: {
            inline_keyboard: $inline_keyboard,
            resize_keyboard: false
        }
    };

    bot.sendMessage(chatId, messageText, messageOpts);
});

bot.onText(/СТАРТ/, function (msg, match) {
    var chatId = msg.chat.id;
    var messageText =
            'Нажмите СТОП для окончания';
    $keyboard = [
            [ 'СТОП' ]
        ];
    var messageOpts = {
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: false
        }
    };

    gChatId = msg.chat.id;
    Timer.start();

    bot.sendMessage(chatId, messageText, messageOpts);
});

bot.onText(/СТОП/, function (msg, match) {
    var chatId = msg.chat.id;
    var messageText =
            'Таймер был остановлен';
    $keyboard = [
        ['Вернуться в Главное Меню']
    ];
    var messageOpts = {
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(chatId, messageText, messageOpts);

//    dailySummary.stop();
//    bot.sendMessage(gChatId, messageText);
});


//bot.onText(/\/action/, function (msg, match) {
//    var chatId = msg.chat.id;
//    var user = msg.from;

//    var messageText = user.first_name + ", choose an action:";

//    // Optional settings, add the keyboard as reply markup.
//    var opts = {
//        reply_markup: {
//            inline_keyboard: [
//                [{ text: "Coffee", callback_data: "coffee" }],
//                [{ text: "Sweets", callback_data: "sweets" }]
//            ]
//        }
//    };

//    bot.sendMessage(chatId, messageText, opts);
//});

bot.on("callback_query", function (msg) {
    var replyData = msg.data; // sector label
//    switch (replyData) {
//    case "П1":
//        sectorLabel = ;
//        break;
//    case "В1П2":
//        console.log("OK2");
//        break;
//    }
    sectorLabel = replyData;
    sendStartEvent(bot, msg);
});


var CronJob = require('cron').CronJob;

var moment = require('moment');
moment.locale('ru');
require('moment-duration-format');

var Timer = new CronJob('00,10,20,30,40,50 * * * * *', function() {
//    console.log("TEST" + " : " + gChatId);

    // check if startTime is defined
    if (!startTime)
        startTime = moment();

//    var dur = startTime.fromNow();

    var messageText =
            'Учет рабочего времени\n\n' +
            'Начало отчета: ' + startTime.format('LTS') + '\n\n' +
//            'Текущее время: ' + moment().format('LTS') + '\n\n' +
            'Текущее время: ' + moment().format('LTS');
//            'Истекшее время: ' + dur + " : " + dur.format("h:m:s");

    bot.sendMessage(gChatId, messageText);

//    var accountBalance;
//    // check if accountBalance is negative
//    if (!accountBalance)
//        // do something
//    ;
});

//dailySummary.start();

var sendStartEvent = function sendStartEvent(bot, msg)
{
    var fromId = msg.from.id;
//    var msgData = msg.data.split(' ');

    var messageText =
            'Вы выбрали сектор <b>' + sectorLabel + '</b>\n\n' +
            'Нажмите СТАРТ чтобы начать отчет';

    $keyboard = [
        [ {text: 'СТАРТ'} ]
    ];
    var messageOpts = {
        parse_mode: "HTML",
        reply_markup: {
            keyboard: $keyboard
//            resize_keyboard: true
        }
    };

    bot.sendMessage(fromId, messageText, messageOpts);
};
