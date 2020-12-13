from typing import List


def generate_pascal_triangle(depth: int) -> List[List[int]]:
    data = [[1] * (i + 1) for i in range(depth)]
    for line in range(2, depth):
        for i in range(1, line):
            data[line][i] = data[line-1][i-1] + data[line-1][i]
    return data


def print_pascal(data: List[int]) -> None:
    max_digit = len(str(max(data[-1])))
    width = max_digit + (max_digit % 2) + 2
    for index, line in enumerate(data):
        numbers = ''.join([str(i).center(width, ' ') for i in line])
        print((' ' * int(width/2)) * (len(data) - index), numbers)


if __name__ == '__main__':
    print_pascal(generate_pascal_triangle(10))
