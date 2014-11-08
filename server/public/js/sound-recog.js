function HiSoundRecog() {
  this.recognition = new webkitSpeechRecognition();
  this.recognition.lang = 'ja-JP';
  this.recognition.continuous = true;
  this.recognition.interimResults = true;
  this.recognition_now = false;

  this.recognition.onresult = function (e) {
    var finalText = '';
    var interimText = '';
    for (var i = 0; i < e.results.length; i++) {
      if (e.results[i].isFinal) {
        finalText += e.results[i][0].transcript;
        hiSocket.emit("message", e.results[i][0].transcript);
      } else {
        interimText += e.results[i][0].transcript;
      }
    }
    // ここのところでWebSocketにばすばす送る
    document.getElementById('result').innerHTML = finalText;
    document.getElementById('interim').innerHTML = interimText;
  };

  this.recognition.onerror = function(e) {
    console.log(e);
  };
};

HiSoundRecog.prototype.start = function() {
  this.recognition.start();
  this.recognition_now = true;
};

HiSoundRecog.prototype.stop = function() {
  this.recognition.stop();
  this.recognition_now = false;
};
