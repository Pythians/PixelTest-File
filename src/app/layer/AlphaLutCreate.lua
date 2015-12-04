--[[

**图片全名不能超过 45 个**

  下面两个文件夹放图片文件 不能有文件夹
    res/clip -> 剪裁保存信息，不保存边界透明区域
    res/keep -> 完整保存像素信息
    
  下面文件夹只放文件夹 不能有文件
    res/multi -> 将子文件夹内的图片信息保存在以子文件夹名命名的文件中
    **此文件夹下只能是文件夹
    **子文件夹只能有一级
    
  指定保存文件路径可写
  可以创建指定路径
--]]

local AlphaLutCreate = class("AlphaLutCreate",function ()
    return cc.LayerColor:create(cc.c4b(100,100,150,255))
end)

-------------------------------------------------------------
--  @field #string path 文件读写路径 （xcode 调试用）
path = "/Users/wjdev02/Desktop/"
--path = device.writablePath

function AlphaLutCreate:ctor()
	self:setNodeEventEnabled(true)
	
    self.alh = ImageAlphaHelper:new()
    self.alh:retain()

	self.isClip = true
	
end



function AlphaLutCreate:onTouchBegin(touch,event)
    
--    local ALHer = ImageAlphaHelper:new()
    local ALHer = self.alh
    
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
    
    local btcpos = self.isClipBt:convertToNodeSpace(touchPoint)
    local btcArea = self.isClipBt:getBoundingBox()
    btcArea.x = 0
    btcArea.y = 0
    
    if cc.rectContainsPoint(bt1Area,bt1Pos) then
        ALHer:setIsClip(false)
        
        -----
        -- 读取图片 路径
        ALHer:setDirectory( path .. "res/keep")
        --    ALHer:saveToFiles( path .. "res/output/keep")
        ----
        -- 保存路径 
        -- 单独文件
        ALHer:saveToFiles( path .."output/keep")

        --print("-- keep")
        self.label:setTextColor(cc.c4b(0,215,215,255))
        self.label:setString("keep OK!!")
    end

    if cc.rectContainsPoint(bt0Area,bt0Pos) then
        ALHer:setIsClip(true)
        ALHer:setDirectory( path .. "res/clip")
        --    ALHer:saveToFiles(path .. "res/output/clip")
        ALHer:saveToFiles(path .. "output/clip")

        print("-- clip")
        self.label:setTextColor(cc.c4b(215,215,0,255))
        self.label:setString("clip OK!!")
    end

    if cc.rectContainsPoint(bt2Area,bt2Pos) then
        if self.isClip then
            ALHer:setIsClip(true)
        else
            ALHer:setIsClip(false)
        end
        ALHer:setDirectory( path .. "res/multi")
        --    ALHer:saveInOneFile(path .. "res/output/multi")
        ---
        -- 保存为单个文件
        ALHer:saveInOneFile(path .. "output/multi")
        print("-- multi")

        self.label:setTextColor(cc.c4b(215,0,215,255))

        if self.isClip then
            self.label:setString("multi clip OK!!")
        else
            self.label:setString("multi OK!!")    
        end
    end
    
    if cc.rectContainsPoint(btcArea,btcpos) then
    
        if self.isClip then
            self.isClip = false
            self.isClipBt:setString("Clip OFF")
            self.isClipBt:setTextColor(cc.c4b(246,132,34,255))
        else
            self.isClip = true
            self.isClipBt:setString("Clip ON")
            self.isClipBt:setTextColor(cc.c4b(0,255,0,255))
        end

    end

    return false
    
end

function AlphaLutCreate:onEnter()
    
    
    self.button0 = cc.Label:create();
    self.button1 = cc.Label:create();
    self.button2 = cc.Label:create();
    self.label = cc.Label:create();
    self.isClipBt = cc.Label:create();
    
    self.button0:setTextColor(cc.c4b(215,215,0,255))
    self.button1:setTextColor(cc.c4b(0,215,215,255))
    self.button2:setTextColor(cc.c4b(215,0,215,255))
    self.label:setTextColor(cc.c4b(215,215,215,255))
    self.isClipBt:setTextColor(cc.c4b(0,255,0,255))
    
    self.button0:setString("clip")
    self.button1:setString("keep")
    self.button2:setString("multi")
    self.label:setString("hello") 
    self.isClipBt:setString("Clip ON")
    
    self.button0:setSystemFontSize(64)
    self.button1:setSystemFontSize(64)
    self.button2:setSystemFontSize(64)
    self.label:setSystemFontSize(72)
    self.isClipBt:setSystemFontSize(28)
    
    display.align(self.button0, display.CENTER, display.width / 3,display.cy)
    display.align(self.button1, display.CENTER, display.width / 3,display.cy * 3 / 2)
    display.align(self.button2, display.CENTER, display.width / 3,display.cy / 2)
    display.align(self.label, display.CENTER, display.width * 3 / 4, display.cy)
    display.align(self.isClipBt, display.CENTER, display.width / 2, display.cy / 2)
    
    self:addChild(self.button0)
    self:addChild(self.button1)
    self:addChild(self.button2)
    self:addChild(self.label)
    self:addChild(self.isClipBt)
    
    local listener = cc.EventListenerTouchOneByOne:create()
    listener:setSwallowTouches(true)
    listener:registerScriptHandler(handler(self,AlphaLutCreate.onTouchBegin),cc.Handler.EVENT_TOUCH_BEGAN)
    
    local eventDispatcher=self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener,self)
   
end

function AlphaLutCreate:onExit()
	self.alh:release()
end

return AlphaLutCreate