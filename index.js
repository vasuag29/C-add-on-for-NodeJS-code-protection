const addon = require('./build/Release/nodeaddon.node');
const assert = require('assert');
/*
console.log(addon.pass_number(100) == 142);
console.log(addon.pass_number(100.5) == 142.5);
console.log(addon.pass_number("100") == 142);
console.log(isNaN(addon.pass_number("no")));
console.log(isNaN(addon.pass_number()));
console.log(isNaN(addon.pass_number(function() {})));
*/

//addon.parse_folder("encryptedfiles");

addon.decrypt('ms250.js');
//var ms250Object = new ms250Obj();
//console.log(ms250Obj.showContent('decrypt Successfully......'));
