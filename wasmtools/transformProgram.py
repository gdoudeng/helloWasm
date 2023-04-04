#encoding:utf-8

import os
import sys
import getopt
import shutil
import subprocess
import re
import multiprocessing

# 修改工程名
project_name = "cocos2dx-minigame"

inputPath = "../{}/emscripten-build/bin/{}/{}.js".format(project_name, project_name, project_name)
outPath = "../minigame/miniprogram/wasm/{}.js".format(project_name)

rules = {
	"var Module=typeof Module!==\"undefined\"?Module:{};"
		: "var Module=GameGlobal.cocosModule||{};",

	"readAsync(wasmBinaryFile,function(response){resolve(new Uint8Array(response))},reject)"
		: "resolve(wasmBinaryFile)",

	"return ver"
		: "if(Module.IsWxGame)return gl;return ver",

	"canvas.style.removeProperty("
		: "if(canvas.style.removeProperty)canvas.style.removeProperty(",

	"canvas.style.setProperty("
		: "if(canvas.style.setProperty)canvas.style.setProperty(",

	"GLFW.onMouseButtonChanged(event,1)" 
		: "if(Module[\"customMouseButtonDown\"])Module[\"customMouseButtonDown\"](Browser,GLFW,event);GLFW.onMouseButtonChanged(event,1)",

	"onMousemove:function(event){if(!GLFW.active)return;Browser.calculateMouseEvent(event);"
		: "onMousemove:function(event){if(!GLFW.active)return;Browser.calculateMouseEvent(event);if(Module[\"customMouseMove\"])Module[\"customMouseMove\"](Browser,GLFW,event);",

	"{GLctx[\"viewport\"](x0,x1,x2,x3)}" 
		: "{if(x0<0||x1<0||x2<0||x3<0)return;GLctx[\"viewport\"](x0,x1,x2,x3)}",

	"function allocateUTF8OnStack"
		: "Module[\"allocateUTF8\"]=allocateUTF8;function allocateUTF8OnStack"
}

rulesDebug = {
	"var Module = typeof Module !== 'undefined' ? Module : {};"
		: "var Module = GameGlobal.cocosModule || {};",

	"readAsync(wasmBinaryFile, function(response) { resolve(new Uint8Array(/** @type{!ArrayBuffer} */(response))) }, reject)"
		: "resolve(wasmBinaryFile)",

	"return ((ver == 'webgl')"
		: "if(Module.IsWxGame) return gl;\n\t\t\t\t\t\treturn ((ver == 'webgl')",

	"canvas.style.removeProperty("
		: "if(canvas.style.removeProperty) canvas.style.removeProperty(",

	"canvas.style.setProperty("
		: "if(canvas.style.setProperty) canvas.style.setProperty(",

	"GLFW.onMouseButtonChanged(event, 1)"
		: "if(Module[\"customMouseButtonDown\"]) Module[\"customMouseButtonDown\"](Browser,GLFW,event);\n\t\t\t\tGLFW.onMouseButtonChanged(event,1)",

	"if (event.target != Module[\"canvas\"] || !GLFW.active.cursorPosFunc) return;"
		: "if (Module[\"customMouseMove\"]) Module[\"customMouseMove\"](Browser, GLFW, event);\n\t\t\t\tif (event.target != Module[\"canvas\"] || !GLFW.active.cursorPosFunc) return;",

	"GLctx['viewport'](x0, x1, x2, x3)"
		: "if(x0<0||x1<0||x2<0||x3<0)return;GLctx['viewport'](x0,x1,x2,x3)",
}

if __name__ == "__main__":

	real_file_path = os.path.dirname(__file__)

	replaceRules = rules

	(opts, args) = getopt.getopt(sys.argv[1:], "d")
	for opt, value in opts:
		if opt == "-d":
			replaceRules = rulesDebug

	file_object = open(os.path.join(real_file_path, inputPath))
try:
	text = file_object.read()
finally:  
	file_object.close( )

	newText = text

	for key in replaceRules:
		newText = newText.replace(key, replaceRules[key])

	file = open(os.path.join(real_file_path, outPath), 'a')
	file.truncate(0)
	file.write(newText)
	file.close()
