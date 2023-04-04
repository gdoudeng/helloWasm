import * as WashHashInfo from "../../wasm/wasmHash"

GameGlobal.cocosModule = GameGlobal.cocosModule || {};
var Module = GameGlobal.cocosModule

Module.IsWxGame = true

Module.CNDUrl = "https://local.newasm.com:8080/hellowasm/webroot/"

// cache canvas
Module["canvas"] = Module["canvas"] || GameGlobal.canvas

// hack1
if (window.WebAssembly == undefined) {
  window.WebAssembly = WXWebAssembly
}
if (window.location.pathname == undefined) {
  window.location.pathname = window.location.href
}

//fix window.alert
if (window.alert == undefined) {
  window.alert = console.log
}

Module["locateFile"] = function (path, scriptDirectory) {
  console.log("get path:", path, scriptDirectory)
  if (path.indexOf(".wasm") > 0) {
    return "/wasm/" + WashHashInfo.WasmFileName
  }
  if (path.indexOf(".data") > 0) {
    return Module.CNDUrl + WashHashInfo.DataFileName
  }
  if (path.indexOf(".metadata") > 0) {
    return Module.CNDUrl + path
  }
  return scriptDirectory + path
}

// update mouse xy
Module["customMouseButtonDown"] = function (Browser, GLFW, event) {
  GLFW.onMousemove(event)
}

Module["customMouseMove"] = function (Browser, GLFW, event) {
  var rect = Module["canvas"].getBoundingClientRect();
  var cw = Module["canvas"].width;
  var ch = Module["canvas"].height;

  var touch = event.touches[0];
  var x = touch.pageX - rect.left;
  var y = touch.pageY - rect.top;
  x = x * (cw / rect.width);
  y = y * (ch / rect.height);
  Browser.mouseMovementX = x - Browser.mouseX;
  Browser.mouseMovementY = y - Browser.mouseY;
  Browser.mouseX = x;
  Browser.mouseY = y
}

Module["print"] = function(args){
  console.log(args)
}

wx.onKeyboardConfirm((data) => {
  let {value} = data
  var onInputFinishCB = Module.cwrap('cocos_editbox_finished', 'number', ['number']); // argument types
  var newText = Module["allocateUTF8"](value)
  onInputFinishCB(newText)
  wx.hideKeyboard()
});

Module['customOpenKeyboard'] = function(flag, newText, posx, posy, width, height){
  wx.showKeyboard({
    defaultValue: newText,
    maxLength: 256,
    multiple: false,
    confirmHold: true
  });
}