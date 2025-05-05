
function add_by_element(t1, t2)
    local len = math.min(#t1, #t2)
    ret = {}
    for i= 1,len do
        ret[i] = t1[i] + t2[i]  
    end
    if #t1 > #t2 then
        ret[len + 1] = t1[len + 1]
    else
        ret[len + 1] = t2[len + 1]
    end
    return ret
end


function test_metatable()
    a = {1, 2, 3}
    b = {5, 5, 0, 1}
    c = {1, 2, 3}
    mt = {__add= add_by_element}

    setmetatable(a, mt)

    local x = a + b
    -- local x2 = c + b
    for i=1,#x do
        print(string.format("ret[%d] = %d", i, ret[i]))
    end
end

test_metatable()

-- D:\Softwares\lua\lua54.exe Coroutine.lua  
