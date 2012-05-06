var request = require('request'),
	fs = require('fs');

module.exports = logwebsite;

function logwebsite(url, filePath, callback) {
	request(url, function(error, response, body) {
		if(!error) {
			fs.writeFile(filePath, body,function(err) {
				callback(err);
			});
		}
		else {
			callback(error);
		}

	});
}