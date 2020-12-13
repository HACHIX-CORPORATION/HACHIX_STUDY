#  l = [1, 3, 4, 2, 4, 5, 1, 6, 9, 8]  =>  l = [4, 2, 4, 6, 8, 1, 3, 5, 1, 9]

from typing import List


def order_even_first_odd_last_v1(numbers: List[int]) -> None:
    even_list, odd_list = [], []
    for num in numbers:
        if num % 2 == 0:
            even_list.append(num)
        else:
            odd_list.append(num)
    numbers[:] = even_list + odd_list


def order_even_first_odd_last_v2(numbers: List[int]) -> None:
    i, j = 0, len(numbers) - 1
    while i < j:
        if numbers[i] % 2 == 0:
            i += 1
        else:
            numbers[i], numbers[j] = numbers[j], numbers[i]
            # tmp = numbers[i]
            # numbers[i] = numbers[j]
            # numbers[j] = tmp
            j -= 1
        print(numbers)


if __name__ == '__main__':
    l = [0, 1, 3, 4, 2, 4, 5, 1, 6, 9, 8]
    order_even_first_odd_last_v2(l)
    print(l)
