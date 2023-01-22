local script = {}

-- runs when the script is created
function script.init()
    print('hello from the init function')
end

-- runs every frame
function script.update()
    print('Update from lua!')
end

return script
