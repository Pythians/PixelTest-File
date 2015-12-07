local pixelTestLayer=class("pixelTestLayer",function()
    return cc.LayerColor:create(cc.c4b(100,100,150,255))
end)


function pixelTestLayer:ctor()
    self:setNodeEventEnabled(true)
    
    self.ccbController={}
    ccb["fightTilesNode"]=self.ccbController

    local proxy = cc.CCBProxy:create()
    self.node  = CCBReaderLoad("ccbi/fightTilesNode.ccbi",proxy,self.ccbController)
    self.node:addTo(self)
    
end

function pixelTestLayer:onEnter()

    local dir = "Test/multi/"
    local lutfile = dir .. "tiles4image.bit"
        
--    local s1="fight_map_tile11.png"
--    local s2 = "fight_map_tile21.png"
--    
--    
--    self.sp=display.newSprite(dir .. s1):addTo(self):pos(display.width / 4,display.cy)
--    self.sp1=display.newSprite(dir .. s2):addTo(self):pos(display.width / 4 * 3,display.cy)

    local luts = ImageAlphaHelper:new()
    luts:createAlphaLutsWithFile(lutfile)
    
    self.tab = luts:getLutMap()
    
    for k, v in pairs(self.tab) do
    	v:retain()    	
    end
    
--    self.spImage= tab[s1]
--    self.spImage:retain()
--    
--    self.spImage1 = tab[s2]
--    self.spImage1:retain()

    local listener=cc.EventListenerTouchOneByOne:create()
    listener:setSwallowTouches(true)
    listener:registerScriptHandler(handler(self,pixelTestLayer._onTouchBegan),cc.Handler.EVENT_TOUCH_BEGAN)
    local eventDispatcher=self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener,self)

end

function pixelTestLayer:_onTouchBegan(touch,event)    
    local touchPoint=touch:getLocation()
    
    print("touch point x: " .. touchPoint.x, " y: " .. touchPoint.y)    
    
    local sp36 = self.node:getChildByTag(36)
    
    if sp36:getPositionY() - sp36:getBoundingBox().height / 2 > touchPoint.y then
    	return false
    end
    
    local sp1 = self.node:getChildByTag(1)
    
    if sp1:getPositionY() + sp1:getBoundingBox().height / 2 < touchPoint.y then
    	return false
    end
    
    
    local children = self.node:getChildren()

    for k, v in pairs(children) do
    	local pos = v:convertToNodeSpace(touchPoint)
    	local area = v:getBoundingBox()
    	area.x = 0
    	area.y = 0
    	
    	if cc.rectContainsPoint(area, pos) then
    		if self.tab["fight_map_tile" .. v:getTag() .. ".png"]:isPixelAlpha(pos.x,pos.y) then
                print("touch " .. v:getTag() .. "th sprite")
    		end
    	end
    end
       
--    local inSpPoint=self.sp:convertToNodeSpace(touchPoint)
--    local defaultArea=self.sp:getBoundingBox()
--    defaultArea.x=0 defaultArea.y=0
--
--    if cc.rectContainsPoint(defaultArea,inSpPoint) then
--        print("left png",inSpPoint.x,inSpPoint.y)
--        if self.spImage:isPixelAlpha(inSpPoint.x,inSpPoint.y) then
--            print("click!!!!")
--        end
--    end
--    
--    local p = self.sp1:convertToNodeSpace(touchPoint)
--    local a = self.sp1:getBoundingBox()
--    a.x = 0
--    a.y = 0
--    
--    if cc.rectContainsPoint(a,p) then
--        print("right png: ",p.x,p.y)
--        if self.spImage1:isPixelAlpha(p.x,p.y) then
--            print("click!!!!")
--        end
--    end
    

    return false
end

function pixelTestLayer:onExit()
--    self.spImage:release()
--    self.spImage=nil

    for k, v in pairs(self.tab) do
    	v:release()
    	v = nil
    end
end

return pixelTestLayer