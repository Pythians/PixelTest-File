

local pixelTestLayer=class("pixelTestLayer",function()
    return cc.LayerColor:create(cc.c4b(100,100,150,255))
end)


function pixelTestLayer:ctor()
    self:setNodeEventEnabled(true)
end

function pixelTestLayer:onEnter()
    local str="keep/building_1_1.png"
    str = "res/multi/tiles4image/fight_map_tile1.png"

    self.sp=display.newSprite(str):addTo(self):pos(display.cx,display.cy)
    

------------------------------------------------------------
-- 图片像素检测对象创建方法
------------------------------------------------------------
--    通过图片创建 
--    @param str string 图片名
--    @return #ImageAlpha 像素检测对象
--    self.spImage=ImageAlpha:createWithImage(str);
------------------------------------------------------------
--    通过图片创建 并剪裁四周透明区域
--    @param string 图片名
--    @return #ImageAlpha 像素检测对象
--    self.spImage=ImageAlpha:createWithImageAndClip(str);
------------------------------------------------------------
--    通过保存的文件创建 （一个图片对应一个文件）
--    @param string 文件名
--    @return #ImageAlpha 像素检测对象 
--    self.spImage=ImageAlpha:createWithFile( path .. "res/output/keep/building_1_1.bit");
    
------------------------------------------------------------
-- 单个文件创建多个像素检测对象辅助对象
--   作为局部变量时 该对象创建的所有像素对象会在作用域结束后自动释放
--   持有创建的对象需要手动调用 retain
------------------------------------------------------------
--  创建辅助对象
    local luts = ImageAlphaHelper:new()
------------------------------------------------------------
--  
    luts:createAlphaLutsWithFile( path .. "res/output/multi/tiles4image.bit")
------------------------------------------------------------
--  获取单个像素检测对象
--    @param str string 图片名
--    @return #ImageImageLut 返回对象 或无则返回 nil
--    self.spImage = luts:getImageImageLut("building_1_1.png");
------------------------------------------------------------
--  获取全部像素检测对象
--    @return #table 所有像素检测的对象 键为对应的图片名
    local tab = luts:getLutMap()
    self.spImage = tab["fight_map_tile1.png"]
    -- 持有对象
    self.spImage:retain();
    
    local listener=cc.EventListenerTouchOneByOne:create()
    listener:setSwallowTouches(true)
    listener:registerScriptHandler(handler(self,pixelTestLayer._onTouchBegan),cc.Handler.EVENT_TOUCH_BEGAN)
    local eventDispatcher=self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener,self)
    
end

function pixelTestLayer:_onTouchBegan(touch,event)    
    local touchPoint=touch:getLocation()
    local inSpPoint=self.sp:convertToNodeSpace(touchPoint)
    local defaultArea=self.sp:getBoundingBox() 
    defaultArea.x=0 defaultArea.y=0
    
    if cc.rectContainsPoint(defaultArea,inSpPoint) then
        print("TouchInBoundingBox",inSpPoint.x,inSpPoint.y)
------------------------------------------------------------
--               像素检测 使用节点坐标
--               @param x number X 坐标
--               @param y number Y 坐标
--               @return #bool 是否有像素
        if self.spImage:isPixelAlpha(inSpPoint.x,inSpPoint.y) then
            print("click!!!!")
        end
    end
    
    return true
end

function pixelTestLayer:onExit()
   self.spImage:release()
   self.spImage=nil
end

return pixelTestLayer
