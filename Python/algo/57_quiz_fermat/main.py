# Fermat's Last Theorem x**2 + y**2 = z**2
# 3**2 + 4**2 == 5**2 OR 6**2 + 8**2 == 10**2
# Input 10, 2 => [(3, 4, 5), (6, 8, 10)]
# (x or y <= 10)
# Input 10, 3 => []
# Input 10, 4 => []
# Input 10, 5 => []
import sys
from typing import List, Tuple


def fermat_last_theorem_v1(max_num: int, square_num: int) -> List[Tuple[int, int, int]]:
    result = []
    if square_num < 2:
        return result

    max_z = int(pow((max_num - 1) ** 2 + max_num ** 2, 1.0 / square_num))
    for x in range(1, max_num + 1):
        for y in range(x+1, max_num + 1):
            for z in range(y+1, max_z):
                if pow(x, square_num) + pow(y, square_num) == pow(z, square_num):
                    result.append((x, y, z))
    return result


def fermat_last_theorem_v2(max_num: int, square_num: int) -> List[Tuple[int, int, int]]:
    result = []
    if square_num < 2:
        return result

    for x in range(1, max_num + 1):
        for y in range(x+1, max_num + 1):
            pow_sum = pow(x, square_num) + pow(y, square_num)

            if pow_sum > sys.maxsize:
                raise ValueError(x, y, z, square_num, pow_sum)

            z = pow(pow_sum, 1.0 / square_num)
            if not z.is_integer():
                continue

            z = int(z)
            z_pow = pow(z, square_num)
            if z_pow == pow_sum:
                result.append((x, y, z))
    return result


if __name__ == '__main__':
    import time

    for n in range(2, 10):
        start = time.time()
        print('v1', fermat_last_theorem_v1(20, n))
        print('v1', 'time =', time.time() - start)

        start = time.time()
        print('v2', fermat_last_theorem_v2(20, n))
        print('v2', 'time =', time.time() - start)
