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

/**
 * @author cesarpachon
 */
#include <cstring>
#include <cstdint>
#include "audio/emscripten/AudioEngine-emscripten.h"

#include "platform/CCFileUtils.h"

using namespace cocos2d;
using namespace cocos2d::experimental;

AudioEngineImpl * g_AudioEngineImpl = nullptr;

void channelCallback(int channel)
{
    g_AudioEngineImpl->onSoundFinished(channel);
}

AudioEngineImpl::AudioEngineImpl()
{
}

AudioEngineImpl::~AudioEngineImpl()
{
    while(Mix_Init(0))
    {
        Mix_Quit();
    }
    Mix_CloseAudio();
}

bool AudioEngineImpl::init()
{
    mapChannelInfo.clear();
    mapSound.clear();

    g_AudioEngineImpl = this;
    SDL_Init(SDL_INIT_AUDIO);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    int ret = Mix_OpenAudio(0, 0, 0, 0);
    CC_ASSERT(ret == 0);
    Mix_AllocateChannels(MAX_AUDIOINSTANCES);
    Mix_ChannelFinished(channelCallback);
    return true;
}

int AudioEngineImpl::play2d(const std::string &fileFullPath, bool loop, float volume)
{
    int id = preload(fileFullPath, nullptr);
    if (id >= 0) {
        mapChannelInfo[id].loop = loop;
        // channel is null here. Don't dereference it. It's only set in resume(id).
        //mapChannelInfo[id].channel->setPaused(true);
        mapChannelInfo[id].volume = volume;
        AudioEngine::_audioIDInfoMap[id].state = AudioEngine::AudioState::PAUSED;
        resume(id);
    }
    return id;
}

void AudioEngineImpl::setVolume(int audioID, float volume)
{
    try {
        volume = volume > 1.0 ? 1.0 : volume;
        volume = volume < 0.0 ? 0.0 : volume;
        Mix_Volume(mapChannelInfo[audioID].channel, volume * MIX_MAX_VOLUME);
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::setVolume: invalid audioID: %d\n", audioID);
    }
}

void AudioEngineImpl::setLoop(int audioID, bool loop)
{
    try {
        mapChannelInfo[audioID].loop = loop;
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::setLoop: invalid audioID: %d\n", audioID);
    }
}

bool AudioEngineImpl::pause(int audioID)
{
    try {
        Mix_Pause(mapChannelInfo[audioID].channel);
        AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PAUSED;
        return true;
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::pause: invalid audioID: %d\n", audioID);
        return false;
    }
}

bool AudioEngineImpl::resume(int audioID)
{
    try {
        if (mapChannelInfo[audioID].channel < 0) {
            int channel = Mix_PlayChannel(-1, mapChannelInfo[audioID].sound, mapChannelInfo[audioID].loop ? -1 : 0);
            if(channel < 0) {
                return false;
            }
            mapChannelInfo[audioID].channel = channel;

            float volume = mapChannelInfo[audioID].volume;
            volume = volume > 1.0 ? 1.0 : volume;
            volume = volume < 0.0 ? 0.0 : volume;
            Mix_Volume(channel, volume * MIX_MAX_VOLUME);
        }else{
            Mix_Resume(mapChannelInfo[audioID].channel);
        }

        AudioEngine::_audioIDInfoMap[audioID].state = AudioEngine::AudioState::PLAYING;

        return true;
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::resume: invalid audioID: %d\n", audioID);
        return false;
    }
}

bool AudioEngineImpl::stop(int audioID)
{
    try {
        if(mapChannelInfo[audioID].channel >= 0) {
            Mix_HaltChannel(mapChannelInfo[audioID].channel);
            mapChannelInfo[audioID].channel = -1;
        }
        return true;
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::stop: invalid audioID: %d\n", audioID);
        return false;
    }
}

void AudioEngineImpl::stopAll()
{
    for (auto& it : mapChannelInfo) {
        ChannelInfo & audioRef = it.second;
        if(audioRef.channel >= 0) {
            audioRef.channel = -1;
        }
    }

    Mix_HaltChannel(-1);
}

float AudioEngineImpl::getDuration(int audioID)
{
    // TODO: should be able to implement with embeded js code
    return AudioEngine::TIME_UNKNOWN;
}

float AudioEngineImpl::getCurrentTime(int audioID)
{
    // TODO: should be able to implement with embeded js code
    return AudioEngine::TIME_UNKNOWN;
}

bool AudioEngineImpl::setCurrentTime(int audioID, float time)
{
    // TODO: should be able to implement with embeded js code
    return false;
}

void AudioEngineImpl::setFinishCallback(int audioID, const std::function<void (int, const std::string &)> &callback)
{
    try {
        mapChannelInfo[audioID].callback = callback;
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::setFinishCallback: invalid audioID: %d\n", audioID);
    }
}

void AudioEngineImpl::onSoundFinished(int channel)
{
    int id = 0;
    try {
        for (auto& it : mapChannelInfo) {
            ChannelInfo & audioRef = it.second;
            if(audioRef.channel == channel) {
                if (audioRef.callback) {
                    audioRef.callback(audioRef.id, audioRef.path);
                }
                audioRef.channel = -1;
                break;
            }
        }
    }
    catch (const std::out_of_range& oor) {
        printf("AudioEngineImpl::onSoundFinished: invalid audioID: %d\n", id);
    }
}

void AudioEngineImpl::uncache(const std::string& path)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    std::map<std::string, Mix_Chunk *>::const_iterator it = mapSound.find(fullPath);
    if (it!=mapSound.end()) {
        Mix_Chunk * sound = it->second;
        if (sound) {
            Mix_FreeChunk(sound);
        }
        mapSound.erase(it);
    }
    mapId.erase(path);
}

void AudioEngineImpl::uncacheAll()
{
    for (const auto& it : mapSound) {
        auto sound = it.second;
        if (sound) {
            Mix_FreeChunk(sound);
        }
    }
    mapSound.clear();
    mapId.clear();
}

int AudioEngineImpl::preload(const std::string& filePath, const std::function<void(bool isSuccess)>& callback)
{
    Mix_Chunk * sound = findSound(filePath);
    if (!sound) {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(filePath);
        sound = Mix_LoadWAV(fullPath.c_str());
        mapSound[fullPath] = sound;
    }

    int id = static_cast<int>(mapChannelInfo.size()) + 1;
    // std::map::insert returns std::pair<iter, bool>
    auto channelInfoIter = mapId.insert({filePath, id});
    id = channelInfoIter.first->second;

    auto& chanelInfo = mapChannelInfo[id];
    chanelInfo.sound = sound;
    chanelInfo.id = id;
    chanelInfo.channel = -1;
    chanelInfo.callback = nullptr;
    chanelInfo.path = filePath;
    
    if (callback) {
        callback(true);
    }
    return id;
}


Mix_Chunk * AudioEngineImpl::findSound(const std::string &path)
{
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
    std::map<std::string, Mix_Chunk *>::const_iterator it = mapSound.find(fullPath);
    return (it != mapSound.end()) ? (it->second) : nullptr;
}