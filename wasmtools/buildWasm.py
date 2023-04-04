# -*- coding: utf-8 -*-
import os, sys, time, shutil, hashlib, json, re

#cmd

print(sys.argv)
cur_dir = os.getcwd()
print(cur_dir)

# 修改工程名
project_name = "cocos2dx-minigame"

#判断是否传入参数
if len(sys.argv)<2:
	print("please input cmd(release, debug)!!!")
	exit(0)

brExePath = ".\\brotli.exe"
wasmFile = "..\\{}\\emscripten-build\\bin\\{}\\{}.wasm".format(project_name, project_name, project_name)
dataFile = "..\\{}\\emscripten-build\\bin\\\{}\\\{}.data".format(project_name, project_name, project_name)
brWasmFile = "..\\{}\\emscripten-build\\bin\\\{}\\\{}.wasm.br".format(project_name, project_name, project_name)

def cmd_help():
	
	pass

def cmd_releaseBuild():
	clientDir = cur_dir + "\\..\\{}".format(project_name)
	os.chdir(clientDir)

	# clean dir
	binDir = cur_dir + "\\..\\{}\\emscripten-build\\bin\\{}\\".format(project_name, project_name)
	cleanBinDir = "del /Q " + binDir + "*"
	print(cleanBinDir)
	os.system(cleanBinDir)

	cmd = "cocos compile -p emscripten -m release"
	os.system(cmd)
	pass

def cmd_debugBuild():
	pass

def cmd_compress():
	os.chdir(cur_dir)

	if os.path.exists(brWasmFile):
		os.remove(brWasmFile)
	
	cmd = "{0} {1}".format(brExePath, wasmFile)
	print(cmd)
	os.system(cmd)
	pass

def cmd_copy():
	os.chdir(cur_dir)
	
	targetWasmDir = "..\\minigame\\miniprogram\\wasm\\"
	targetWebRootDir = "..\\webroot\\"

	# 删除旧的wasm文件
	for root, dirs, files in os.walk(targetWasmDir):
		for f in files:
			if f.endswith(".br"):
				fpath = os.path.join(root, f)
				os.remove(fpath)
	# 删除旧的data文件
	for root, dirs, files in os.walk(targetWebRootDir):
		for f in files:
			if f.endswith(".data.txt"):
				fpath = os.path.join(root, f)
				os.remove(fpath)

	# wasmFile
	wasmFileMd5 = hashlib.md5(open(brWasmFile, "rb").read()).hexdigest()[0:15]
	targetWasmName = ("{}-" + wasmFileMd5 + ".wasm.br").format(project_name)
	targetWasmPath = targetWasmDir + targetWasmName
	shutil.copyfile(brWasmFile, targetWasmPath)

	dataFileMd5 = hashlib.md5(open(dataFile, "rb").read()).hexdigest()[0:15]
	targetDataName = ("{}-" + dataFileMd5 + ".data.txt").format(project_name)
	targetDataPath = targetWebRootDir + targetDataName
	shutil.copyfile(dataFile, targetDataPath)

	# transform js
	os.system("python ./transformProgram.py")
			
	# 写入json信息
	hashInfo = "const WasmFileName = \"{0}\"; const DataFileName = \"{1}\"; export {{WasmFileName, DataFileName}}".format(targetWasmName, targetDataName)

	with open("..\\minigame\\miniprogram\\wasm\\wasmHash.js", "w") as f:
		f.write(hashInfo)

	pass

if __name__ == '__main__':
	target = sys.argv[1]
	print("cmd is:", target)
	if target == "release":
		cmd_releaseBuild()

		cmd_compress()

		cmd_copy()
		pass
