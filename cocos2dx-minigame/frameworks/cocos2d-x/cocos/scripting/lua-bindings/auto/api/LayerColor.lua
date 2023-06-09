
--------------------------------
-- @module LayerColor
-- @extend Layer,BlendProtocol
-- @parent_module cc

--------------------------------
--  Change width and height in Points.<br>
-- param w The width of layer.<br>
-- param h The Height of layer.<br>
-- since v0.8
-- @function [parent=#LayerColor] changeWidthAndHeight 
-- @param self
-- @param #float w
-- @param #float h
-- @return LayerColor#LayerColor self (return value: cc.LayerColor)
        
--------------------------------
--  BlendFunction. Conforms to BlendProtocol protocol <br>
-- lua NA
-- @function [parent=#LayerColor] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- code<br>
-- When this function bound into js or lua,the parameter will be changed<br>
-- In js: var setBlendFunc(var src, var dst)<br>
-- In lua: local setBlendFunc(local src, local dst)<br>
-- endcode
-- @function [parent=#LayerColor] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return LayerColor#LayerColor self (return value: cc.LayerColor)
        
--------------------------------
--  Change width in Points.<br>
-- param w The width of layer.
-- @function [parent=#LayerColor] changeWidth 
-- @param self
-- @param #float w
-- @return LayerColor#LayerColor self (return value: cc.LayerColor)
        
--------------------------------
-- @overload self, color4b_table         
-- @overload self, color4b_table, float, float         
-- @function [parent=#LayerColor] initWithColor
-- @param self
-- @param #color4b_table color
-- @param #float width
-- @param #float height
-- @return bool#bool ret (return value: bool)

--------------------------------
--  Change height in Points.<br>
-- param h The height of layer.
-- @function [parent=#LayerColor] changeHeight 
-- @param self
-- @param #float h
-- @return LayerColor#LayerColor self (return value: cc.LayerColor)
        
--------------------------------
-- @overload self, color4b_table, float, float         
-- @overload self         
-- @overload self, color4b_table         
-- @function [parent=#LayerColor] create
-- @param self
-- @param #color4b_table color
-- @param #float width
-- @param #float height
-- @return LayerColor#LayerColor ret (return value: cc.LayerColor)

--------------------------------
-- 
-- @function [parent=#LayerColor] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return LayerColor#LayerColor self (return value: cc.LayerColor)
        
--------------------------------
-- 
-- @function [parent=#LayerColor] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#LayerColor] getDescription 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#LayerColor] setContentSize 
-- @param self
-- @param #size_table var
-- @return LayerColor#LayerColor self (return value: cc.LayerColor)
        
--------------------------------
-- 
-- @function [parent=#LayerColor] LayerColor 
-- @param self
-- @return LayerColor#LayerColor self (return value: cc.LayerColor)
        
return nil
