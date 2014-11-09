var sentiment = require('sentiment');

module.exports = function(msg, callback) {
  var result = sentiment(msg);
  // convert the value between -1 to 1
  var pnValue = result.comparative / 5.0
  callback(pnValue);
};
