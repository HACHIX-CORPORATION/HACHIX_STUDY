from collections import deque
from typing import Any


class Queue(object):

    def __init__(self) -> None:
        self.queue = []

    def enqueue(self, data: Any) -> None:
        self.queue.append(data)

    def dequeue(self) -> Any:
        if self.queue:
            return self.queue.pop(0)


if __name__ == '__main__':
    q = deque()
    q.append(1)
    q.append(2)
    q.append(3)
    q.append(4)
    print(q)
    print(q.pop())
    print(q.pop())
    print(q.pop())
    print(q.pop())
    # q = Queue()
    # q.enqueue(1)
    # q.enqueue(2)
    # q.enqueue(3)
    # q.enqueue(4)
    # print(q.queue)
    # print(q.dequeue())
    # print(q.dequeue())
    # print(q.dequeue())
    # print(q.dequeue())
