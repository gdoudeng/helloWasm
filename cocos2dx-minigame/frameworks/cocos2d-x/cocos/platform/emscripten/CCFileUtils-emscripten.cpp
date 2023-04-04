/****************************************************************************
Copyright (c) 2011      Laschweinski
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_EMSCRIPTEN

#include "platform/emscripten/CCFileUtils-emscripten.h"
#include "platform/emscripten/CCApplication-emscripten.h"
#include "platform/CCCommon.h"
#include "base/ccMacros.h"
#include "base/ccUTF8.h"
#include <unistd.h>

using namespace std;

NS_CC_BEGIN

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsEmscripten();
        if(!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = nullptr;
          CCLOG("ERROR: Could not init CCFileUtilsEmscripten");
        }
    }
    return s_sharedFileUtils;
}

FileUtilsEmscripten::FileUtilsEmscripten()
{}

bool FileUtilsEmscripten::init()
{
    _defaultResRootPath = "/";
    return FileUtils::init();
}

string FileUtilsEmscripten::getWritablePath() const
{
    return "/cocos2dxWritablePath/";
}

bool FileUtilsEmscripten::isFileExistInternal(const std::string& strFilePath) const
{
    if (strFilePath.empty())
    {
        return false;
    }

    std::string strPath = strFilePath;
    if (strPath[0] != '/')
    { // Not absolute path, add the default root path at the beginning.
        if (strPath.find(_defaultResRootPath) != 0)
        {// Didn't find "assets/" at the beginning of the path, adding it.
            strPath.insert(0, _defaultResRootPath);
        }
    }

    return access(strPath.c_str(), F_OK) != -1 ? true : false;
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
