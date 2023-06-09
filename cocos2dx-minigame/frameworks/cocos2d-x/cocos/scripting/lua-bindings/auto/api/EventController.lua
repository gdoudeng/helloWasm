
--------------------------------
-- @module EventController
-- @extend Event
-- @parent_module cc

--------------------------------
--  Gets the event type of the controller.<br>
-- return The event type of the controller.
-- @function [parent=#EventController] getControllerEventType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Sets the connect status.<br>
-- param True if it's connected.
-- @function [parent=#EventController] setConnectStatus 
-- @param self
-- @param #bool isConnected
-- @return EventController#EventController self (return value: cc.EventController)
        
--------------------------------
--  Gets the connect status.<br>
-- return True if it's connected.
-- @function [parent=#EventController] isConnected 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#EventController] setKeyCode 
-- @param self
-- @param #int keyCode
-- @return EventController#EventController self (return value: cc.EventController)
        
--------------------------------
-- 
-- @function [parent=#EventController] getController 
-- @param self
-- @return Controller#Controller ret (return value: cc.Controller)
        
--------------------------------
--  Gets the key code of the controller.<br>
-- return The key code of the controller.
-- @function [parent=#EventController] getKeyCode 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @overload self, int, cc.Controller, bool         
-- @overload self, int, cc.Controller, int         
-- @function [parent=#EventController] EventController
-- @param self
-- @param #int type
-- @param #cc.Controller controller
-- @param #int keyCode
-- @return EventController#EventController self (return value: cc.EventController)

return nil
