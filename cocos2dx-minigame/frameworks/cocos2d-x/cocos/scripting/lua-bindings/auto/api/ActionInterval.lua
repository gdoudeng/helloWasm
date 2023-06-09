
--------------------------------
-- @module ActionInterval
-- @extend FiniteTimeAction
-- @parent_module cc

--------------------------------
--  Gets the amplitude rate, extension in GridAction<br>
-- return  The amplitude rate.
-- @function [parent=#ActionInterval] getAmplitudeRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  initializes the action 
-- @function [parent=#ActionInterval] initWithDuration 
-- @param self
-- @param #float d
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Sets the amplitude rate, extension in GridAction<br>
-- param amp   The amplitude rate.
-- @function [parent=#ActionInterval] setAmplitudeRate 
-- @param self
-- @param #float amp
-- @return ActionInterval#ActionInterval self (return value: cc.ActionInterval)
        
--------------------------------
--  How many seconds had elapsed since the actions started to run.<br>
-- return The seconds had elapsed since the actions started to run.
-- @function [parent=#ActionInterval] getElapsed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ActionInterval] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return ActionInterval#ActionInterval self (return value: cc.ActionInterval)
        
--------------------------------
-- param dt in seconds
-- @function [parent=#ActionInterval] step 
-- @param self
-- @param #float dt
-- @return ActionInterval#ActionInterval self (return value: cc.ActionInterval)
        
--------------------------------
-- 
-- @function [parent=#ActionInterval] clone 
-- @param self
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
-- 
-- @function [parent=#ActionInterval] reverse 
-- @param self
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
-- 
-- @function [parent=#ActionInterval] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
