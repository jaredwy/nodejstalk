var request = require('request'),
	fs = require('fs');

module.exports = logwebsite;

function logwebsite(url, file, callback) {

	function doRequest(error,response, body) {
		if(!error) {
			fs.writeFile(file, body, writenFile);
		}
		else {
			callback(error);
		}
	}

	function writenFile(error)  {
		callback(error);
	}
	request(url, doRequest);
}