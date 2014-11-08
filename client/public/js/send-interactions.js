function LikeSender(button, socket) {
  // button is document.getElementById('hoge') object
  this.button = button;
  // socket is socket.io object
  this.socket = socket;

  this.button.onclick = function(){
    var el = document.createElement('div');
    el.innerHTML = "like";
    this.parentNode.appendChild(el);
  };
}

function HiSender(button, socket) {
  // button is document.getElementById('hoge') object
  this.button = button;
  // socket is socket.io object
  this.socket = socket;

  this.button.onclick = function(){
    var el = document.createElement('div');
    el.innerHTML = "Hi!";
    this.parentNode.appendChild(el);
  };
}
