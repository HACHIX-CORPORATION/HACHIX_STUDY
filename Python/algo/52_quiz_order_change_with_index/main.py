"""
Input : ['h', 'y', 'n', 'p', 't', 'o'], [3, 1, 5, 0, 2, 4]
Output: python
"""
from typing import List


def order_change_by_indexes_v1(chars: List[str], indexes: List[int]) -> str:
    tmp = [None] * len(chars)
    for i, index in enumerate(indexes):
        tmp[index] = chars[i]
    return ''.join(tmp)


def order_change_by_indexes_v2(chars: List[str], indexes: List[int]) -> str:
    i, len_indexes = 0, len(indexes) - 1
    while i < len_indexes:
        while i != indexes[i]:
            index = indexes[i]
            chars[index], chars[i] = chars[i], chars[index]
            indexes[index], indexes[i] = indexes[i], indexes[index]
        i += 1
    return ''.join(chars)


if __name__ == '__main__':
    w = ['h', 'y', 'n', 'p', 't', 'o']
    i = [3, 1, 5, 0, 2, 4]
    print(order_change_by_indexes_v2(w, i))
