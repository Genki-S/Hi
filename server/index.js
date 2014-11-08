var app = require('express')();
var request = require("request");
var server = require('http').Server(app);
var io = require('socket.io')(server);
var kinectConnection = require('./kinect_connection');

app.use(require('express').static(__dirname + '/public'));

app.get('/', function(req, res) {
  res.sendFile(__dirname + '/index.html');
});

app.get('/betao', function(req, res) {
  res.sendFile(__dirname + '/betao.html');
});

io.on('connection', function(socket) {
  socket.on('message', function(msg) {
    kinectConnection.sendMessage(msg);
  });

  socket.on('hi', function() {
    // Send from Betao to conversation members
    console.log('emit hi.');
    socket.broadcast.emit('hi');
    console.log("hi");
  });

  socket.on('like', function() {
    kinectConnection.sendLike();
  });
});

server.listen(8888, function() {
  console.log('listening on *:8888');
});
