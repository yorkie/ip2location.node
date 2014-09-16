
var IP2Location = require('./index').IP2Location;
var loc = new IP2Location('./IP-COUNTRY-SAMPLE.BIN');

console.log(loc.getAll('19.1.1.1'));