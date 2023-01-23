local script = {}

-- runs when the script is created
function script.init()
    print('hello from the init function')
end

-- runs every frame
function script.update()
    local obj = TransformBinding(42, 0, 0)

    obj:translate(0, 0, 0)
end

return script
