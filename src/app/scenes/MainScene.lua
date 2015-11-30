
local pixelTextLayer=require("app.layer.pixelTestLayer")
local alphaLut = require("app.layer.AlphaLutCreate")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    
end

function MainScene:onEnter()
    alphaLut.new():addTo(self)
--    pixelTextLayer.new():addTo(self)
    
end

function MainScene:onExit()
end

return MainScene
