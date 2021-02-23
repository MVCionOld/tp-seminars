from abc import ABC
from abc import abstractmethod
import copy
import time


class Cloneable(ABC):

    @abstractmethod
    def clone(self) -> "Cloneable":
        raise NotImplementedError("Method clone is not implemented")


class BasePrototype(Cloneable):

    def __init__(self, key: str = None):
        self._payload = {
            "key": key
        }
        self.__setup_other_data()

    def __setup_other_data(self):
        time.sleep(10)  # emulates long-executing extraction from db
        self.data = [{} for _ in range(100)]

    def update_key(self, key: str):
        self._payload["key"] = key

    def clone(self) -> "BasePrototype":
        proto = copy.deepcopy(self)
        proto._payload["key"] = None
        return proto


class DerivedPrototype(BasePrototype):

    def __init__(self, key: str = None):
        BasePrototype.__init__(self, key)

