var dgram = require('dgram');
var getPnValue = require('./pn_value')

var KINECT_PORT = 9999;
var KINECT_HOST = 'localhost';
var TYPE_ID = {
  'like': '1',
  'message': '2',
}

module.exports = new kinectConnectionConstructor();

// it's a singleton, so not bothering with prototype.
function kinectConnectionConstructor() {
  this.socket = dgram.createSocket('udp4'),

  this.sendText = function(text) {
    console.log("[send via UDP] " + text);

    var buf = new Buffer(text);
    this.socket.send(buf, 0, buf.length, KINECT_PORT, KINECT_HOST, function(err, bytes) {
      // TODO: check status
    });
  }

  this.sendLike = function() {
    var contents = [TYPE_ID.like, 'Like'];
    this.sendText(contents.join(','));
  },

  this.sendMessage = function(msg) {
    var self = this;
    getPnValue(msg, function(pnValue) {
      var contents = [TYPE_ID.message, pnValue, msg];
      self.sendText(contents.join(','));
    });
  }
}
