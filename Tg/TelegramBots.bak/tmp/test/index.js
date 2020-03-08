//var express = require('express');
//var bodyParser = require()
//var packageInfo = require('./package.json');

//var app = express();
//var server = app.listen(process.env.PORT || 5000, function() {
//    var host = server.address().address;
//    var port = server.address().port;

//    console.log('Web server started at http://%s:%s', host, port);
//});

//app.get('/', function(request, response) {
////  response.render('pages/index');
//    response.json({ name: packageInfo.name });
//    response.json({ version: packageInfo.version });
//});

//***************************

// app.set('port', (process.env.PORT || 5000));

//app.use(express.static(__dirname + '/public'));

// views is directory for all template files
// app.set('views', __dirname + '/views');
// app.set('view engine', 'ejs');

//app.listen(app.get('port'), function() {
// console.log('Node app is running on port', app.get('port'));
// });






var express = require('express');
var packageInfo = require('./package.json');
var bodyParser = require('body-parser');

var app = express();
app.use(bodyParser.json());

app.get('/', function (req, res) {
  res.json({ version: packageInfo.version });
});

var server = app.listen(process.env.PORT, "0.0.0.0", function () {
  var host = server.address().address;
  var port = server.address().port;
  console.log('Web server started at http://%s:%s', host, port);
});

module.exports = function (bot) {
  app.post('/' + bot.token, function (req, res) {
    bot.processUpdate(req.body);
    res.sendStatus(200);
  });
};
