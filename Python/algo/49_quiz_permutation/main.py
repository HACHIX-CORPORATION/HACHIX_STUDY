'''
from itertools import permutations
for i in permutations([1, 2, 3]):
    print(i)
'''
from typing import List, Iterator, Tuple


def all_perms_v1(elements: List[int]) -> List[List[int]]:
    result = []
    if len(elements) <= 1:
        return [elements]

    for perm in all_perms_v1(elements[1:]):
        for i in range(len(elements)):
                result.append(perm[:i] + elements[0:1] + perm[i:])
    return result


def all_perms_v2(elements: List[int]) -> Iterator[List[int]]:
    if len(elements) <= 1:
        yield elements
    else:
        for perm in all_perms_v2(elements[1:]):
            for i in range(len(elements)):
                yield perm[:i] + elements[0:1] + perm[i:]


if __name__ == '__main__':
    elements = [1, 2, 3]
    for p in all_perms_v1(elements):
        print(p)
    print('')
    for p in all_perms_v2(elements):
        print(p)

