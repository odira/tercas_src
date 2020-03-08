var showPrivate = function showPrivate(bot, msg)
{
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

    $inlineKeyboard = [
                [ { text: 'Отдел ОрИВП ЦМТУ Росавиации', callback_data: 'Отдел ОрИВП ЦМТУ Росавиации' } ],
                [ { text: 'МЦ АУВД', callback_data: 'МЦ АУВД' } ]
            ];

    var messageOpts = {
        parse_mode: "HTML",
        reply_markup: {
            inline_keyboard: $inlineKeyboard,
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts);
};

module.exports.showPrivate = showPrivate;


var showVacation = function showVacation(bot, msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '<b>График 🍹отпусков 2018 г.</b>\n\n' +
        'Ильин\n🍹22.02-03.03\n🍹29.04-08.05\n🍹28.07-31.07\n🍹26.09-29.09\n🍹01.12-28.12\n\n' +
        'Алеев\n🍹29.01-11.02\n🍹28.06-25.07\n🍹13.11-28.11\n\n' +
        'Береза\n🍹23.01-01.02\n🍹18.03-21.03\n🍹05.04-14.04\n🍹05.05-12.05\n🍹02.09-17.09\n🍹13.11-16.11\n\n' +
        'Волков \n🍹28.02-09.03\n🍹29.04-08.05\n🍹01.12-09.12\n\n' +
        'Зыбина\n👶on baby sitter\n\n' +
        'Иванов\n🍹15.04-02.05\n🍹27.05-15.06\n🍹14.09-07.10\n🍹31.12-03.01\n\n' +
        'Лисяк\n🍹28.06-13.07 \n🍹20.09-19.10 \n🍹25.12-11.01\n\n' +
        'Маркелов\n🍹10.04-02.05\n🍹03.08-30.08\n🍹26.10-10.11\n\n' +
        'Платонова\n🍹23.02-09.03\n🍹29.04-08.05\n🍹16.06-25.06\n🍹21.08-30.08\n🍹01.11-22.11\n\n' +
        'Степанов\n🍹29.05-13.06\n🍹16.07-31.07\n🍹14.09-05.10\n\n' +
        'Степанова\n🍹11.05-26.05\n🍹16.07-25.07\n🍹02.09-11.09\n🍹20.10-10.11\n\n' +
        'Трунин\n🍹17.04-26.04\n🍹03.08-30.08\n🍹13.11-28.11\n\n' +
        'Юреня\n🍹11.05-20.05\n🍹03.08-18.08\n🍹19.11-04.12';
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
};

module.exports.showVacation = showVacation;


var showLearn = function showLearn(bot, msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '<b>График 📚 КПК 2018 г.</b>\n\n' +
        'Алеев\n📚 (КПП) 13.02-06.03\n🇬🇧 (ref) 08.10-19.10\n\n' +
        'Береза\n📚 21.05-31.05\n🇬🇧 01.06-22.06\n\n' +
        'Волков\n🇬🇧 (ref)10.12-21.12\n\n' +
        'Ильин\n\n' +
        'Зыбина\n\n' +
        'Иванов\n📚 22.11-04.12\n\n' +
        'Лисяк\n\n' +
        'Маркелов\n\n' +
        'Платонова\n🇬🇧  (ref) 12.02-22.02\n\n' +
        'Степанов\n🇬  (ref) 29.10-09.11\n\n' +
        'Степанова\n📚 03.04-13.04\n🇬🇧 16.04-08.05\n\n' +
        'Трунин\n🇬🇧 24.01-13.02\n📚 08.10-18.10\n\n' +
        'Юреня\n🇬🇧 24.01-13.02';
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
};

module.exports.showLearn = showLearn;


var showDayoff = function showDayoff(bot, msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '<b>График 🍭отгулов 2018 г.</b>\n\n' +
        '🍭 Алеев 07-09.03 (март)\n' +
        '🍭 Береза 05-07.02 (февраль)\n' +
        '🍭 Волков 30.01-01.02 (январь-февраль)\n' +
        '🍭 Ильин 18-20.01 (январь) ✅\n' +
        '🍭 Зыбина\n' +
        '🍭 Иванов 07.03-09.03 (март)\n' +
        '🍭 Лисяк 17-19.02 (февраль)\n' +
        '🍭 Маркелов 25-27.03 (март)\n' +
        '🍭 Платонова 06-08.01 (январь) ✅\n' +
        '🍭 Степанова 13-15.03 (март)\n' +
        '🍭 Степанов 24-26.01 (январь)\n' +
        '🍭 Трунин 19-21.03 (март)\n' +
        '🍭 Юреня 06-08.01 (январь) ✅';
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
};

module.exports.showDayoff = showDayoff;


var showSectorcheck = function showSectorcheck(bot, msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
        '<b>График 🍼 Проверок на секторе</b>\n\n' +
        '<b>🍼 Алеев</b>\n<b>В1П1П2</b> 20.01.2018 г.\n<b>X1X2</b> 07.01.2018 г.\n<b>В2В3В4</b> 08.12.2017 г.\n\n' +
        '<b>🍼 Береза</b>\n<b>В1П1П2</b> 02.11.2017 г.\n\n' +
        '<b>🍼 Волков</b>\n\n' +
        '<b>🍼 Девликамов</b>\n<b>В1П1П2</b>02.12.2017 г.\n\n' +
        '<b>🍼 Иванов</b>\n<b>В1П1П2</b> 20.11.2017 г.\n<b>К1К2</b> 25.01.2018 г.\n<b>Х1Х2</b> 21.12.2017 г.\n<b>А5</b> 08.01.2018 г.\n\n' +
        '<b>🍼 Ильин</b>\n<b>В1П1П2</b> 08.12.2017 г.\n<b>К1К2</b> 15.07.2016 г. ❗️\n<b>Г2Г5</b> 05.05.2016 г. ❗️\n<b>В2В3В4</b> 19.11.2016 г. ❗️\n\n' +
        '<b>🍼 Зыбина</b>\n<b>В1П1П2</b> 02.11.2017 г.\n\n' +
        '<b>🍼 Кулаков</b>\n<b>В1П1П2</b> 21.12.2017 г. ❗️\n\n' +
        '<b>🍼 Лисяк</b>\n<b>В1П1П2</b> 03.11.2017 г.\n<b>З1З2</b> 08.01.2018 г.\n<b>Г3Г4Г6</b> 14.12.2017 г.\n<b>В2</b> 16.05.2016 г. ❗️\n<b>Л1С1</b>❗️\n\n' +
        '<b>🍼 Мамедов</b>\n<b>В1П1П2</b> 18.07.2017 г.\n\n' +
        '<b>🍼 Маркелов</b>\n<b>В1П1П2</b> 27.11.2017 г.\n<b>В2В3В4</b> 20.12.2017 г.\n\n' +
        '<b>🍼 Пилипенко</b>\n<b>В1П1П2</b> 24.04.2017 г. ❗️\n\n' +
        '<b>🍼 Платонова</b>\n<b>В1П1П2</b> 08.11.2017 г.\n\n' +
        '<b>🍼 Степанова</b>\n<b>В1П1П2</b> 20.11.2017 г.\n<b>В3</b> 11.04.2017 г. ❗️\n\n' +
        '<b>🍼 Степанов</b>\n<b>В1П1П2</b> 22.10.2017 г.\n<b>В2В3В4</b> 13.05.2017 г. ❗️\n\n' +
        '<b>🍼 Сутурин</b>\n<b>В1П1П2</b> 18.04.2017 г. ❗️\n\n' +
        '<b>🍼 Трунин</b>\n<b>В1П1П2</b> 23.10.2017 г.\n<b>В2В3В4</b> 02.12.2017 г.\n\n' +
        '<b>🍼 Цимбровский</b>\n<b>В1П1П2</b> 18.04.2017 г. ❗️\n\n' +
        '<b>🍼 Шуватов</b>\n<b>В1П1П2</b> 25.01.2018 г.\n\n' +
        '<b>🍼 Юреня</b>\n<b>В1П1П2</b> 03.11.2017 г.';
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
};

module.exports.showSectorcheck = showSectorcheck;
