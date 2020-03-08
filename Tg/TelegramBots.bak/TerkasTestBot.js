var Q = require('q');
var request = Q.denodeify(require("request"));

var pg = require('pg');

var Bot = require('node-telegram-bot-api');
var Token = require('./tokens/token.TerkasTestBot.js');
var botOptions = {
    polling : true
};
var bot = new Bot(Token.token, botOptions);


bot.getMe().then(function(me)
{
    console.log('Hello! My name is %s!', me.first_name);
    console.log('My id is %s.', me.id);
    console.log('And my username is @%s.', me.username);
});

bot.onText(/^\/start/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText = 'Перейти в Главное Меню';
    $keyboard = [['Перейти в Главное Меню'],
            [{text: 'Телефонный номер', request_contact: true}]];
    var messageOpts = {
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };
    bot.sendMessage(msgChatId, messageText, messageOpts);
});

//
// matches /get some
//
bot.onText(/^\/get (.+)/, function (msg, match)
{
    var fromId = msg.from.id; // get the id, of who is sending the message
    var params = {
        host: 'ec2-46-137-73-65.eu-west-1.compute.amazonaws.com',
        database: 'dtd9hnmschbrv',
        user: 'jxiumgmvybfmvb',
        password: '05WGi1et9b64fxnnvx88HLB1fZ',
        ssl: true
    };
    var client = new pg.Client(params);

});

bot.on('message', function(msg)
{
    console.log('\n\n');
    console.log(msg);
    console.log('\n\n');
    if (msg.contact !== undefined) {
        console.log(msg.contact.phone_number);
        console.log('\n\n');

        var fromId = msg.from.id;
        var pgParams = {
            host: 'ec2-46-137-73-65.eu-west-1.compute.amazonaws.com',
            database: 'dtd9hnmschbrv',
            user: 'jxiumgmvybfmvb',
            password: '05WGi1et9b64fxnnvx88HLB1fZ',
            ssl: true
        };
        var client = new pg.Client(pgParams);

        client.connect(function (err) {
            if (err) throw err;

//            var queryStr = 'SELECT surname,tabnum,mobilephone FROM person.person WHERE mobilephone like \'' + msg.contact.phone_number + '\'';
            var queryStr = 'SELECT surname,tabnum,mobilephone FROM person.person WHERE mobilephone like \'%' + '903-596-76-36' + '%\'';
            client.query(queryStr, function(err, result) {
                if (err) throw err;
                for (var i = 0; i < result.rows.length; i++) {
                    var outputString = result.rows[i].surname + ' ' + result.rows[i].tabnum + ' ' + result.rows[i].mobilephone;
                }
                var inlineMessageText = 'Ваш контакт:' + outputString;
                client.end(function (err) {
                    if (err) throw err;
                });
                bot.sendMessage(fromId, inlineMessageText);
            });
        });
    }
});

// var t = require("./TerkasTestBot/test");
// bot.onText(/ok/, function(msg)
// {
//     t.test();
// });
