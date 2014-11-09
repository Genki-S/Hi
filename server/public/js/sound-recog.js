// This speech recognition logic is full of hacks.
// Problem: webkitSpeechRecognition does not stop recognition while there is
//          some audio input (so, in conversations it is likely that recognition
//          does never stop...)
// Hack:    *delete* webkitSpeechRecognition object when RECOGNITION_TIMEOUT
//          has passed. And *newly create* webkitSpeechRecognition.
//          when doing this, the last recognized interim result from old
//          webkitSpeechRecognition is emit to ensure the best effort.
var RECOGNITION_TIMEOUT = 5000;

function HiSoundRecog() {
  var self = this;
  this.recognition = null;
  this.lastRecognizedMessage = "";

  this.initAndStartRecognition = function() {
    console.log("[Speech Recognition] initRecognition");

    console.log(self.lastRecognizedMessage);
    if (self.lastRecognizedMessage !== "") {
      self.emitMessage(self.lastRecognizedMessage);
    }
    self.lastRecognizedMessage = "";

    self.recognition = new webkitSpeechRecognition();
    self.recognition.lang = 'ja-JP';
    self.recognition.interimResults = true;
    self.recognition.onstart = self.recognitionOnStartHundler;
    self.recognition.onresult = self.recognitionOnResultHundler;
    self.recognition.onspeechstart = self.recognitionOnSpeechstartHundler;
    self.recognition.onspeechend = self.recognitionOnSpeechendHundler;
    self.recognition.onend = self.recognitionOnEndHundler;
    self.recognition.onerror = self.recognitionOnErrorHundler;
    self.recognition.start();
  };

  this.emitMessage = function(message) {
    console.log('[emit message] ' + message);
    hiSocket.emit("message", message);
    document.getElementById('result').innerHTML = message;
  };

  this.recognitionOnStartHundler = function() {
    console.log("[Speech Recognition] START");
    setTimeout(function() {
      self.stopAndRestart();
    }, RECOGNITION_TIMEOUT);
  };

  this.recognitionOnResultHundler = function (e) {
    console.log("[Speech Recognition] RESULT");
    console.log(e);
    var result = e.results[e.results.length - 1];
    var inputMsg = result[0].transcript.trim();
    self.lastRecognizedMessage = inputMsg;
  };

  this.recognitionOnSpeechstartHundler = function (e) {
    console.log("[Speech Recognition] SPEECH START");
  };

  this.recognitionOnSpeechendHundler = function (e) {
    console.log("[Speech Recognition] SPEECH END");
  };

  this.recognitionOnEndHundler = function() {
    console.log("[Speech Recognition] END");
  };

  this.recognitionOnErrorHundler = function(e) {
    console.log("[Speech Recognition] ERROR");
    console.log(e);
  };

  this.stopAndRestart = function() {
    self.recognition.stop();
    self.initAndStartRecognition();
  };
};

HiSoundRecog.prototype.start = function() {
  this.initAndStartRecognition();
};

HiSoundRecog.prototype.stop = function() {
  this.recognition.stop();
};
