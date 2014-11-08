// require socket.io
function HiSocket() {
  this.socket = io();
}

HiSocket.prototype.sendSomething = function(header, message) {
  hiSocket.emit(header, message);
};
