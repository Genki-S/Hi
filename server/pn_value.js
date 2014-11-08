var http = require('http');

module.exports = function(msg, callback) {
  var encodedMessage = encodeURIComponent(msg);
  var httpOptions = {
    hostname: 'localhost',
    port: 3000,
    path: '/api/v1/pn_value/' + encodedMessage
  };

  http.get(httpOptions, function(res) {
    var body = '';
    res.on('data', function(chunk) {
      body += chunk;
    });
    res.on('end', function() {
      var obj = JSON.parse(body);
      callback(obj.pn_value);
    });
  }).on('error', function(e) {
    console.log("Got error: ", e);
  });
};
