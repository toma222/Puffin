require(Scancodes)

-- Variables defined and initilized here
Scroll = {
    transformRect = nil,
    scrollSpeed = 1
}

-- Function called on the first scene render
function Scroll.Start()
    Scroll.transformRect = Scroll.transform:GetRect();

    -- You can also get the transform data from the attached entity like this
    -- Scroll.transformRect = Scroll.entity:GetComponent():GetRect();
end

-- Function called every scene render
function Scroll.Update()
    Scroll.transformRect.x = Scroll.transformRect.x + Scroll.scrollSpeed;

    -- if puffin.IsKeyPressed(0) then
    --     print('up')
    -- end
end

return Scroll
