var helloWorld = require('./build/Release/demo');

helloWorld.helloWorld("Say this", function(err,say) {
	console.log(say);
});