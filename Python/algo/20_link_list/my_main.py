from __future__ import annotations
from typing import Any


class Node(object):
    def __init__(self, data: Any, next: Node = None):
        self.data = data
        self.next = next


class LinkedList():
    def __init__(self):
        self.head = None

    def append(self, data):
        new_node = Node(data)

        if self.head is None:
            self.head = new_node
            return

        # 最後のnodeまで見つける
        last_node = self.head
        while last_node.next:
            last_node = last_node.next

        last_node.next = new_node

    def print(self) -> None:
        current_node = self.head
        while current_node:
            print(current_node.data)
            current_node = current_node.next


if __name__ == '__main__':
    l = LinkedList()
    l.append(1)
    l.append(2)
    l.append(3)
    # l.insert(0)

    l.print()