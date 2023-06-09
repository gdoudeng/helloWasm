
--------------------------------
-- @module Place
-- @extend ActionInstant
-- @parent_module cc

--------------------------------
--  Initializes a Place action with a position 
-- @function [parent=#Place] initWithPosition 
-- @param self
-- @param #vec2_table pos
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Creates a Place action with a position.<br>
-- param pos  A certain position.<br>
-- return  An autoreleased Place object.
-- @function [parent=#Place] create 
-- @param self
-- @param #vec2_table pos
-- @return Place#Place ret (return value: cc.Place)
        
--------------------------------
-- 
-- @function [parent=#Place] clone 
-- @param self
-- @return Place#Place ret (return value: cc.Place)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#Place] update 
-- @param self
-- @param #float time
-- @return Place#Place self (return value: cc.Place)
        
--------------------------------
-- 
-- @function [parent=#Place] reverse 
-- @param self
-- @return Place#Place ret (return value: cc.Place)
        
--------------------------------
-- 
-- @function [parent=#Place] Place 
-- @param self
-- @return Place#Place self (return value: cc.Place)
        
return nil
