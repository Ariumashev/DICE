-- The on_click and on_move functions are called from C++ via LuaScriptEngine::fireEvent().

function on_click(self)
    cpp_log("Clicked: " .. self:getName())
    local x = self:getX()
    local y = self:getY()
    self:setPosition(x, y - 10)
    if y - 10 < 0 then
        self:setActive(false)
        cpp_log("Chip reached top edge, deactivating: " .. self:getName())
    end
end

function on_move(self)
    cpp_log("Moved: " .. self:getName() ..
            " to (" .. self:getX() .. ", " .. self:getY() .. ")")
end
