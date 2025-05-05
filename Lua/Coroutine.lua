

function coro_sample()
    co = coroutine.create(function ()
        for i=1,10 do
            print("co", i)
            coroutine.yield()
          end
    end)

    coroutine.resume(co)
    coroutine.resume(co)
    coroutine.resume(co)
    coroutine.resume(co)
end

coro_sample()
--  D:\Softwares\lua\lua54.exe Coroutine.lua  
