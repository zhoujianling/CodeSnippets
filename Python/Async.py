import asyncio
import types

@types.coroutine
def gen():
    print("00")
    yield 1
    print("11")
    return (yield 2)

async def aa():
    print("?")
    a = await gen()
    print("return " + str(a))

def main():
    try:
        a = aa()
        a.send(None)
        a.send(None)
        a.send(None)
    except StopIteration as e:
        print(e.value)
    pass

if __name__ == "__main__":
    main()
    pass