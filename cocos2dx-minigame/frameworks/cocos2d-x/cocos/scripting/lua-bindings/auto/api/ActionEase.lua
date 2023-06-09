
--------------------------------
-- @module ActionEase
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- brief Initializes the action.<br>
-- return Return true when the initialization success, otherwise return false.
-- @function [parent=#ActionEase] initWithAction 
-- @param self
-- @param #cc.ActionInterval action
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Get the pointer of the inner action.<br>
-- return The pointer of the inner action.
-- @function [parent=#ActionEase] getInnerAction 
-- @param self
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
-- 
-- @function [parent=#ActionEase] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return ActionEase#ActionEase self (return value: cc.ActionEase)
        
--------------------------------
-- 
-- @function [parent=#ActionEase] stop 
-- @param self
-- @return ActionEase#ActionEase self (return value: cc.ActionEase)
        
--------------------------------
-- 
-- @function [parent=#ActionEase] update 
-- @param self
-- @param #float time
-- @return ActionEase#ActionEase self (return value: cc.ActionEase)
        
return nil
