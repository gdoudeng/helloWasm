
--------------------------------
-- @module TextureCache
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Reload texture from the image file.<br>
-- If the file image hasn't loaded before, load it.<br>
-- Otherwise the texture will be reloaded from the file image.<br>
-- param fileName It's the related/absolute path of the file image.<br>
-- return True if the reloading is succeed, otherwise return false.
-- @function [parent=#TextureCache] reloadTexture 
-- @param self
-- @param #string fileName
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Unbind all bound image asynchronous load callbacks.<br>
-- since v3.1
-- @function [parent=#TextureCache] unbindAllImageAsync 
-- @param self
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
--  Deletes a texture from the cache given a its key name.<br>
-- param key It's the related/absolute path of the file image.<br>
-- since v0.99.4
-- @function [parent=#TextureCache] removeTextureForKey 
-- @param self
-- @param #string key
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
--  Purges the dictionary of loaded textures.<br>
-- Call this method if you receive the "Memory Warning".<br>
-- In the short term: it will free some resources preventing your app from being killed.<br>
-- In the medium term: it will allocate more resources.<br>
-- In the long term: it will be the same.
-- @function [parent=#TextureCache] removeAllTextures 
-- @param self
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#TextureCache] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Output to CCLOG the current contents of this TextureCache.<br>
-- This will attempt to calculate the size of each texture, and the total texture memory in use.<br>
-- since v1.0
-- @function [parent=#TextureCache] getCachedTextureInfo 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- @overload self, cc.Image, string         
-- @overload self, string         
-- @function [parent=#TextureCache] addImage
-- @param self
-- @param #cc.Image image
-- @param #string key
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)

--------------------------------
--  Unbind a specified bound image asynchronous callback.<br>
-- In the case an object who was bound to an image asynchronous callback was destroyed before the callback is invoked,<br>
-- the object always need to unbind this callback manually.<br>
-- param filename It's the related/absolute path of the file image.<br>
-- since v3.1
-- @function [parent=#TextureCache] unbindImageAsync 
-- @param self
-- @param #string filename
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
--  Returns an already created texture. Returns nil if the texture doesn't exist.<br>
-- param key It's the related/absolute path of the file image.<br>
-- since v0.99.5
-- @function [parent=#TextureCache] getTextureForKey 
-- @param self
-- @param #string key
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- Get the file path of the texture<br>
-- param texture A Texture2D object pointer.<br>
-- return The full path of the file.
-- @function [parent=#TextureCache] getTextureFilePath 
-- @param self
-- @param #cc.Texture2D texture
-- @return string#string ret (return value: string)
        
--------------------------------
--  Reload texture from a new file.<br>
-- This function is mainly for editor, won't suggest use it in game for performance reason.<br>
-- param srcName Original texture file name.<br>
-- param dstName New texture file name.<br>
-- since v3.10
-- @function [parent=#TextureCache] renameTextureWithKey 
-- @param self
-- @param #string srcName
-- @param #string dstName
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
--  Removes unused textures.<br>
-- Textures that have a retain count of 1 will be deleted.<br>
-- It is convenient to call this method after when starting a new Scene.<br>
-- since v0.8
-- @function [parent=#TextureCache] removeUnusedTextures 
-- @param self
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
--  Deletes a texture from the cache given a texture.
-- @function [parent=#TextureCache] removeTexture 
-- @param self
-- @param #cc.Texture2D texture
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
-- Called by director, please do not called outside.
-- @function [parent=#TextureCache] waitForQuit 
-- @param self
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
-- 
-- @function [parent=#TextureCache] setETC1AlphaFileSuffix 
-- @param self
-- @param #string suffix
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
--------------------------------
-- 
-- @function [parent=#TextureCache] getETC1AlphaFileSuffix 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- js ctor
-- @function [parent=#TextureCache] TextureCache 
-- @param self
-- @return TextureCache#TextureCache self (return value: cc.TextureCache)
        
return nil
