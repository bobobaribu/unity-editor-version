// this is how we will require our module
const m = require('./')

const currVersion = new m.GetUnityVersion('D:\\unity5_6\\Editor\\Unity.exe');
console.log(currVersion);
