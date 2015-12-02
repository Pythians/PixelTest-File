
local AlphaLutCreate = class("AlphaLutCreate",function ()
    return cc.LayerColor:create(cc.c4b(100,100,150,255))
end)

function AlphaLutCreate:ctor()
	self:setNodeEventEnabled(true)
    self.alphaLut = ImageAlphaHelper:new()
	self.alphaLut:retain()
	
    print( device.writablePath )
end

path = "/Users/wjdev02/Desktop/"

function AlphaLutCreate:keep()
    self.alphaLut:setIsClip(false)
    self.alphaLut:setDirectory( path .. "res/keep")
    self.alphaLut:saveInOneFile( path .. "res/output/keep")
end

function AlphaLutCreate:clip()

    -- self.alphaLut:setDirectory( path .. "res/clip")
    -- self.alphaLut:saveToFiles(path .. "res/output/clip")

    self.alphaLut:createAlphaLutsWithFile( path .. "res/output/keep/keep.bit")

    local luts = self.alphaLut:getLutMap()
    print (type(luts["building_1_1.png"]))

    local lut = self.alphaLut:getImageImageLut("building_1_1.png")
    print(type(lut))
    print(type(self.alphaLut))
    
end

function AlphaLutCreate:multi()
    self.alphaLut:setDirectory( path .. "res/multi")
    self.alphaLut:saveInOneFile(path .. "res/output/multi")

end


function AlphaLutCreate:onTouchBegin(touch,event)
    
    local touchPoint=touch:getLocation()
    
    local bt0Pos = self.button0:convertToNodeSpace(touchPoint)
    local bt0Area = self.button0:getBoundingBox()
    bt0Area.x = 0
    bt0Area.y = 0
    
    
    local bt1Pos=self.button1:convertToNodeSpace(touchPoint)
    local bt1Area=self.button1:getBoundingBox() 
    bt1Area.x=0 
    bt1Area.y=0

    local bt2Pos = self.button2:convertToNodeSpace(touchPoint)
    local bt2Area = self.button2:getBoundingBox()
    bt2Area.x = 0
    bt2Area.y = 0
    
    if cc.rectContainsPoint(bt1Area,bt1Pos) then
        print("Touch button0 keep")
        self:keep()
        self.label:setTextColor(cc.c4b(0,215,215,255))
        self.label:setString("keep OK!!")
    end

    if cc.rectContainsPoint(bt0Area,bt0Pos) then
        print("Touch button1 clip")
        self:clip()
        self.label:setTextColor(cc.c4b(215,215,0,255))
        self.label:setString("clip OK!!")
    end

    if cc.rectContainsPoint(bt2Area,bt2Pos) then
        print("Touch button2 multi")

        self:multi()
        self.label:setTextColor(cc.c4b(215,0,215,255))
        self.label:setString("multi OK!!")
    end

    return false
    
end

function AlphaLutCreate:onEnter()
    
    
    self.button0 = cc.Label:create();
    self.button1 = cc.Label:create();
    self.button2 = cc.Label:create();
    self.label = cc.Label:create();
    
    self.button0:setTextColor(cc.c4b(215,215,0,255))
    self.button1:setTextColor(cc.c4b(0,215,215,255))
    self.button2:setTextColor(cc.c4b(215,0,215,255))
    self.label:setTextColor(cc.c4b(215,215,215,255))
    
    self.button0:setString("clip")
    self.button1:setString("keep")
    self.button2:setString("multi")
    self.label:setString("hello") 
    
    self.button0:setSystemFontSize(64)
    self.button1:setSystemFontSize(64)
    self.button2:setSystemFontSize(64)
    self.label:setSystemFontSize(72)
    
    display.align(self.button0, display.CENTER, display.width / 3,display.cy)
    display.align(self.button1, display.CENTER, display.width / 3,display.cy * 3 / 2)
    display.align(self.button2, display.CENTER, display.width / 3,display.cy / 2)
    display.align(self.label, display.CENTER, display.width * 3 / 4, display.cy)
    
    self:addChild(self.button0)
    self:addChild(self.button1)
    self:addChild(self.button2)
    self:addChild(self.label)
    
    local listener = cc.EventListenerTouchOneByOne:create()
    listener:setSwallowTouches(true)
    listener:registerScriptHandler(handler(self,AlphaLutCreate.onTouchBegin),cc.Handler.EVENT_TOUCH_BEGAN)
    
    local eventDispatcher=self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener,self)

    
   
end

function AlphaLutCreate:onExit()

    self.alphaLut:release()

end


return AlphaLutCreate