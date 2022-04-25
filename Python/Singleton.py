
class Singleton(object):
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(Singleton, cls).__new__(cls)
            # Put any initialization here.
        return cls._instance


if __name__ == '__main__':
    s1 = Singleton()
    s2 = Singleton()
    assert(s1 is s2)
