# 説明
# 流れとしては、まず「中間の値（軸要素）」を決めて、左右から入れ替え、分割を繰り返すアルゴリズムである。
from typing import List


def quick_sort(number: List[int], left: int, right: int) -> List[int]:
    if left < right:
        pi = partition(number, left, right)
        quick_sort(number, left, pi - 1)
        quick_sort(number, pi + 1, right)
    return number


def partition(number: List[int], left: int, right: int) -> int:
    # left, rightの真ん中の値を取り出し、その値とrightの値をswapする。
    pivot = int((left + right) / 2)
    number[pivot], number[right] = number[right], number[pivot]
    store = left

    for i in range(left, right):
        if number[i] <= number[right]:
            number[i], number[store] = number[store], number[i]
            store += 1

    number[store], number[right] = number[right], number[store]

    return store


if __name__ == '__main__':
    import random
    nums = [random.randint(0, 1000) for _ in range(10)]
    print("before sort nums = {}".format(nums))
    print("after sort nums = {}".format(quick_sort(nums, 0, len(nums) - 1)))
