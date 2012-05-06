var helloWorld = require('./build/release/demo'),
	net =  require('net');


net.createServer(function(sock) {
    sock.on('data', function(data) {
      	helloWorld.helloWorld(data, function(err,say) {
			console.log(data);
		});
    });
    
    
    sock.on('close', function(data) {
    	console.log('bye bye')   
    });
    
}).listen(4488);


