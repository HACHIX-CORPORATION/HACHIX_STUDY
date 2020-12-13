def merge_sort(data: list, l: int, m: int, r: int) -> list:
    len_left, len_right = m - l + 1, r - m
    left, right = [], []
    for i in range(0, len_left):
        left.append(data[l + i])
    for i in range(0, len_right):
        right.append(data[m + 1 + i])

    i, j, k = 0, 0, l
    while i < len_left and j < len_right:
        if left[i] <= right[j]:
            data[k] = left[i]
            i += 1
        else:
            data[k] = right[j]
            j += 1
        k += 1

    while i < len_left:
        data[k] = left[i]
        k += 1
        i += 1

    while j < len_right:
        data[k] = right[j]
        k += 1
        j += 1

    return data


def insertion_sort(data: list, left: int, right: int) -> list:
    for i in range(left + 1, right + 1):
        temp = data[i]
        j = i - 1
        while j >= left and data[j] > temp:
            data[j + 1] = data[j]
            j -= 1

        data[j + 1] = temp
    return data


def tim_sort(data: list, size: int = 32) -> list:
    n = len(data)
    for i in range(0, n, size):
        insertion_sort(data, i, min((i + 31), (n - 1)))

    while size < n:
        for left in range(0, n, 2 * size):
            mid = left + size - 1
            right = min((left + 2 * size - 1), (n - 1))
            merge_sort(data, left, mid, right)
        size = 2 * size
    return data


if __name__ == '__main__':
    import random
    nums = [random.randint(0, 1000) for _ in range(1000)]
    print(tim_sort(nums))

