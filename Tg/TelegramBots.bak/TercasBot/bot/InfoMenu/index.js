var showInfo = function showInfo(bot, msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
            '<b>Дополнительная информация</b>';
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

    bot.sendMessage(msgChatId, messageText, messageOpts).then(function () {
        var inlineMessageText = 'Адреса';
        $inlineKeyboard = [
                    [ { text: 'Отдел ОрИВП ЦМТУ Росавиации', callback_data: 'Отдел ОрИВП ЦМТУ Росавиации' } ],
                    [ { text: 'МЦ АУВД', callback_data: 'МЦ АУВД' } ]
                ];
        var inlineMessageOpts = {
            parse_mode: "HTML",
            reply_markup: {
                inline_keyboard: $inlineKeyboard
            }
        };

        bot.sendMessage(msgChatId, inlineMessageText, inlineMessageOpts);
    });
};


var sendEventInfoMC = function sendEventInfoMC(bot, msg)
{
    var fromId = msg.from.id;
    var messageText =
            'Полное наименование организации:\n' +
            '<b>Филиал "Московский центр автоматизированного управления воздушным движением"\n' +
            'ФГУП "Госкорпорация по ОрВД"</b>\n\n' +
            'Юридический/Почтовый адрес (индекс): <b>125993 г. Москва, Ленинградский пр-кт, дом 37, корп. 7</b>\n' +
            'Фактический адрес (индекс): <b>119027 г. Москва, ул. Большая Внуковская, дом 2А, стр. 9</b>\n' +
            'Телефон (бухгалтерия): <b>956-43-16</b>\n' +
            'Телефон (отдел кадров): <b>956-88-42</b>\n' +
            'ИНН <b>7734135124/КПП 773202001</b>\n' +
            'ОГРН <b>1027739057500</b>\n\n' +
            'Банковские реквизиты:\n' +
            'банк <b>Сбербанк России ОАО г. Москва</b>\n' +
            'БИК 044525225 р/с 40502810338180133740\n' +
            'к/с 30101810400000000225\n\n' +
            'Директор: <b>Владимир Владимирович Ужаков</b>';
    var messageOpts = {
        parse_mode: "HTML"
    };

    bot.sendMessage(fromId, messageText, messageOpts);
};

var sendEventInfoCMTU = function sendEventInfoCMTU(bot, msg)
{
    var fromId = msg.from.id;
    var messageText =
            '<b>Отдел ОрИВП ЦМТУ Росавиации</b>\n\n' +
            'Начальник отдела ОрИВП: <b>Говоров Сергей Владимирович</b>\n' +
            'тел.: 8-915-265-56-52 <i>(предварительно позвонить)</i>\n\n' +
            'Секретарь: <b>Урсу Юрий Иванович</b>\n' +
            'тел.: 8-967-121-35-01\n\n' +
            'Зам. начальника: \n' +
            'тел.: 8-495-540-67-02\n\n' +
            'Адрес: г.Люберцы, Октябрьский проспект, д.15 (каб. №523 и каб. №416)\n\n' +
            'Как добираться:\n' +
            '1. М.Лермонтовский проспект - выход из первого вагона.\n' +
            '2. Выходим на улицу, далее идем в сторону области по тротуару 10-15 мин до' +
            '   5-ти этажного здания из серой керамической плитки (здание \"Международный банк сервиса\")' +
            '3. Войти через центральный вход.\n\n' +
            'При себе иметь:\n' +
            '1. Общегражданский паспорт\n' +
            '2. Свидетельство диспетчера УВД (взять у инструкторов)\n' +
            '3. Другие необходимые документы';
    var messageOpts = {
        parse_mode: "HTML"
    };

    bot.sendMessage(fromId, messageText, messageOpts);
};


module.exports.showInfo = showInfo;
module.exports.sendEventInfoMC = sendEventInfoMC;
module.exports.sendEventInfoCMTU = sendEventInfoCMTU;
