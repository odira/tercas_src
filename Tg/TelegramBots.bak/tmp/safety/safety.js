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

var sendSafetyEventsList = function safetyEventsList(bot, msg)
{
    var client = new pg.Client(params);

    client.connect(function (err)
    {
        if (err) throw err;

        var queryStr = 'SELECT * FROM safety.vw_safety WHERE department like \'РДЦ\'';
        client.query(queryStr, function(err, result)
        {
            if (err) throw err;

            bot.answerCallbackQuery(msg.id, 'Найдено ' + result.rows.length + ' записей');

            $inlineKeyboard = [];
            for (var i = 0; i < result.rows.length; i++)
            {
                var outputString = (i + 1).toString() + '. ' +
                        datef('dd MMMM YYYY', result.rows[i].date) + ' \n' +
                        'РДЦ смена №' + result.rows[i].shift + ' ' +
                        'место: ' + result.rows[i].location;
                var inlineKeyboardButton = {
                    text: outputString,
                    callback_data: 'АвиационныйИнцидент ' + result.rows[i].pid.toString()
                };
                $inlineKeyboard.push([inlineKeyboardButton]);
            }
            var inlineMessageText = 'Выберите авиационный инцидент:';
            var inlineMessageOpts = {
                parse_mode: "HTML",
                reply_markup: { inline_keyboard: $inlineKeyboard }
            };

            client.end(function (err) {
                if (err) throw err;
            });

            bot.sendMessage(msg.chat.id, inlineMessageText, inlineMessageOpts);
        });
    });
};


var sendSafetyEvent = function sendSafetyEvent(bot, msg)
{
    var msgData = msg.data.split(' ');
    var fromId = msg.from.id;
    var client = new pg.Client(params);

    client.connect(function (err) {
        if (err) throw err;

        var queryStr = 'SELECT * FROM safety.vw_safety WHERE pid=' + msgData[1];

        client.query(queryStr, function(err, result) {
            if (err) throw err;

            var messageText =
                    '<b>' + datef('dd MMMM YYYY', result.rows[0].date) + ' г.' + '</b> <i>район</i>: <b>' + result.rows[0].location + '</b>\n' +
                    '<b>' + result.rows[0].department + '</b> <i>смена №</i> <b>' + result.rows[0].shift + '</b>\n\n' +
                    '<i>Классификация события:</i>\n<b>' + result.rows[0].classification + '</b>';
            if (result.rows[0].type.length > 0) {
                messageText += '\n\n<i>Вид события:</i>\n<b>' + result.rows[0].type + '</b>';
            }
            if (result.rows[0].factor.length > 0) {
                messageText += '\n\n<i>Факторы:</i>\n<b>' + result.rows[0].factor + '</b>';
            }
            if (result.rows[0].cause.length > 0) {
                messageText += '\n\n<i>Причины события:</i>\n' + result.rows[0].cause;
            }
            if (result.rows[0].details.length > 0) {
                messageText += '\n\n<i>Примечание:</i>\n' + result.rows[0].details;
            }

            var messageOpts = {
                parse_mode: "HTML",
            };

            bot.sendMessage(fromId, messageText, messageOpts);

            client.end(function (err) {
                if (err) throw err;
            });
        });
    });
};


module.exports.sendSafetyEventsList = sendSafetyEventsList;
module.exports.sendSafetyEvent = sendSafetyEvent;
