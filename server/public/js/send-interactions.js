function LikeSender(button) {
  // button is document.getElementById('hoge') object
  this.button = button;

  this.button.onclick = function(){
    hiSocket.emit("like", "like");
  };
}

function HiSender(button) {
  // button is document.getElementById('hoge') object
  this.button = button;

  this.button.onclick = function(){
    hiSocket.emit("hi", "Hi");
  };
}
