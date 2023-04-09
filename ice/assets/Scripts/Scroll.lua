

-- If the module name is changed then make sure to edit the scene file
-- so that it regonises that you changed.
Scroll = 
{
    IscrollSpeed = 1,

    Start = function ()
        rect = Rectangle.new()
        rect.x = 2;
        
        print(Scroll.entity:GetName());
        print(tostring(Scroll.entity:GetUUID()))
    end,

    Update = function ()
        --Scroll.testNum.x = Scroll.testNum.x + 1
    end
}
