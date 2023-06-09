
--------------------------------
-- @module Physics3DShape
-- @extend Ref
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Physics3DShape] getbtShape 
-- @param self
-- @return btCollisionShape#btCollisionShape ret (return value: btCollisionShape)
        
--------------------------------
-- 
-- @function [parent=#Physics3DShape] initSphere 
-- @param self
-- @param #float radius
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Physics3DShape] initBox 
-- @param self
-- @param #vec3_table ext
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Physics3DShape] initCapsule 
-- @param self
-- @param #float radius
-- @param #float height
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Physics3DShape] initCylinder 
-- @param self
-- @param #float radius
-- @param #float height
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- get shape type
-- @function [parent=#Physics3DShape] getShapeType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- create box shape<br>
-- param extent The extent of sphere.
-- @function [parent=#Physics3DShape] createBox 
-- @param self
-- @param #vec3_table extent
-- @return Physics3DShape#Physics3DShape ret (return value: cc.Physics3DShape)
        
--------------------------------
-- create cylinder shape<br>
-- param radius The radius of cylinder.<br>
-- param height The height.
-- @function [parent=#Physics3DShape] createCylinder 
-- @param self
-- @param #float radius
-- @param #float height
-- @return Physics3DShape#Physics3DShape ret (return value: cc.Physics3DShape)
        
--------------------------------
-- create convex hull<br>
-- param points The vertices of convex hull<br>
-- param numPoints The number of vertices.
-- @function [parent=#Physics3DShape] createConvexHull 
-- @param self
-- @param #vec3_table points
-- @param #int numPoints
-- @return Physics3DShape#Physics3DShape ret (return value: cc.Physics3DShape)
        
--------------------------------
-- create capsule shape<br>
-- param radius The radius of capsule.<br>
-- param height The height (cylinder part).
-- @function [parent=#Physics3DShape] createCapsule 
-- @param self
-- @param #float radius
-- @param #float height
-- @return Physics3DShape#Physics3DShape ret (return value: cc.Physics3DShape)
        
--------------------------------
-- create sphere shape<br>
-- param radius The radius of sphere.
-- @function [parent=#Physics3DShape] createSphere 
-- @param self
-- @param #float radius
-- @return Physics3DShape#Physics3DShape ret (return value: cc.Physics3DShape)
        
--------------------------------
-- 
-- @function [parent=#Physics3DShape] Physics3DShape 
-- @param self
-- @return Physics3DShape#Physics3DShape self (return value: cc.Physics3DShape)
        
return nil
