
var IP2Location = require('./index').IP2Location;
var loc = new IP2Location('./IP-COUNTRY-SAMPLE.BIN');

var date = Date.now();
for (var i = 0; i<10000; i++) loc.query('19.1.1.1');

console.log(Date.now() - date);