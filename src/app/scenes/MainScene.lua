
local pixelTextLayer=require("app.layer.pixelTestLayer")
local alphaLut = require("app.layer.AlphaLutCreate")

local keep = require("app.Test.keepTest")
local clip = require("app.Test.clipTest")
local multi = require("app.Test.multiTest")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    
end

function MainScene:onEnter()
---------------------------------------
--      切换工具和演示

--    alphaLut.new():addTo(self)
--    pixelTextLayer.new():addTo(self)

--    keep.new():addTo(self)
--    clip.new():addTo(self)
    multi.new():addTo(self)
    
end

function MainScene:onExit()
end

return MainScene
