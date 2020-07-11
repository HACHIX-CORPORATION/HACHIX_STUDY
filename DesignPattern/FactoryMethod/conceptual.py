from __future__ import annotations
from abc import ABC, abstractmethod


class Creator(ABC):

    @abstractmethod
    def factory_method(self):
        """
        the Creator also provide some default implementation of the factory method
        :return:
        """
        pass

    def some_operation(self) -> str:
        """
        not creating products. Only contains some core business logic that relies on Product objects.
        :return:
        """

        # Call the factory method to create a Product object:
        product = self.factory_method()

        # Now, use the product.
        result = f"Creator: The same creator's code has just worked with {product.operation()}"

        return result


class ConcreteCreator1(Creator):

    def factory_method(self) -> ConcreteProduct1:
        return ConcreteProduct1()


class ConcreteCreator2(Creator):

    def factory_method(self) -> ConcreteProduct2:
        return ConcreteProduct2()


class Product(ABC):

    @abstractmethod
    def operation(self) -> str:
        pass


"""
Concrete Products provide various implementations of the Product interface. 
"""


class ConcreteProduct1(Product):
    def operation(self) -> str:
        return "{Result of the ConcreteProduct1}"


class ConcreteProduct2(Product):
    def operation(self) -> str:
        return "{Result of the ConcreteProduct2}"


def client_code(creator: Creator) -> None:
    """
    The client code works with an instance of a concrete creator, albeit through its base interface. As long as the
    client keeps working with the creator via the base interface, you can pass it any creator's subclass.
    :param creator:
    :return:
    """

    print(f"Client: I'm not aware of the creator's class, but it still works. \n"
          f"{creator.some_operation()}", end="")


if __name__ == "__main__":
    print("App: Launched with the ConcreteCreator1")
    client_code(ConcreteCreator1())
    print("\n")

    print("App: Launched with the ConcreteCreator2")
    client_code(ConcreteCreator2())
