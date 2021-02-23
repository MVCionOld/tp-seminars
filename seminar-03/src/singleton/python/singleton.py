class Singleton(object):

    def __new__(cls):
        # Перекрываем создание объекта класса
        if not hasattr(cls, 'instance'):
            cls.instance = super(Singleton, cls).__new__(cls)
        return cls.instance
