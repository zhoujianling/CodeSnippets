

"""
1. function as decorators
"""

def Deco1(func):
    print("hello, func type is " + str(type(func)))
    def decorate():
        return func()
    return decorate

@Deco1
def foo():
    print("foo")
    pass


class Foo(object):
    def __init__(self) -> None:
        super().__init__()

    @Deco1
    def do_something(self):
        pass

    # def 


if __name__ == '__main__':
    # foo()
    pass