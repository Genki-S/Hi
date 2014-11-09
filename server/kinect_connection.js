var dgram = require('dgram');
var getPnValue = require('./pn_value_en')

var HSV_ACCUMULATION_LIMIT = 1;

var KINECT_PORT = 55555;
// var KINECT_HOST = '255.255.255.255';
var KINECT_HOST = '172.17.0.68';

// likeOn(0 or 1), hi(0 or 1), hsv(string), message
var I_LIKE = 0;
var I_HI = 1;
var I_HSV = 2;
var I_MESSAGE = 3;

module.exports = new kinectConnectionConstructor();

// it's a singleton, so not bothering with prototype.
function kinectConnectionConstructor() {
  var self = this;
  this.socket = dgram.createSocket('udp4'),

  this.params = [0, 0, 140, ""];
  this.accumulatedHSVs = [];
  this.accumulateHSVSum = 0;

  this.clearParams = function() {
    this.params = [0, 0, this.params[I_HSV], " "];
  };

  this.sendParams = function() {
    var paramString = this.params.join(',');
    console.log("[send via UDP] " + paramString);

    var buf = new Buffer(paramString);
    this.socket.send(buf, 0, buf.length, KINECT_PORT, KINECT_HOST, function(err, bytes) {
      // TODO: check status
    });

    this.clearParams();
  }

  this.sendHi = function() {
    this.params[I_HI] = 1;
    this.sendParams();
    // FIXME: Clear LIKE flag, but should not be here
    this.params[I_HI] = 0;
    setTimeout(function() { self.sendParams(); }, 2000);
  };

  this.sendLike = function() {
    this.params[I_LIKE] = 1;
    this.sendParams();
    // FIXME: Clear LIKE flag, but should not be here
    this.params[I_LIKE] = 0;
    setTimeout(function() { self.sendParams(); }, 2000);
  },

  this.sendMessage = function(msg) {
    var self = this;
    this.params[I_MESSAGE] = msg;
    getPnValue(msg, function(pnValue) {
      self.params[I_HSV] = self.pnValueToHSV(pnValue);
      self.sendParams();
    });
  };

  // NOTE: using arithmetic average
  this.pnValueToHSV = function(pnValue) {
    var h = ((-1 * pnValue) * 100) + 140;
    this.accumulateHSV(h);
    return Math.round(this.accumulateHSVSum / this.accumulatedHSVs.length);
  };

  this.accumulateHSV = function(h) {
    this.accumulatedHSVs.push(h);
    this.accumulateHSVSum += h;
    if (this.accumulatedHSVs.length > HSV_ACCUMULATION_LIMIT) {
      var front = this.accumulatedHSVs.shift();
      this.accumulateHSVSum -= front;
    }
    console.log(this.accumulatedHSVs);
  }
}
