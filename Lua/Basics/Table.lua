
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

function test_mockClass()
--     我认为Lua就是天生支持成员函数语法的，即`function 表名:函数名() end` ，且支持在成员函数中引用表的成员的。
--     这里关键的问题在于：类和对象，是两个概念。Lua这里**缺乏的能力是“把表看做一个类，并将其实例化**”。 
--     所以需要模拟的工作是:实现一个假的类构造函数，Copy当前类表作为实例，并通过metatable重新绑定新的实例的函数调用。
    local Circle = {
        radius=3.0
    }
    function Circle:new()
        -- mock class constructor
        local inst = {}
        setmetatable(inst, {__index=self})
        inst.radius = self.radius
        return inst
    end
    function Circle:area()
       return self.radius * self.radius 
    end

    local c = Circle:new()
    c.radius = 5.0
    print(c:area())
end

-- use metable to add operator+ for table
-- test_metatable()
test_mockClass()

-- D:\Softwares\lua\lua54.exe Coroutine.lua  
