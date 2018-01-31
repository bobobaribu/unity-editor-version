var binding = require('./build/Release/editorVersion.node');

exports.getUnityVersion = function(path, cb) {
    if (cb) {
      return binding.GetUnityVersion(path, cb);
    }
    return binding.GetUnityVersion(path);
}