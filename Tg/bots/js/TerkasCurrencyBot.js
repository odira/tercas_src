var http = require('http');
var Bot = require('node-telegram-bot-api');
var Token = require('./tokens/token.TerkasCurrencyBot.js');
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

bot.onText(/^\/start/, function(msg)
{
    var msgChatId = msg.chat.id;
    var messageText =
            'Курс обмена валюты\n\n' +
            'Выберите вылюту';
    $keyboard = [
        [{text: 'USD'}, {text: 'EUR'}]
    ];
    var messageOpts = {
        reply_markup: {
            keyboard: $keyboard,
            resize_keyboard: true
        }
    };

    bot.sendMessage(msgChatId, messageText, messageOpts);
});

bot.onText(/(USD)|(EUR)/, function(msg)
{
    var msgChatId = msg.chat.id;
    updateCurrencyList(msgChatId);
});

function updateCurrencyList(msgChatId)
{
    var httpOptions = {
        host: 'www.cbr.ru',
        port: 80,
        path: '/scripts/XML_daily.asp?'
    };
    var req = http.request(httpOptions, function(res) {
        res.setEncoding("utf8");
        res.on("data", function(chunk) {
            content += chunk;
        });
        res.on("end", function() {
            bot.sendMessage(msgChatId, shittyParseXml(content));
        });
    });
    req.end();
}

function shittyParseXml(allXml)
{
    var currencyList = {
        'USD': 0.0,
        'EUR': 0.0
    };
    currencyList.USD = getCurrencyValue('USD', allXml);
    currencyList.EUR = getCurrencyValue('EUR', allXml);

    return generateBotAnswer(currencyList);
}

function generateBotAnswer(aCurrencyList)
{
    var currencyTable = 'CURRENCY:\n';
    currencyTable += '1 USD = ' + aCurrencyList.USD + ' RUB;\n';
    currencyTable += '1 EUR = ' + aCurrencyList.EUR + ' RUB;\n';
    return currencyTable;
}

function getCurrencyValue(aCurrency, aString)
{
    var nominal = parseFloat(
        replaceCommasByDots(getStringBelow(aString.indexOf(aCurrency), 1, aString)));

    var value = parseFloat(
        replaceCommasByDots(getStringBelow(aString.indexOf(aCurrency), 3, aString)));

    return (value/nominal).toFixed(4);
}

function replaceCommasByDots(aString)
{
    return aString.replace(',', '.');
}

function getStringBelow(aStart, aBelow, aString)
{
    var textSize = aString.length;
    var countOfLineEndings = 0;
    var getLineWith = 0;

    for (var i = aStart; i < textSize; ++i) {
        if (countOfLineEndings === aBelow) {
            getLineWith = i;
            break;
        }
        if (aString[i] === '\n') {
            countOfLineEndings++;
        }
    }

    return getLineFromXml(getLineWith, aString);
}

function getLineFromXml(aStart, aString)
{
    var textSize = aString.length;
    var targetString = '';

    for (var i = aStart; i < textSize; i++) {
        if (aString[i] === '\n') {
            break;
        }
        targetString += aString[i];
    }

    return removeTags(targetString.trim());
}

function removeTags(aString)
{
    return aString.replace(/(<([^>]+)>)/ig, '');
}
