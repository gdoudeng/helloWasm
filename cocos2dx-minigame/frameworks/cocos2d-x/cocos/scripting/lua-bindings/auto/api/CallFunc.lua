
--------------------------------
-- @module CallFunc
-- @extend ActionInstant
-- @parent_module cc

--------------------------------
--  Executes the callback.
-- @function [parent=#CallFunc] execute 
-- @param self
-- @return CallFunc#CallFunc self (return value: cc.CallFunc)
        
--------------------------------
--  Get the selector target.<br>
-- return The selector target.
-- @function [parent=#CallFunc] getTargetCallback 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
--  Set the selector target.<br>
-- param sel The selector target.
-- @function [parent=#CallFunc] setTargetCallback 
-- @param self
-- @param #cc.Ref sel
-- @return CallFunc#CallFunc self (return value: cc.CallFunc)
        
--------------------------------
-- 
-- @function [parent=#CallFunc] clone 
-- @param self
-- @return CallFunc#CallFunc ret (return value: cc.CallFunc)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#CallFunc] update 
-- @param self
-- @param #float time
-- @return CallFunc#CallFunc self (return value: cc.CallFunc)
        
--------------------------------
-- 
-- @function [parent=#CallFunc] reverse 
-- @param self
-- @return CallFunc#CallFunc ret (return value: cc.CallFunc)
        
--------------------------------
-- 
-- @function [parent=#CallFunc] CallFunc 
-- @param self
-- @return CallFunc#CallFunc self (return value: cc.CallFunc)
        
return nil
