经过一段时间的实践和测试，我已经成功地将cocos2dx游戏转换为微信小游戏，并在这个过程中遇到了不少问题。现在，我想分享我的经验并开源我的代码，以便更多的人能够参与进来，共同协作改进，填补漏洞。希望这个仓库能够引起大家的关注，为cocos2dx转换为微信小游戏的过程提供有益的帮助。

目前只支持cocos2dx 3.17.2版本的转换,下面是环境搭建流程：
1. 安装emsdk，然后切换到2.0.34版本

2. 安装指定版本cocos2dx 
https://github.com/WuJiayiSH/cocos2d-x

3. 编译 python3 
wasmtools/buildWasm.py release

4. 新建一个资源服务器，并指向webroot路径，然后使用微信开发者工具打开工程，并修改 js/libs/cocosPlugin.js里面的Module.CNDUrl变量.

为了方便大家交流，可以加qq群: 15973429 