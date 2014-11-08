var app = require('express')();
var request = require("request");
var server = require('http').Server(app);
var io = require('socket.io')(server);
var getPnValue = require('./pn_value')

app.get('/', function(req, res) {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function(socket) {
  socket.on('message', function(msg) {
    getPnValue(msg, function(pnValue) {
      // TODO: Send to Kinect
      console.log("pnValue: " + pnValue);
    });
  });

  socket.on('hi', function() {
    // Send from Betao to conversation members
    socket.broadcast.emit('hi');
  });

  socket.on('like', function() {
    // TODO: Send to Kinect
  });
});

server.listen(8888, function() {
  console.log('listening on *:8888');
});
