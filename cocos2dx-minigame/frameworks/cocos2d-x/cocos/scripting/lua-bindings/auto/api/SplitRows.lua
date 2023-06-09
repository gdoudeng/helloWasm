
--------------------------------
-- @module SplitRows
-- @extend TiledGrid3DAction
-- @parent_module cc

--------------------------------
-- brief Initializes the action with the number rows and the duration.<br>
-- param duration Specify the duration of the SplitRows action. It's a value in seconds.<br>
-- param rows Specify the rows count should be split.<br>
-- return If the creation success, return true; otherwise, return false.
-- @function [parent=#SplitRows] initWithDuration 
-- @param self
-- @param #float duration
-- @param #unsigned int rows
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Create the action with the number of rows and the duration.<br>
-- param duration Specify the duration of the SplitRows action. It's a value in seconds.<br>
-- param rows Specify the rows count should be split.<br>
-- return If the creation success, return a pointer of SplitRows action; otherwise, return nil.
-- @function [parent=#SplitRows] create 
-- @param self
-- @param #float duration
-- @param #unsigned int rows
-- @return SplitRows#SplitRows ret (return value: cc.SplitRows)
        
--------------------------------
-- 
-- @function [parent=#SplitRows] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return SplitRows#SplitRows self (return value: cc.SplitRows)
        
--------------------------------
-- 
-- @function [parent=#SplitRows] clone 
-- @param self
-- @return SplitRows#SplitRows ret (return value: cc.SplitRows)
        
--------------------------------
-- 
-- @function [parent=#SplitRows] update 
-- @param self
-- @param #float time
-- @return SplitRows#SplitRows self (return value: cc.SplitRows)
        
--------------------------------
-- 
-- @function [parent=#SplitRows] SplitRows 
-- @param self
-- @return SplitRows#SplitRows self (return value: cc.SplitRows)
        
return nil
