// this is how we will require our module
const m = require('./editor-version')

const currVersion = m.getUnityVersion('C:\\Program Files\\Unity\\Editor\\Unity.exe');
console.log(`Version: ${currVersion}`);
const nextVersion = m.getUnityVersion('C:\\Program Files\\Unity\\Editor\\Unity.exe', (error, version) => {
  console.log(`Version: ${version}`);
});
console.log(`nextVersion: ${nextVersion}`);
console.log('done');
