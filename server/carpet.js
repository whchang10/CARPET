//My CARPET webpage is host by node.js. 
//To start bart webpage, please go to /home/COEN315 and run "sudo node carpet.js

var express = require('express');
var app = express();
var fs = require('fs');
var port = process.env.PORT || 3031;
var http = require("http");
var net = require('net');
var WebSocketServer = require('websocket').server;


var streaming = false;
var liveImge = fs.readFileSync(__dirname + '/cameraTest.bmp');
var feedcat;
var bodyParser = require('body-parser')
var carDirection = "stop";
var motionDetect = 'no';
var connection;

var server = http.createServer(function (req, res) {
	res.writeHead(200, {'Content-Type': 'text/plain'});
	res.end();
}).listen(50766);

//web socket is for the use of notification
wsServer = new WebSocketServer({
	httpServer: server,
	autoAcceptConnections: false
});

function onWsRequest(request) {
	connection = request.accept('echo-protocol', request.origin);
	connection.sendUTF('test');
}

wsServer.on('request', onWsRequest);

app.use(bodyParser.raw({ type: 'text/plain' })); // to handle post body

app.get('/favicon.ico', function(req, res) {
    res.status(204);
});

app.get('/get_car_direction', function(req, res) {
	console.log('Get car direction ' + carDirection);
	res.set('Content-Type', 'text/plain; charset=utf-8');
	res.set('Direction',  carDirection);
	res.send(carDirection);
	if (carDirection === "right" || carDirection === "left") {
 		carDirection = "stop";
	}
});

app.get('/motion_sensor', function(req, res) {
	if ( motionDetect === 'no' && req.query.detect === 'yes') {
		if(typeof(connection) !== 'undefined'){
			connection.sendUTF('yes');
		}
	}
	motionDetect = req.query.detect;
	console.log('Motion sensor detected: ' + motionDetect);
	res.status(204).send();
});

app.get('/set_car_direction', function(req, res) {
	carDirection = req.query.direction;
	console.log('Set car direction ' + carDirection);
	res.status(204).send();
});

app.get('/motion_notification', function(req, res){
	res.writeHead(200, { 'Content-Type': 'text/plain' });
	if (audioFlag) {
		audioFlag = false;
		res.end('yes');
	} else res.end('no');
});

app.get('/camera', function(req, res) {
	res.writeHead(200, { 'Content-Type': 'image/bmp' });
	res.end(liveImge);
});

app.get('/assets/js/*', function(req, res) {
	//console.log('js: ' + req.path);
	res.writeHead(200, { 'Content-Type': 'application/javascript' });
    var html = fs.readFileSync(__dirname + req.path, 'utf8');
    res.end(html);
});

app.get('/firebase-messaging-sw.js', function(req, res) {
	//console.log('js: ' + req.path);
	res.writeHead(200, { 'Content-Type': 'application/javascript' });
    var html = fs.readFileSync(__dirname + req.path, 'utf8');
    res.end(html);
});

app.get('/assets/css/*', function(req, res) {
	//console.log('css: ' + req.path);
	res.writeHead(200, { 'Content-Type': 'text/css' });
    var html = fs.readFileSync(__dirname + req.path, 'utf8');
    res.end(html);
});

app.get('/assets/img_w/*', function(req, res) {
	//console.log('img:' + req.path);
	res.writeHead(200, { 'Content-Type': 'image/png' });
    var html = fs.readFileSync(__dirname + req.path);
    res.end(html);
});

app.get('/assets/sound/*', function(req, res) {
	//console.log('img:' + req.path);
	res.writeHead(200, { 'Content-Type': 'audio/mpeg' });
    var html = fs.readFileSync(__dirname + req.path);
    res.end(html);
});

app.get('/*', function(req, res) {
	console.log('main' + req.path);
	streaming = false;
    res.writeHead(200, { 'Content-Type': 'text/html' });
	var path = req.path;
	if (path === '/') path = '/index.html';
	console.log(path);
    var html = fs.readFileSync(__dirname + path, 'utf8');
    res.end(html);
});

app.post('/camera', function(req, res){
	console.log('post' + req.path);
	console.log(req.body.length);
	liveImge = req.body;
});

app.listen(3031, '127.0.0.1');
