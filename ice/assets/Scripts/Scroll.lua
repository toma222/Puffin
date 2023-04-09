

-- If the module name is changed then make sure to edit the scene file
-- so that it regonises that you changed.
Scroll = 
{
    IscrollSpeed = 1,

    Start = function ()
        rect = Rectangle.new()
        rect.x = 2;

        print(tostring(rect.x))

        transform = Transform.new(4,3,2,1)
        print(tostring(transform.m_rect.x))
    end,

    Update = function ()
        --Scroll.testNum.x = Scroll.testNum.x + 1
    end
}
