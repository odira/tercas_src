//var pg = require('pg');
//var params = {
//    host: 'ec2-46-137-73-65.eu-west-1.compute.amazonaws.com',
//    database: 'dtd9hnmschbrv',
//    user: 'jxiumgmvybfmvb',
//    password: '05WGi1et9b64fxnnvx88HLB1fZ',
//    ssl: true
//};

//var datef = require('datef');
//datef.lang('ru');


var showPersonMenu = function showPersonMenu(bot, msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
            '<b>Служебная информация подразделения РДЦ</b> \u{2708}\n\n' +
            '\u{26A0} <b>Внимание:</b> СТАДИЯ ТЕСТИРОВАНИЯ';
    $keyboard = [
                ['График работы на год \u{1F4C5}', 'Техническая учеба на год \u{1F4C5}', 'График отпусков \u{1F4C5}'],
                ['Расстановка на смену \u{1F46B}', 'Персональные данные \u{1F464}'],
                //                ['Расстановка на смену \u{1F46B}', {text: 'Персональные данные \u{1F464}', request_contact: true}],
                ['Вернуться в Главное Меню \u{2B05}']
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

var showPersonalDataMenu = function showPersonalDataMenu(bot, msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
            '<b>Персональные данные работников</b> \u{2708}\n\n' +
            '\u{26A0} Внимание: СТАДИЯ ТЕСТИРОВАНИЯ';
    $keyboard = [
                ['Вернуться в Служебное Меню \u{1F51E}', 'Вернуться в Главное Меню \u{2B05}']
            ];
    var messageOpts = {
        parse_mode: "HTML",
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts).then(function ()
    {
        var inlineMessageText = 'Выберите первую букву фамилии пользователя';
        $inlineKeyboard = [
                    [{text: 'А', callback_data: '2 А'},
                     {text: 'Б', callback_data: '2 Б'},
                     {text: 'В', callback_data: '2 В'},
                     {text: 'Г', callback_data: '2 Г'},
                     {text: 'Д', callback_data: '2 Д'},
                     {text: 'Е', callback_data: '2 Е'}
                    ],
                    [{text: 'Ж', callback_data: '2 Ж'},
                     {text: 'З', callback_data: '2 З'},
                     {text: 'И', callback_data: '2 И'},
                     {text: 'К', callback_data: '2 К'},
                     {text: 'Л', callback_data: '2 Л'},
                     {text: 'М', callback_data: '2 М'}
                    ],
                    [{text: 'Н', callback_data: '2 Н'},
                     {text: 'О', callback_data: '2 О'},
                     {text: 'П', callback_data: '2 П'},
                     {text: 'Р', callback_data: '2 Р'},
                     {text: 'С', callback_data: '2 С'},
                     {text: 'Т', callback_data: '2 Т'}
                    ],
                    [{text: 'У', callback_data: '2 У'},
                     {text: 'Ф', callback_data: '2 Ф'},
                     {text: 'Х', callback_data: '2 Х'},
                     {text: 'Ц', callback_data: '2 Ц'},
                     {text: 'Ч', callback_data: '2 Ч'},
                     {text: 'Ш', callback_data: '2 Ш'}
                    ],
                    [{text: 'Щ', callback_data: '2 Щ'},
                     {text: 'Э', callback_data: '2 Э'},
                     {text: 'Ю', callback_data: '2 Ю'},
                     {text: 'Я', callback_data: '2 Я'}
                    ]
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

//        bot.on('message', function(msg)
//        {
//            console.log('\n\n');
//            console.log(msg);
//            console.log('\n\n');
//            if (msg.contact !== undefined) {
//                console.log(msg.contact.phone_number);
//                console.log('\n\n');

//                var fromId = msg.from.id;
//                var pgParams = {
//                    host: 'ec2-46-137-73-65.eu-west-1.compute.amazonaws.com',
//                    database: 'dtd9hnmschbrv',
//                    user: 'jxiumgmvybfmvb',
//                    password: '05WGi1et9b64fxnnvx88HLB1fZ',
//                    ssl: true
//                };
//                var client = new pg.Client(pgParams);

//                client.connect(function (err) {
//                    if (err) throw err;

//        //            var queryStr = 'SELECT surname,tabnum,mobilephone FROM person.person WHERE mobilephone like \'' + msg.contact.phone_number + '\'';
//                    var queryStr = 'SELECT surname,tabnum,mobilephone FROM person.person WHERE mobilephone like \'%' + '903-596-76-36' + '%\'';
//                    client.query(queryStr, function(err, result) {
//                        if (err) throw err;
//                        for (var i = 0; i < result.rows.length; i++) {
//                            var outputString = result.rows[i].surname + ' ' + result.rows[i].tabnum + ' ' + result.rows[i].mobilephone;
//                        }
//                        var inlineMessageText = 'Ваш контакт:' + outputString;
//                        client.end(function (err) {
//                            if (err) throw err;
//                        });
//                        bot.sendMessage(fromId, inlineMessageText);
//                    });
//                });
//            }
//        });


module.exports.showPersonMenu = showPersonMenu;
module.exports.showPersonalDataMenu = showPersonalDataMenu;
