"""
Input 5, 20
Output
[[7], [6, 3], [6, 0, 15], [4, 20, 1, 8], [6, 4, 4, 1, 0]]
            7
          6   3
        6   0   15
      4   20  1   8
    6   4   4   1   0
min path = 12
"""
from typing import List, Optional
import random


def generate_triangle_list(depth: int, max_num: int) -> List[List[int]]:
    return [[random.randint(0, max_num) for _ in range(i)] for i in range(1, depth+1)]


def print_triangle(data: List[List[int]]) -> None:
    max_digit = len(str(max([max(l) for l in data])))
    width = max_digit + (max_digit % 2) + 2
    for index, line in enumerate(data):
        numbers = ''.join([str(i).center(width, ' ') for i in line])
        print(' ' * int(width/2) * (len(data) - index), numbers)


def sum_min_path(triangle: List[List[int]]) -> Optional[int]:
    tree_sum = triangle[:]
    j, len_triangle = 1, len(triangle)
    if not len_triangle:
        return

    while j < len_triangle:
        line = triangle[j]
        line_path_sum = []
        for i, value in enumerate(line):
            if i == 0:
                sum_value = line[i] + tree_sum[j-1][0]
            elif i == len(line) - 1:
                sum_value = line[i] + tree_sum[j-1][i-1]
            else:
                min_path = min(tree_sum[j-1][i-1], tree_sum[j-1][i])
                sum_value = line[i] + min_path
            line_path_sum.append(sum_value)
        tree_sum[j] = line_path_sum
        j += 1
    return min(tree_sum[-1])


if __name__ == '__main__':
    data = generate_triangle_list(5, 9)
    print(data)
    print_triangle(data)
    print('min path =', sum_min_path(data))

