

-- If the module name is changed then make sure to edit the scene file
-- so that it regonises that you changed.
Scroll = 
{
    IscrollSpeed = 1,

    Start = function ()
        print('Update from start')
        v = Vector2.new()
        v.x = v.x + 1

        print(tostring(v.x));
    end,

    Update = function ()
        --Scroll.testNum.x = Scroll.testNum.x + 1
    end
}
