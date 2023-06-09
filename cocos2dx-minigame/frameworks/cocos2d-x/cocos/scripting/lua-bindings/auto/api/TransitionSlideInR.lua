
--------------------------------
-- @module TransitionSlideInR
-- @extend TransitionSlideInL
-- @parent_module cc

--------------------------------
--  Creates a transition with duration and incoming scene.<br>
-- param t Duration time, in seconds.<br>
-- param scene A given scene.<br>
-- return A autoreleased TransitionSlideInR object.
-- @function [parent=#TransitionSlideInR] create 
-- @param self
-- @param #float t
-- @param #cc.Scene scene
-- @return TransitionSlideInR#TransitionSlideInR ret (return value: cc.TransitionSlideInR)
        
--------------------------------
--  Returns the action that will be performed by the incoming and outgoing scene. 
-- @function [parent=#TransitionSlideInR] action 
-- @param self
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
-- 
-- @function [parent=#TransitionSlideInR] TransitionSlideInR 
-- @param self
-- @return TransitionSlideInR#TransitionSlideInR self (return value: cc.TransitionSlideInR)
        
return nil
