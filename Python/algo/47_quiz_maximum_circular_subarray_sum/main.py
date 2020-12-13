"""
1. Maximum subarray sum
Input [1, 3, -1, -2, 4, 5, 7, -10, -1, 2]
Output 16 (1 + 3 - 1 - 2 + 4 + 5 + 7)

2. Maximum circular subarray sum
Input [1, 3, -1, -2, 4, 5, 7, -10, -1, 2]
Output 19 (1 + 3 - 1 - 2 + 4 + 5 + 7 + 2)
"""
from typing import List


def get_max_sequence_sum(numbers: List[int], operator=max) -> int:
    result_sequence, sum_sequence = 0, 0
    for num in numbers:
        sum_sequence = operator(num, sum_sequence + num)
        result_sequence = operator(result_sequence, sum_sequence)
        # temp_sum_sequence = sum_sequence + num
        # iftemp_sum_sequence > num:
        #     sum_sequence = temp_sum_sequence
        # else:
        #     sum_sequence = num
        # if result_sequence > sum_sequence:
        #     result_sequence = sum_sequence
    return result_sequence


def find_max_circular_sequence_sum(numbers: List[int]) -> int:
    max_sequence_sum = get_max_sequence_sum(numbers)
    max_wrap_sequence = sum(numbers) - get_max_sequence_sum(numbers, operator=min)
    # all_sum = 0
    # invert_numbers = []
    # for num in numbers:
    #     all_sum += num
    #     invert_numbers.append(-num)
    #
    # max_invert_numbers = get_max_sequence_sum(invert_numbers)
    # max_wrap_sequence = all_sum - (-max_invert_numbers)

    return max(max_sequence_sum, max_wrap_sequence)


if __name__ == '__main__':
    l = [1, -2, 3, 6, -1, 2, 4, -5, 2]
    print(get_max_sequence_sum(l))
    print(find_max_circular_sequence_sum(l))
