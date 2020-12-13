"""
1. Check palindrome
aba => True
abc => False
racecar => True

2. Find palindrome
abcracecarbda => cec, aceca, racecar

racecar
"""
from typing import Generator


def is_palindrome(strings: str) -> bool:
    len_strings = len(strings)
    if not len_strings:
        return False
    if len_strings == 1:
        return True

    start, end = 0, len_strings - 1
    while start < end:
        if strings[start] != strings[end]:
            return False
        start += 1
        end -= 1
    return True


def find_palindrome(strings: str, left: int, right: int) -> Generator[str, None, None]:
    while 0 <= left and right <= len(strings) - 1:
        if strings[left] != strings[right]:
            break
        yield strings[left: right+1]
        left -= 1
        right += 1


def find_all_palindrome(strings: str) -> Generator[str, None, None]:
    len_strings = len(strings)
    if not len_strings:
        yield
    if len_strings == 1:
        yield strings

    for i in range(1, len_strings-1):
        yield from find_palindrome(strings, i-1, i+1)
        yield from find_palindrome(strings, i-1, i)


if __name__ == '__main__':
    for s in find_all_palindrome('fdafiewaafcabacdfafdaf'):
        print(s)
