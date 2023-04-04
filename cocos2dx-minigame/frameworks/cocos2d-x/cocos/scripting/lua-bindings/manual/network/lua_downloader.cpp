/****************************************************************************
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
#include "lua_downloader.h"

#include "cocos2d.h"
#include "network/CCDownloader.h"
#include "lua_extensions.h"
#include <iostream>

#include <unordered_map>
#include <string>
#include <sstream>

using namespace cocos2d;
using namespace cocos2d::network;

class LuaDownloader : public cocos2d::Ref
{
public:
    Downloader* _downloader;
    lua_State* _state;
    LuaDownloader(lua_State *L, const DownloaderHints& hint)
    {
        _state = L;
        _downloader = new Downloader(hint);

        //register callback table
        lua_pushlightuserdata(_state, (void*)this);        //stack downloader, key[*downloader]
        lua_newtable(_state);                              //stack downloader, key[*downloader], {}
        lua_settable(_state, LUA_REGISTRYINDEX);           //stack downloaders
    };

    LuaDownloader(lua_State *L)
    {
        _state = L;
        _downloader = new Downloader();

        //register callback table
        lua_pushlightuserdata(_state, (void*)this);        //stack downloader, key[*downloader]
        lua_newtable(_state);                              //stack downloader, key[*downloader], {}
        lua_settable(_state, LUA_REGISTRYINDEX);           //stack downloaders
    };

    ~LuaDownloader()
    {
        //remove callback table
        lua_pushlightuserdata(_state, (void*)this);
        lua_pushnil(_state);
        lua_settable(_state, LUA_REGISTRYINDEX);
        if(_downloader) delete _downloader;
    };
};

static int get_field_int(lua_State *L, const char *field, int def)
{
    int ret = def;
    lua_pushstring(L, field);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1))
    {
        //luaL_error(L, "get_field_int: field '%s' no exists.", field);
        lua_pop(L, 1);
        return ret;
    }
    ret = (int)lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ret;
}

static std::string get_field_string(lua_State *L, const char *field, const char *def)
{
    std::string ret = def;
    lua_pushstring(L, field);
    lua_gettable(L, -2);
    if (lua_isnil(L, -1))
    {
        //CCLOGERROR("get_field_string: field '%s' no exists.", field);
        lua_pop(L, 1);
        return ret;
    }
    ret = std::string(lua_tostring(L, -1));
    lua_pop(L, 1);
    return ret;
}

static void set_field_string(lua_State *L, const char *field, const char *value)
{
    lua_pushstring(L, field);
    lua_pushstring(L, value);
    lua_settable(L, -3);
}

static LuaDownloader *checkDownloader(lua_State *L) {
    void *ud = luaL_checkudata(L, 1, "cc.Downloader");
    luaL_argcheck(L, ud != NULL, 1, "`Downloader' expected");
    return *(LuaDownloader **)ud;
}

static void pushTaskTable(lua_State *L, const DownloadTask &task)
{
    lua_newtable(L);
    set_field_string(L, "identifier", task.identifier.c_str());
    set_field_string(L, "requestURL", task.requestURL.c_str());
    set_field_string(L, "storagePath", task.storagePath.c_str());
}


static void saveCallback(lua_State *L, void *addr, const char *callbackName)
{
    //stack [fn]
    lua_pushlightuserdata(L, (void*)addr);          //stack fn, ud
    lua_gettable(L, LUA_REGISTRYINDEX);             //stack fn, callbacks_tb
    lua_pushstring(L, callbackName);                //stack fn, callbacks_tb, callbackName
    lua_pushvalue(L, -3);                           //stack fn, callbacks_tb, callbackName, fn 
    lua_settable(L, -3);                            //stack fn, callbacks_tb
    lua_pop(L, 2);                                  //stack 
}

static int getCallback(lua_State *L, void *addr, const char *callbackName)
{
    //stack []
    lua_pushlightuserdata(L, (void*)addr);          //stack ud
    lua_gettable(L, LUA_REGISTRYINDEX);             //stack callbacks_tb
    if (!lua_istable(L, -1))
    {
        return 0;
    }

    lua_pushstring(L, callbackName);                //stack callbacks_tb, callbackName
    lua_gettable(L, -2);                            //stack callbacks_tb, callbackfn
    lua_remove(L, -2);                              //stack callbackfn
    return lua_isfunction(L, -1) ? 1 : 0;
}

static int lua_downloader_new(lua_State *L)
{
    LuaDownloader *downloader = nullptr;
    int argc = lua_gettop(L) - 1;
    if (argc >= 1) {
        //parse DownloaderHints
        if (!lua_istable(L, -1)) {
            CCLOGERROR("cc.Downloader.new: first argument should be table if set");
            return 0;
        }
        DownloaderHints hints;
        hints.countOfMaxProcessingTasks = get_field_int(L, "countOfMaxProcessingTasks", 6);
        hints.timeoutInSeconds          = get_field_int(L, "timeoutInSeconds", 45);
        hints.tempFileNameSuffix        = get_field_string(L, "tempFileNameSuffix", ".tmp");

        void** ptr = (void**)lua_newuserdata(L, sizeof(void *));
        *ptr = downloader = new LuaDownloader(L, hints);
    }
    else
    {
        void** ptr = (void**)lua_newuserdata(L, sizeof(void *));
        *ptr = downloader = new LuaDownloader(L);
    }

    downloader->autorelease();
    downloader->retain();

    downloader->_downloader->setOnFileTaskSuccess([downloader, L](const DownloadTask &task) {
        int ret = getCallback(L, downloader, "setOnFileTaskSuccess"); //stack callbackfn
        if (ret)
        {
            pushTaskTable(L, task);                          //stack callbackfn, task
            if (lua_pcall(L, 1, 0, 0) != 0)
            {
                lua_pop(L, 1);                                // remove callback or nil
                CCLOGERROR("cc.Downloader.setOnFileTaskSuccess invoke callback error!");
                return;
            }
        }
        else {
            lua_pop(L, 1);                                   // remove callback or nil
        }
        downloader->release();
    });

    downloader->_downloader->setOnDataTaskSuccess([downloader, L](const DownloadTask &task, std::vector<unsigned char>& data) {
        int ret = getCallback(L, downloader, "setOnDataTaskSuccess"); //stack callbackfn
        if (ret)
        {
            pushTaskTable(L, task);                          //stack callbackfn, task
            lua_pushlstring (L, reinterpret_cast<char*>(data.data()), data.size()); //stack callbackfn, task, dataString
            if (lua_pcall(L, 2, 0, 0) != 0)                  //stack callbackfn
            {
                lua_pop(L, 1);                               // stack
                CCLOGERROR("cc.Downloader.setOnDataTaskSuccess invoke callback error!");
                return;
            }
        }
        else {
            lua_pop(L, 1);                                   // stack
        }
        downloader->release();
    });

    downloader->_downloader->setOnTaskProgress([downloader, L](const DownloadTask &task,
        int64_t bytesReceived,
        int64_t totalBytesReceived,
        int64_t totalBytesExpected) {
        int ret = getCallback(L, downloader, "setOnTaskProgress"); //stack callbackfn
        if (ret)
        {
            pushTaskTable(L, task);                          //stack callbackfn, task
            lua_pushnumber(L, bytesReceived);
            lua_pushnumber(L, totalBytesReceived);
            lua_pushnumber(L, totalBytesExpected);
            if (lua_pcall(L, 4, 0, 0) != 0)
            {
                lua_pop(L, 1);                                // remove callback or nil
                CCLOGERROR("cc.Downloader.setOnTaskProgress invoke callback error!");
                return;
            }
        }
        else {
            lua_pop(L, 1);                                   // remove callback or nil
        }
    });

    downloader->_downloader->setOnTaskError([downloader, L](const DownloadTask &task,
        int errorCode,
        int errorCodeInternal,
        const std::string& errorSt) {
        int ret = getCallback(L, downloader, "setOnTaskError");       //stack callbackfn
        if (ret)
        {
            pushTaskTable(L, task);                          //stack callbackfn, task
            lua_pushnumber(L, errorCode);
            lua_pushnumber(L, errorCodeInternal);
            lua_pushstring(L, errorSt.c_str());
            if (lua_pcall(L, 4, 0, 0) != 0)
            {
                lua_pop(L, 1);                                // remove callback or nil
                CCLOGERROR("cc.Downloader.setOnTaskError invoke callback error!");
                return;
            }
        }
        else {
            lua_pop(L, 1);                                   // remove callback or nil
        }
        downloader->release();
    });

    luaL_getmetatable(L, "cc.Downloader");              //stack  downloader, cc.Downloader
    lua_setmetatable(L, -2);                            //stack  downloader
    return 1;
}


static int lua_downloader_createDownloadDataTask(lua_State *L)
{
    LuaDownloader *d = checkDownloader(L);
    int argc = lua_gettop(L) - 1;
    std::string url = "";
    std::string identifier = "";

    if (argc == 0)
    {
        CCLOGERROR("cc.Downloader.createDownloadDataTask parameter error");
        return 0;
    }

    if (argc >= 1) url = lua_tostring(L, 2);
    if (argc >= 2) identifier = lua_tostring(L, 3);

    auto tsk = d->_downloader->createDownloadDataTask(url, identifier);
    pushTaskTable(L, *tsk);
    d->retain();
    return 1;
}

static int lua_downloader_createDownloadFileTask(lua_State *L)
{
    int argc = lua_gettop(L) - 1;
    LuaDownloader *d = checkDownloader(L);
    std::string url = "";
    std::string storagePath = "";
    std::string identifier = "";

    if (argc < 2)
    {
        CCLOGERROR("cc.Downloader.createDownloadFileTask parameter error!");
        return 0;
    }

    url = lua_tostring(L, 2);
    storagePath = lua_tostring(L, 3);
    if (argc > 2) identifier = lua_tostring(L, 4);

    auto tsk = d->_downloader->createDownloadFileTask(url, storagePath, identifier);
    pushTaskTable(L, *tsk);
    d->retain();
    return 1;
}

static int lua_downloader_setOnDataTaskSuccess(lua_State *L)
{
    int argc = lua_gettop(L) - 1;
    LuaDownloader *d = checkDownloader(L);
    if (argc != 1) {
        CCLOGERROR("cc.Downloader.setOnDataTaskSuccess parameter error!");
        return 0;
    }
    luaL_argcheck(L, lua_isfunction(L, 2), 2, "should be a function");
    saveCallback(L, d, "setOnDataTaskSuccess");
    return 0;
}

static int lua_downloader_setOnFileTaskSuccess(lua_State *L)
{
    int argc = lua_gettop(L) - 1;
    LuaDownloader *d = checkDownloader(L);
    if (argc != 1) {
        CCLOGERROR("cc.Downloader.setOnFileTaskSuccess parameter error!");
        return 0;
    }
    luaL_argcheck(L, lua_isfunction(L, 2), 2, "should be a function");
    saveCallback(L, d, "setOnFileTaskSuccess");

    return 0;
}

static int lua_downloader_setOnTaskProgress(lua_State *L)
{
    LuaDownloader *d = checkDownloader(L);
    int argc = lua_gettop(L) - 1;
    if (argc != 1) {
        CCLOGERROR("cc.Downloader.setOnTaskProgress parameter error!");
        return 0;
    }
    luaL_argcheck(L, lua_isfunction(L, 2), 2, "should be a function");
    saveCallback(L, d, "setOnTaskProgress");

    return 0;
}

static int lua_downloader_setOnTaskError(lua_State *L)
{
    LuaDownloader *d = checkDownloader(L);
    int argc = lua_gettop(L) - 1;
    if (argc != 1) {
        CCLOGERROR("cc.Downloader.setOnTaskError parameter error!");
        return 0;
    }
    luaL_argcheck(L, lua_isfunction(L, 2), 2, "should be a function");
    saveCallback(L, d, "setOnTaskError");

    return 0;
}


static int lua_downloader_cleanup(lua_State *L)
{
    LuaDownloader *d = checkDownloader(L);

    // Relase downloader
    // Downloader will still work until it finishes its ongoing tasks
    d->release();
    return 0;
}

static int lua_downloader_tostring(lua_State *L)
{
    lua_pushstring(L, "[cc.Downloader]");
    return 1;
}

static const struct luaL_Reg downloaderStaticFns[] = {
    { "new", lua_downloader_new }, 
    /* 
     * cocos2d::Downloader is not a subclass of cocos2d::Ref, 
     * `create()` is not provided.
     */
    //{ "create", lua_downloader_new },  
    { nullptr, nullptr }
    };


static const struct luaL_Reg downloaderMemberFns[] = {
    { "createDownloadDataTask", lua_downloader_createDownloadDataTask },
    { "createDownloadFileTask", lua_downloader_createDownloadFileTask },
    { "setOnFileTaskSuccess",   lua_downloader_setOnFileTaskSuccess },
    { "setOnDataTaskSuccess",   lua_downloader_setOnDataTaskSuccess },
    { "setOnTaskProgress",      lua_downloader_setOnTaskProgress },
    { "setOnTaskError",         lua_downloader_setOnTaskError },
    { "__gc",                   lua_downloader_cleanup },
    { "__tostring",             lua_downloader_tostring },
    { nullptr, nullptr }
};

int register_downloader(lua_State* L)
{
    int stackSize = lua_gettop(L);
    luaL_newmetatable(L, "cc.Downloader");  //stack metatable(cc.Downloader)
    lua_pushstring(L, "__index");           //stack metatable(*), __index
    lua_pushvalue(L, -2);                   //stack metatable(*), __index, metatable(*)
    lua_settable(L, -3);                    //stack metatable(*)
    luaL_register(L, nullptr, downloaderMemberFns);   //stack metatable(*)
    lua_pop(L, 1);                                      //stack *empty*
    luaL_register(L, "cc.Downloader", downloaderStaticFns);   //stack *empty*
    lua_pop(L, 1);
    assert(stackSize == lua_gettop(L));
    return 1;
}

