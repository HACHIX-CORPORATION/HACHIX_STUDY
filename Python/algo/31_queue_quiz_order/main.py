from collections import deque


def reverse(queue: deque) -> deque:
    new_queue = deque()
    while queue:
        new_queue.append(queue.pop())
    [queue.append(d) for d in new_queue]
    # return new_queue


if __name__ == '__main__':
    q = deque()
    q.append(1)
    q.append(2)
    q.append(3)
    q.append(4)
    print(q)
    # q.reverse()
    # print(q)
    reverse(q)
    print(q)
