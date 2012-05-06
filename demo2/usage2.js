var logwebsite = require('./logwebsite'),
	fs = require('promised-io/fs'),
	promise = require('promised-io/promise');


function readFile() {
	return fs.read("./codemania.html");
}
function writeData(data) {
	console.log(data);
}
function error(err) {
	console.log(err);
}

logwebsite("http://www.codemania.co.nz","./codemania.html")
.then(readFile, error)
.then(writeData);
