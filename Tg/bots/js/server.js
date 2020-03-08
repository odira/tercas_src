var express = require('express');
var packageInfo = require('./package.json');

var app = express();

app.get('/', function (req, res) {
    console.log('\n\n--==== SERVER is triggered at ' + new Date().toISOString() + ' ===--');
    res.json({ version: packageInfo.version });
});

var server = app.listen(process.env.PORT, function () {
    var host = server.address().address;
    var port = server.address().port;
    console.log('Web server started at http://%s:%s', host, port);
});
