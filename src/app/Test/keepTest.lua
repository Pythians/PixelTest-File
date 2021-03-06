local pixelTestLayer=class("pixelTestLayer",function()
    return cc.LayerColor:create(cc.c4b(100,100,150,255))
end)


function pixelTestLayer:ctor()
    self:setNodeEventEnabled(true)
end

function pixelTestLayer:onEnter()

    local str="Test/keep/building_5_1.png"
--    str = "Test/keep/building_6_1.png"
    
    self.sp=display.newSprite(str):addTo(self):pos(display.cx,display.cy)
    
    
    self.spImage=ImageAlpha:createWithImage(str);
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