var datef = require('datef');
datef.lang('ru');

var pg = require('pg');
var params = {
    host: 'ec2-46-137-73-65.eu-west-1.compute.amazonaws.com',
    database: 'dtd9hnmschbrv',
    user: 'jxiumgmvybfmvb',
    password: '05WGi1et9b64fxnnvx88HLB1fZ',
    ssl: true
};

var sendSurnameFirstLetterList = function sendSurnameFirstLetterList(bot, msg)
{
    var msgData = msg.data.split(' ');
    var fromId = msg.from.id;
    var client = new pg.Client(params);

    client.connect(function (err) {
        if (err) throw err;

        var queryStr = 'SELECT pid,surname FROM person.person WHERE surname ilike \'' + msgData[1] + '\%\' AND shift=4';

        client.query(queryStr, function(err, result) {
            if (err) throw err;

            bot.answerCallbackQuery(msg.id, 'Фамилий начинающихся на ' + msgData[1] + ' найдено ' + result.rows.length);

            $inlineKeyboard = [];
            for (var i = 0; i < result.rows.length; i++) {
                var inlineKeyboardButton = {
                    text: result.rows[i].surname,
                    callback_data: '3 ' + result.rows[i].pid.toString()
                };
                $inlineKeyboard.push([inlineKeyboardButton]);
            }
            var inlineMessageText = 'Выберите пользователя:';
            var inlineMessageOpts = {
                parse_mode: "HTML",
                reply_markup: { inline_keyboard: $inlineKeyboard }
            };

            client.end(function (err) {
                if (err) throw err;
            });

            bot.sendMessage(fromId, inlineMessageText, inlineMessageOpts);
        });
    });
};

var sendPersonData = function sendPersonData(bot, msg)
{
    var msgData = msg.data.split(' ');
    var fromId = msg.from.id;
    var client = new pg.Client(params);

    client.connect(function (err) {
        if (err) throw err;

        var queryStr = 'SELECT * FROM person.person WHERE pid=' + msgData[1];

        client.query(queryStr, function(err, result) {
            if (err) throw err;

            var messageText =
                    '<b>' + result.rows[0].surname + '</b>\n' +
                    '<b>' + result.rows[0].name + ' ' + result.rows[0].middlename + '</b>\n' +
                    'Дата рождения: ' + datef('dd MMMM YYYY', result.rows[0].birthday) + '\n\n' +
                    result.rows[0].division + ' ' + result.rows[0].subdivision + ' №' + result.rows[0].shift + '\n' +
                    result.rows[0].position + '\n' +
                    'Табельный номер: ' + result.rows[0].tabnum + '\n' +
                    'Допуски к работе: ' + result.rows[0].positionadmittance;
            var messageOpts = {
                parse_mode: "HTML",
            };

            client.end(function (err) {
                if (err) throw err;
            });

            bot.sendMessage(fromId, messageText, messageOpts);
        });
    });
};

module.exports.sendSurnameFirstLetterList = sendSurnameFirstLetterList;
module.exports.sendPersonData = sendPersonData;
