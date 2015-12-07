local pixelTestLayer=class("pixelTestLayer",function()
    return cc.LayerColor:create(cc.c4b(100,100,150,255))
end)


function pixelTestLayer:ctor()
    self:setNodeEventEnabled(true)
end

function pixelTestLayer:onEnter()

    local dir = "Test/multi/"
    local lutfile = dir .. "tiles4image.bit"
        
    local s1="fight_map_tile11.png"
    local s2 = "fight_map_tile21.png"
    
    
    self.sp=display.newSprite(dir .. s1):addTo(self):pos(display.width / 4,display.cy)
    self.sp1=display.newSprite(dir .. s2):addTo(self):pos(display.width / 4 * 3,display.cy)

    local luts = ImageAlphaHelper:new()
    luts:createAlphaLutsWithFile(lutfile)
    
    local tab = luts:getLutMap()
    
    self.spImage= tab[s1]
    self.spImage:retain()
    
    self.spImage1 = tab[s2]
    self.spImage1:retain()

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
        print("left png",inSpPoint.x,inSpPoint.y)
        if self.spImage:isPixelAlpha(inSpPoint.x,inSpPoint.y) then
            print("click!!!!")
        end
    end
    
    local p = self.sp1:convertToNodeSpace(touchPoint)
    local a = self.sp1:getBoundingBox()
    a.x = 0
    a.y = 0
    
    if cc.rectContainsPoint(a,p) then
        print("right png: ",p.x,p.y)
        if self.spImage1:isPixelAlpha(p.x,p.y) then
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