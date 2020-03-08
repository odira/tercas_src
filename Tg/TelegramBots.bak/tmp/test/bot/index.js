var app = require('express');
var Bot = require('node-telegram-bot-api');
var Token = require('./token.js');
var botOptions = {
    polling : true
//    webHook : true
};
var bot = new Bot(Token.token, botOptions);

// ******************** Bot Information *************************

bot.getMe().then(function(me)
{
    console.log('Hello! My name is %s!', me.first_name);
    console.log('My id is %s.', me.id);
    console.log('And my username is @%s.', me.username);
});

// ************************** /start *****************************

bot.onText(/^\/start/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
            'Hello everyone!\n\n' +
            'My name is TERCAS 🤖 Bot, and I\'m a bot made to help you in your work';
    $keyboard = [
                ['Перейти в 👔 Главное Меню']
            ];
    var messageOpts = {
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts);
});

// *********************** ГЛАВНОЕ МЕНЮ ************************

bot.onText(/Главное Меню/, function(msg)
{
    console.log('Переходим в 👔 Главное Меню\n\n');

    var msgChatId = msg.chat.id;
    var messageText =
            'Вы перешли в 👔 Главное Меню!\n\n' +
            'Выберите интересующий вас пункт меню.';
    $keyboard = [
         ['👁 Каналы', '\u{1F4AC} Чаты'],
         ['\u{1F4BE} Информация', '🚷 Личный кабинет'],
         ['\u{2139} Справка', '🤖 О программе']
    ];
    var messageOpts = {
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts);
});

bot.onText(/Каналы/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '👁  <b>Каналы</b>\n\n' +
        'Каналы предствляют из себя новостную ленту, сообщения в которой ' +
        'модерируются администраторами этого канала. ' +
        'Обычные пользователи добавлять и редактировать сообщения не могут. ' +
        'По всем интересующим вопросам необходимо обращаться ' +
        'к администраторам канала.\n\n' +
        'Выберите интересующий Вас канал';
    $inlineKeyboard = [
                [ { text: 'TERCAS 🇬🇧 English', url: 'https://t.me/joinchat/AAAAAENJkgoT8KuqKgJYdg' } ],
                [ { text: 'TERCAS 🎧 Portal', url: 'https://t.me/joinchat/AAAAAEGdKzRQnSmNFGMZiQ' } ],
                [ { text: 'TERKAS Channel смена 4 ***Пенза***', url: 'https://t.me/joinchat/AAAAAD7qZtCutWe3PRpOgw' } ]
    ];
    var messageOpts = {
        parse_mode: "HTML",
        reply_markup: {
            inline_keyboard: $inlineKeyboard
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts)
});

bot.onText(/Чаты/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '\u{1F4AC} <b>Чаты</b>\n\n' +
        'Чаты представляют из себы средство общения пользователей';
    $inlineKeyboard = [
                [ { text: 'TERCAS Chat :)', url: 'https://t.me/joinchat/DQSXZENO2aXSICIkJIiUKQ' } ],
                [ { text: 'TERKAS Chat смена 4 *** Пенза ***', url: 'https://t.me/joinchat/DQSXZAoeuoIzGlIJ2GmgWQ' } ]
    ];
    var messageOpts = {
        parse_mode: "HTML",
        reply_markup: {
            inline_keyboard: $inlineKeyboard
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts);
});


// Дополнительная Информация

var InfoMenu = require('./InfoMenu');

bot.onText(/Информация/, function(msg) {
    InfoMenu.showInfo(bot, msg);
});

bot.onText(/Отдел ОрИВП ЦМТУ/, function(msg) {
   InfoMenu.showInfoCMTU(bot, msg)  ;
});


// Главное Меню --> Личный кабинет
bot.onText(/Личный кабинет/, function(msg)
{
//    Information.showInformationMenu(bot, msg);
    var msgChatId = msg.chat.id;
    var messageText =
            '<b>Личный кабинет</b> \u{2708}\n\n' +
            'На данный момент информация в данном разделе предназначена для работников ' +
            'РДЦ смены №4 (Пензенское направление)\n\n' +
            '\u{26A0} Да, пока в таком виде, позже будет по каждому человеку отдельно 🎃';
    $keyboard = [
                [ '🍹 Отпуска', '📚 КПК', '🍭 Отгулы' ],
                [ '🍼 Проверки на секторе', '💼 Служебная информация' ],
//                ['Статистика', 'База данных АП'],
//                ['\u{1F4B1} Курс\nвалюты ЦБ', '\u{2600} Погода на\nаэродромах'],
                ['⬅️ Вернуться в 👔 Главное Меню']
            ];
    var messageOpts = {
        parse_mode: "HTML",
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts);
});

//// Главное Меню --> Отпуска
bot.onText(/Отпуска/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '<b>График 🍹отпусков 2018 г.</b>\n\n' +
        'Ильин\n🍹22.02-03.03\n🍹29.04-08.05\n🍹28.07-31.07\n🍹26.09-29.09\n🍹01.12-28.12\n\n' +
        'Алеев\n🍹29.01-11.02\n🍹28.06-25.07\n🍹13.11-28.11\n\n' +
        'Береза\n🍹23.01-01.02\n🍹18.03-21.03\n🍹05.04-14.04\n🍹05.05-12.05\n🍹02.09-17.09\n🍹13.11-16.11\n\n' +
        'Волков \n🍹28.02-09.03\n🍹29.04-08.05\n🍹01.12-09.12\n\n' +
        'Зыбина\n🍹11.01-20.01\n🍹05.04-14.04\n🍹04.07-19.07\n🍹08.10-23.10\n\n' +
        'Лисяк\n🍹28.06-13.07 \n🍹20.09-19.10 \n🍹25.12-11.01\n\n' +
        'Маркелов\n🍹10.04-02.05\n🍹03.08-30.08\n🍹26.10-10.11\n\n' +
        'Платонова\n🍹23.02-09.03\n🍹29.04-08.05\n🍹16.06-25.06\n🍹21.08-30.08\n🍹01.11-22.11\n\n' +
        'Степанов\n🍹29.05-13.06\n🍹16.07-31.07\n🍹14.09-05.10\n\n' +
        'Степанова\n🍹04.02-11.02\n🍹11.05-26.05\n🍹16.07-25.07\n🍹02.09-11.09\n🍹20.10-10.11\n\n' +
        'Трунин\n🍹17.04-26.04\n🍹03.08-30.08\n🍹13.11-28.11\n\n' +
        'Юреня\n🍹04.02-12.02\n🍹11.05-26.05\n🍹03.08-18.08\n🍹19.11-04.12';
    $keyboard = [
                ['⬅️ Вернуться в 👔 Главное Меню']
    ];
    var messageOpts = {
        parse_mode: "HTML",
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts)
});

//// Главное Меню --> КПК
bot.onText(/КПК/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '<b>График 📚 КПК 2018 г.</b>\n\n' +
        'Алеев\n📚 13.02-06.03\n🇬🇧 08.10-19.10\n\n' +
        'Береза\n🇬🇧14.05-29.05\n📚30.05-09.06\n\n' +
        'Волков\n🇬🇧 10.12-21.12\n\n' +
        'Ильин\n\n' +
        'Зыбина\n\n' +
        'Лисяк\n\n' +
        'Маркелов\n\n' +
        'Платонова\n🇬🇧 12.02-22.02\n\n' +
        'Степанов\n📚 13.02-06.03\n🇬🇧 14.05-25.05\n📚 23.10-02.11\n\n' +
        'Степанова\n🇬🇧02.04-17.04\n📚18.04-28.04\n\n' +
        'Трунин\n🇬🇧11.01-26.01\n📚04.10-16.10\n\n' +
        'Юреня\n📚04.06-15.06\n🇬🇧18.06-03.07';
    $keyboard = [
                ['⬅️ Вернуться в 👔 Главное Меню']
    ];
    var messageOpts = {
        parse_mode: "HTML",
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts)
});

//// Главное Меню --> Отгулы
bot.onText(/Отгулы/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '<b>График 🍭отгулов 2018 г.</b>\n\n' +
        '🍭 Алеев 07-09.03 (март)\n' +
        '🍭 Береза 05-07.02 (февраль)\n' +
        '🍭 Волков 30.01-01.02 (январь-февраль)\n' +
        '🍭 Ильин 18-20.01 (январь)\n' +
        '🍭 Зыбина 07-09.03 (март)\n' +
        '🍭 Лисяк 17-19.02 (февраль)\n' +
        '🍭 Маркелов 25-27.03 (март)\n' +
        '🍭 Платонова 06-08.01 (январь)\n' +
        '🍭 Степанова 13-15.03 (март)\n' +
        '🍭 Степанов 24-26.01 (январь)\n' +
        '🍭 Трунин 19-21.03 (март)\n' +
        '🍭 Юреня 06-08.01 (январь';
    $keyboard = [
                ['⬅️ Вернуться в 👔 Главное Меню']
    ];
    var messageOpts = {
        parse_mode: "HTML",
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts)
});

//// Главное Меню --> 🍼 Проверки на секторе
bot.onText(/🍼 Проверки на секторе/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '<b>График 🍼 Проверок на секторе</b>\n\n' +
        '<b>🍼 Алеев</b>\n<b>В1П1П2</b> 30.04.2017 г. ❗️\n<b>X1X2</b> 19.03.2017 г. ❗️\n<b>В2В3В4</b> 18.05.2017 г. \n\n' +
        '<b>🍼 Береза</b>\n<b>В1П1П2</b> 24.01.2017 г. ❗️\n\n' +
        '<b>🍼 Волков</b>\n\n' +
        '<b>🍼 Девликамов</b>\n<b>В1П1П2</b> 05.06.2017 г.\n\n' +
        '<b>🍼 Иванов</b>\n\n' +
        '<b>🍼 Ильин</b>\n<b>В1П1П2</b> 12.05.2017 г.\n<b>К1К2</b> 15.07.2016 г. ❗️\n<b>Г2Г5</b> 05.05.2016 г. ❗️\n<b>В2В3В4</b> 19.11.2016 г. ❗️\n\n' +
        '<b>🍼 Зыбина</b>\n<b>П1</b> 24.12.2016 г. ❗️\n<b>В1П2</b> 16.04.2017 г. ❗️\n\n' +
        '<b>🍼 Кулаков</b>\n<b>В1П1П2</b> 24.05.2017 г.\n\n' +
        '<b>🍼 Лисяк</b>\n<b>В1П1П2</b> 30.04.2017 г. ❗️\n<b>З1З2</b> 24.05.2016 г. ❗️\n<b>Г3Г4Г6</b> 13.03.2017 г. ❗️\n<b>В2</b> 16.05.2016 г. ❗️\n\n' +
        '<b>🍼 Мамедов</b>\n<b>В1П1П2</b> 18.07.2017 г.\n\n' +
        '<b>🍼 Маркелов</b>\n<b>В1П1П2</b> 10.08.2017 г.\n\n' +
        '<b>🍼 Пилипенко</b>\n<b>В1П1П2</b> 24.04.2017 г. ❗️\n\n' +
        '<b>🍼 Платонова</b>\n<b>В1П1П2</b> 18.05.2017 г.\n<b>П1</b> 02.09.2017 г.\n\n' +
        '<b>🍼 Степанова</b>\n<b>В1П1П2</b> 18.04.2017 г. ❗️\n\n' +
        '<b>🍼 Степанов</b>\n<b>В1П1П2</b> 22.10.2017 г.\n<b>В2В3В4</b> 13.05.2017 г.\n\n' +
        '<b>🍼 Сутурин</b>\n<b>В1П1П2</b> 18.04.2017 г. ❗️\n\n' +
        '<b>🍼 Трунин</b>\n<b>В1П1П2</b> 23.10.2017 г.\n<b>В2</b> 24.01.2017 г. ❗️\n\n' +
        '<b>🍼 Цимбровский</b>\n<b>В1П1П2</b> 18.04.2017 г. ❗️\n\n' +
        '<b>🍼 Шуватов</b>\n<b>В1П1П2</b> 17.08.2017 г.\n\n' +
        '<b>🍼 Юреня</b>\n<b>В1П1П2</b> 24.01.2017 г. ❗️';
    $keyboard = [
                ['⬅️ Вернуться в 👔 Главное Меню']
    ];
    var messageOpts = {
        parse_mode: "HTML",
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts)
});

//// Главное Меню --> О программе
bot.onText(/О программе/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '\u{2139} <b>О программе</b>\n\n' +
        '@TercasBot на данный момент находится в тестовом режиме. \u{1F6A7}\n' +
        'Свои предложения и замечания по его работе ' +
        'Вы можете направлять пользователю @Tercas\n\n' +
        'Приглашаются желающие принять участие в разработке ! ' +
        '(Знание JavaScript, Python, PHP, C, Perl приветствуются но это необязательно)';
    $keyboard = [
                ['⬅️ Вернуться в 👔 Главное Меню']
    ];
    var messageOpts = {
        parse_mode: "HTML",
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts)
});




////var safety = require('./safety');
////var person = require('./person');


////var pg = require('pg');
////var params = {
////    host: 'ec2-46-137-73-65.eu-west-1.compute.amazonaws.com',
////    database: 'dtd9hnmschbrv',
////    user: 'jxiumgmvybfmvb',
////    password: '05WGi1et9b64fxnnvx88HLB1fZ',
////    ssl: true
////};

////var datef = require('datef');
////datef.lang('ru');


////var TelegramBot = require('node-telegram-bot-api'),
////    port = process.env.PORT || 443,
////    host = '0.0.0.0',  // probably this change is not required
////    externalUrl = process.env.CUSTOM_ENV_VARIABLE || 'https://my-app.herokuapp.com',
////    token = process.env.TOKEN,
////    bot = new TelegramBot(process.env.TOKEN, { webHook: { port : port, host : host } });
////bot.setWebHook(externalUrl + ':443/bot' + token);


////var bot = new Bot(Token.token);
////bot.setWebHook('https://terkasbot.herokuapp.com');

////var bot = new Bot('232616102:AAG8ujo6P5Eak3XtcrW6gvfqodIB68Dl91o', { webHook: { port: 8443, host: '0.0.0.0' } });
////bot.setWebHook('https://terkasbot.herokuapp.com' + ':8443/bot' + '232616102:AAG8ujo6P5Eak3XtcrW6gvfqodIB68Dl91o');
////bot.setWebHook('');

////var bot = new Bot('232616102:AAG8ujo6P5Eak3XtcrW6gvfqodIB68Dl91o');
////bot.setWebHook('https://terkasbot.herokuapp.com' + ':8443/' + '232616102:AAG8ujo6P5Eak3XtcrW6gvfqodIB68Dl91o');



//bot.getMe().then(function(me)
//{
//    console.log();
//    console.log('Hello! My name is %s!', me.first_name);
//    console.log('My id is %s.', me.id);
//    console.log('And my username is @%s.', me.username);
//    console.log('I started at ', Date());
//    console.log();
//});




//// ****************************************************
//// ************* INFORMATION Menu *********************
//// ****************************************************


//    bot.sendMessage(msgChatId, messageText, messageOpts).then(function (go)
//    {
//        console.log('OK');
//    });
//});

//// Главное Меню --> Информация --> База данных
////        ...                  --> валюты
////        ...                  --> Погода
////
//bot.on('text', function (msg)
//{
//    msgText = msg.text;

//    if (msgText.indexOf('База данных') >= 0)
//        safety.sendSafetyEventsList(bot, msg);
//    else if (msgText.indexOf('валюты') >= 0)
//        bot.sendMessage(msgChatId, '@TerkasCurrencyBot');
//    else if (msgText.indexOf('Погода') >= 0)
//        bot.sendMessage(msgChatId, '@TerkasWeatherBot');
//});


//// ****************************************************
//// ************* PERSON Menu **************************
//// ****************************************************

//// Главное Меню --> Сотрудники
////
//bot.onText(/Сотрудники/, function(msg)
//{
//    var msgChatId = msg.chat.id;
//    var messageText =
//            '<b>Служебная информация подразделения РДЦ</b> \u{2708}\n\n' +
//            '\u{26A0} <b>Внимание:</b> СТАДИЯ ТЕСТИРОВАНИЯ';
//    $keyboard = [
//                ['График работы на год \u{1F4C5}', 'Техническая учеба на год \u{1F4C5}', 'График отпусков \u{1F4C5}'],
//                ['Расстановка на смену \u{1F46B}', 'Персональные данные \u{1F464}'],
//                //                ['Расстановка на смену \u{1F46B}', {text: 'Персональные данные \u{1F464}', request_contact: true}],
//                ['Вернуться в Главное Меню \u{2B05}']
//            ];
//    var messageOpts = {
//        parse_mode: "HTML",
//        reply_markup: {
//            keyboard: $keyboard,
//            resize_keyboard: true
//        }
//    };

//    bot.sendMessage(msgChatId, messageText, messageOpts);
//});

//// Главное Меню --> Сотрудники --> Персональные данные
////
//bot.onText(/Персональные данные/, function(msg)
//{
//    var msgChatId = msg.chat.id;
//    var messageText =
//            '<b>Персональные данные работников</b> \u{2708}\n\n' +
//            '\u{26A0} Внимание: СТАДИЯ ТЕСТИРОВАНИЯ';
//    $keyboard = [
//                ['Вернуться в меню Сотрудники \u{1F51E}', 'Вернуться в Главное Меню \u{2B05}']
//            ];
//    var messageOpts = {
//        parse_mode: "HTML",
//        reply_markup: {
//            keyboard: $keyboard,
//            resize_keyboard: true
//        }
//    };

//    bot.sendMessage(msgChatId, messageText, messageOpts).then(function ()
//    {
//        var inlineMessageText = 'Выберите первую букву фамилии пользователя';
//        $inlineKeyboard = [
//                    [{text: 'А', callback_data: '2 А'},
//                     {text: 'Б', callback_data: '2 Б'},
//                     {text: 'В', callback_data: '2 В'},
//                     {text: 'Г', callback_data: '2 Г'},
//                     {text: 'Д', callback_data: '2 Д'},
//                     {text: 'Е', callback_data: '2 Е'}
//                    ],
//                    [{text: 'Ж', callback_data: '2 Ж'},
//                     {text: 'З', callback_data: '2 З'},
//                     {text: 'И', callback_data: '2 И'},
//                     {text: 'К', callback_data: '2 К'},
//                     {text: 'Л', callback_data: '2 Л'},
//                     {text: 'М', callback_data: '2 М'}
//                    ],
//                    [{text: 'Н', callback_data: '2 Н'},
//                     {text: 'О', callback_data: '2 О'},
//                     {text: 'П', callback_data: '2 П'},
//                     {text: 'Р', callback_data: '2 Р'},
//                     {text: 'С', callback_data: '2 С'},
//                     {text: 'Т', callback_data: '2 Т'}
//                    ],
//                    [{text: 'У', callback_data: '2 У'},
//                     {text: 'Ф', callback_data: '2 Ф'},
//                     {text: 'Х', callback_data: '2 Х'},
//                     {text: 'Ц', callback_data: '2 Ц'},
//                     {text: 'Ч', callback_data: '2 Ч'},
//                     {text: 'Ш', callback_data: '2 Ш'}
//                    ],
//                    [{text: 'Щ', callback_data: '2 Щ'},
//                     {text: 'Э', callback_data: '2 Э'},
//                     {text: 'Ю', callback_data: '2 Ю'},
//                     {text: 'Я', callback_data: '2 Я'}
//                    ]
//                ];
//        var inlineMessageOpts = {
//            parse_mode: "HTML",
//            reply_markup: {
//                inline_keyboard: $inlineKeyboard
//            }
//        };

//        bot.sendMessage(msgChatId, inlineMessageText, inlineMessageOpts);
//    });
//});





//// ****************************************************
//// ************* CALLBACK QUERY Menu ******************
//// ****************************************************

//bot.on('callback_query', function (msg)
//{
//    var msgData = msg.data.split(' ');

//    if (msgData[0] === 'АвиационныйИнцидент')
//    {
//        // InformationMenu -> safety.js
//        safety.sendSafetyEvent(bot, msg);
//    }
//    else if (msgData[0] === '2')
//    {
//        // PersonMenu -> person.js
//        person.sendSurnameFirstLetterList(bot, msg);
//    }
//    else if (msgData[0] === '3')
//    {
//        // PersonMenu -> person.js
//        person.sendPersonData(bot, msg);
//    }
//});

