var logwebsite = require('./logwebsite'),
	fs = require('fs');


logwebsite("http://www.codemania.co.nz","./codemania.html", function(error) {
	if(!error) { 
		fs.readFile("./codemania.html", 'ascii', function(err, data) {
			if(!err) {
				console.log(data);
			} else {
				console.log(err)
			}
		});
	} else {
		console.log(error);
	}
});

console.log("hello world");