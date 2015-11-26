
local pixelTextLayer=require("app.layer.pixelTestLayer")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    
end

function MainScene:onEnter()
    pixelTextLayer.new():addTo(self)
end

function MainScene:onExit()
end

return MainScene
