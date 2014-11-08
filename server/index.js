var app = require('express')();
var request = require("request");
var server = require('http').Server(app);
var io = require('socket.io')(server);
var kinectConnection = require('./kinect_connection');

app.get('/', function(req, res) {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function(socket) {
  socket.on('message', function(msg) {
    kinectConnection.sendMessage(msg);
  });

  socket.on('hi', function() {
    // Send from Betao to conversation members
    console.log('emit hi.');
    socket.broadcast.emit('hi');
  });

  socket.on('like', function() {
    kinectConnection.sendLike();
  });
});

server.listen(8888, function() {
  console.log('listening on *:8888');
});
