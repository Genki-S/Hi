function HiSoundRecog() {
  var self = this;
  this.recognition = new webkitSpeechRecognition();
  this.recognition.lang = 'ja-JP';
  this.recognition_now = false;

  this.recognition.onstart = function() {
    console.log("[Speech Recognition] START");
  };

  this.recognition.onresult = function (e) {
    console.log("[Speech Recognition] RESULT");
    console.log(e);
    var result = e.results[e.results.length - 1];
    if (result.isFinal) {
      var inputMsg = result[0].transcript.trim();
      console.log('[emit message] ' + inputMsg);
      hiSocket.emit("message", inputMsg);
    }
    // ここのところでWebSocketにばすばす送る
    document.getElementById('result').innerHTML = result[0].transcript.trim();
  };

  this.recognition.onend = function() {
    console.log("[Speech Recognition] END");
    self.recognition.start();
  };

  this.recognition.onerror = function(e) {
    console.log("[Speech Recognition] ERROR");
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
