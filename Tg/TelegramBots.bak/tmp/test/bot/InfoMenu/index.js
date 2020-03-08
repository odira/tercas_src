//var Safety = require('./safety');

//var showInformationMenu = function showInformationMenu(bot, msg)
//{
//    var msgChatId = msg.chat.id;
//    var messageText =
//            '<b>Служебная информация РДЦ\nсмены №4 (Пензенское направление)</b> \u{2708}\n\n' +
//            'На данный момент информация в данном разделе предназначена для работников ' +
//            'РДЦ смены №4 (Пензенское направление)\n\n' +
//            '\u{26A0} Внимание: СТАДИЯ ТЕСТИРОВАНИЯ';
//    $keyboard = [
//                ['Статистика', 'База данных АП'],
//                ['\u{1F4B1} Курс\nвалюты ЦБ', '\u{2600} Погода на\nаэродромах'],
//                ['Вернуться в Главное Меню \u{2B05}']
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
//        bot.onText(/База данных/, function(message) { Safety.sendSafetyEventsList(bot, msg); });
//        bot.onText(/валюты/, function(message) { bot.sendMessage(msgChatId, '@TerkasCurrencyBot'); });
//        bot.onText(/Погода/, function(message) { bot.sendMessage(msgChatId, '@TerkasWeatherBot'); });
//    });
//};

//module.exports.showInformationMenu = showInformationMenu;


var showInfo = function showInfo(bot, msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
            '<b>Дополнительная информация</b>';
    $keyboard = [
                [ 'Отдел ОрИВП ЦМТУ Росавиации' ],
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
};

var showInfoCMTU = function showInfoCMTU(bot, msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
            '<b>Отдел ОрИВП ЦМТУ Росавиации</b>\n\n' +
            'Начальник отдела ОрИВП: <b>Говоров Сергей Владимирович</b>\n' +
            'тел.: 8-915-265-56-52 <color=red>(предварительно позвонить)</color>\n\n' +
            '';

    bot.sendMessage(msgChatId, messageText);
};

module.exports.showInfo = showInfo;
module.exports.showInfoCMTU = showInfoCMTU;



//// Главное Меню --> Службы
//bot.onText(/Службы/, function(msg)
//{
////    Information.showInformationMenu(bot, msg);
//    var msgChatId = msg.chat.id;
//    var messageText =
//            '<b>Дополнительная информация</b> \u{2708}\n\n';
//    $keyboard = [
//                [ 'Отдел ОрИВП ЦМТУ Росавиации' ],
//                ['⬅️ Вернуться в 👔 Главное Меню']
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

//// Главное Меню --> Отдел ОрИВП
//bot.onText(/Отдел ОрИВП/, function(msg)
//{
////    Information.showInformationMenu(bot, msg);
//    var msgChatId = msg.chat.id;
//    var messageText =
//            '<b>Отдел ОрИВП ЦМТУ Росавиации</b> \u{2708}\n\n' +
//            'Начальник отдела ОрИВП: <b>Говоров Сергей Владимирович</b>\n' +
//            'тел.: 8-915-265-56-52 (предварительно позвонить)\n\n' +
//            '';

//    bot.sendMessage(msgChatId, messageText);
//});
