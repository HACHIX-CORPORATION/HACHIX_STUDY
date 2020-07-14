from abc import ABC, abstractmethod


class AbstractClass(ABC):

    def template_method(self) -> None:
        """
        The template method defines the skeleton of an algorithm
        :return:
        """
        self.base_operation()
        self.required_operations1()
        self.required_operations2()
        self.hook()
        # This operation already have implementation

    @staticmethod
    def base_operation() -> None:
        print("Something in common")

    @abstractmethod
    def required_operations1(self) -> None:
        pass

    @abstractmethod
    def required_operations2(self) -> None:
        pass

    def hook(self) -> None:
        """
        hooks already have default (not empty) implementation.
        :return:
        """
        pass


class ConcreteClass1(AbstractClass):

    def required_operations1(self) -> None:
        print("Operation 1 of ConcreteClass 1")

    def required_operations2(self) -> None:
        print("Operation 2 of ConcreteClass 2")


class ConcreteClass2(AbstractClass):

    def required_operations1(self) -> None:
        print("Operation 1 of ConcreteClass 1")

    def required_operations2(self) -> None:
        print("Operation 2 of ConcreteClass 2")

    def hook(self) -> None:
        print("Overridden Hook!")


def client_code(abstract_class: AbstractClass) -> None:
    abstract_class.template_method()


if __name__ == "__main__":
    client_code(ConcreteClass1())

    client_code(ConcreteClass2())
