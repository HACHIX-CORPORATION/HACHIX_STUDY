# Quiz
# 

from typing import Any
from collections import deque


def reverse(queue: deque) -> Any:
    new_q = deque()

    for _ in range(len(queue)):
        new_q.append(queue.pop())

    return new_q


if __name__ == '__main__':
    q = deque()
    q.append(1)
    q.append(2)
    q.append(3)
    q.append(4)
    print(q)
    new_q = reverse(q)
    print(new_q)