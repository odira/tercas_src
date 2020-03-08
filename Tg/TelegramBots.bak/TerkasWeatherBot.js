var http = require('http');
var Bot = require('node-telegram-bot-api');
var Token = require('./tokens/token.TerkasWeatherBot.js');
var botOptions = {
    polling : true
};

var bot = new Bot(Token.token, botOptions);

var content = "";

bot.getMe().then(function(me)
{
    console.log('Hello! My name is %s!', me.first_name);
    console.log('My id is %s.', me.id);
    console.log('And my username is @%s.', me.username);
});

//
// matches /start
//
bot.onText(/^\/start/, function (msg)
{
    var fromId = msg.from.id; // get the id, of who is sending the message
    var messageText = "Добро пожаловать! \n\n" +
            "Вас приветствует бот @TERKASWeatherBot\n\n" +
            "Получите погоду в городе путем отправки команды:\n /weather [ваш_город]";

    bot.sendMessage(fromId, messageText);
});

//
// matches /weather [whatever]
//
bot.onText(/^\/weather (.+)/, function (msg, match) {
    var fromId = msg.from.id;
    var postcode = match[1];

    getWeatherData(postcode).then(function(data) {
        var messageText = "Погода для " + postcode + "\n";
        messageText += data.wx_desc + "\n";
        messageText += "temp: " + data.temp_c + "C";

        bot.sendMessage(fromId, messageText);
    });
});

function getWeatherData(postcode) {
    var app_id = "c498b87f";
    var app_key = "2a8dc875bc649cbbbff7636b5eb3ad5a";
    var url = "http://api.weatherunlocked.com/api/current/us."+postcode
    url += "?app_id="+app_id+"&app_key="+app_key;

    var options = {
        url: url,
        method: "GET",
        json: true
    }
    var response = request(options);
    return response.then(function (r) {
        return r[0].body
    })
}
