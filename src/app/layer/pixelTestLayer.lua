

local pixelTestLayer=class("pixelTestLayer",function()
    return cc.LayerColor:create(cc.c4b(100,100,150,255))
end)


function pixelTestLayer:ctor()
    self:setNodeEventEnabled(true)
end

function pixelTestLayer:onEnter()
    local str="building_1_1.png"

    self.sp=display.newSprite(str):addTo(self):pos(display.cx,display.cy)
    
    self.spImage=ImageAlpha:createWithFile(str);
    self.spImage:retain();

    
    local restart = cc.MenuItemImage:create("restart.png","restart.png");
    restart:setPosition(100,100);    
    restart:registerScriptTapHandler(function()
        print("menu touch");
        
        alphaFile()
    end)
    
    local menu = cc.Menu:create(restart);
    menu:setPosition(0,0);
    self:addChild(menu, 100);
    
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
