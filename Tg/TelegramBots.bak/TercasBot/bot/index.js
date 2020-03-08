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

// ************************** start *****************************

bot.onText(/^\/start/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
            'Hello everyone!\n\n' +
            'My name is TERCAS 🤖 Bot, and I\'m a bot made to help you in your work';
    $keyboard = [
                ['👔 Главное Меню']
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

bot.onText(/👔 Главное Меню/, function(msg)
{
    console.log('Пользователь перешел в 👔 Главное Меню');

    var msgChatId = msg.chat.id;
    var messageText =
            'Вы перешли в 👔 <b>Главное Меню</b>\n\n' +
            'Выберите интересующий вас пункт меню:\n' +
            '1. 👁 Каналы\n' +
            '2. 💬 Чаты\n' +
            '3. Информация\n' +
            '4. 🚷 Личный кабинет\n' +
            '5. Справка\n' +
            '6. 🤖 О программе\n' +
            '.';
    $keyboard = [
         ['👁 Каналы', '💬 Чаты'],
         ['Информация', '🚷 Личный кабинет'],
         ['Справка', '🤖 О программе']
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

bot.onText(/👁 Каналы/, function(msg)
{
    console.log('Пользователь перешел в меню 👁 Каналы');

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

bot.onText(/💬 Чаты/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '💬 <b>Чаты</b>\n\n' +
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

// \🚷
// Личный кабинет

var PrivateMenu = require('./PrivateMenu');

bot.onText(/🚷 Личный кабинет/, function(msg) {
    PrivateMenu.showPrivate(bot, msg);
});

bot.onText(/🍹 Отпуска/, function(msg) {
    PrivateMenu.showVacation(bot, msg);
});

bot.onText(/📚 КПК/, function(msg) {
    PrivateMenu.showLearn(bot, msg);
});

bot.onText(/🍭 Отгулы/, function(msg) {
    PrivateMenu.showDayoff(bot, msg);
});
bot.onText(/🍼 Проверки на секторе/, function(msg) {
    PrivateMenu.showSectorcheck(bot, msg);
});


// О программе

bot.onText(/🤖 О программе/, function(msg)
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


// ************* CALLBACK QUERY ******************

bot.on('callback_query', function (msg)
{
//    var msgData = msg.data.split(' ');
    var msgData = msg.data;

    if (msgData == 'Отдел ОрИВП ЦМТУ Росавиации') {
        InfoMenu.sendEventInfoCMTU(bot, msg);
    } else if (msgData == 'МЦ АУВД') {
        InfoMenu.sendEventInfoMC(bot, msg);
    }

//    if (msgData[0] === 'Отдел ОрИВП ЦМТУ Росавиации')
//    {
////        safety.sendSafetyEvent(bot, msg);
//        console.log('TEST');
//    }
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

