"""
Input 568-379-8466 Output [..., 'LOVEPYTHON', ... ]
Input 435-569-6753 Output [..., 'HELLOWORLD', ...]
"""
from typing import List, NewType


PhoneAlphabet = NewType('PhoneAlphabet', str)

# NUM_ALPHABET_MAPPING = {
#     0: PhoneAlphabet('+'),
#     1: PhoneAlphabet('@'),
#     2: PhoneAlphabet('ABC'),
#     3: PhoneAlphabet('DEF'),
#     4: PhoneAlphabet('GHI'),
#     5: PhoneAlphabet('JKL'),
#     6: PhoneAlphabet('MNO'),
#     7: PhoneAlphabet('PQRS'),
#     8: PhoneAlphabet('TUV'),
#     9: PhoneAlphabet('WXYZ')
# }

NUM_ALPHABET_MAPPING = {
    0: '+',
    1: '@',
    2: 'ABC',
    3: 'DEF',
    4: 'GHI',
    5: 'JKL',
    6: 'MNO',
    7: 'PQRS',
    8: 'TUV',
    9: 'WXYZ'
}

def phone_mnemonic_v1(phone_number: str) -> List[str]:
    phone_number = [int(s) for s in phone_number.replace('-', '')]
    candidate = []
    tmp= [''] * len(phone_number)

    def find_candidate_alphabet(digit: int = 0) -> None:
        if digit == len(phone_number):
            candidate.append(''.join(tmp))
        else:
            for char in NUM_ALPHABET_MAPPING[phone_number[digit]]:
                tmp[digit] = char
                find_candidate_alphabet(digit+1)

    find_candidate_alphabet()
    return candidate


# def phone_mnemonic_v1(phone_number: str) -> List[str]:
#     phone_number: List[int] = [int(s) for s in phone_number.replace('-', '')]
#     candidate: List[PhoneAlphabet] = []
#     tmp: List[PhoneAlphabet] = [PhoneAlphabet('')] * len(phone_number)
#
#     def find_candidate_alphabet(digit: int = 0) -> None:
#         if digit == len(phone_number):
#             candidate.append(''.join(tmp))
#         else:
#             for char in NUM_ALPHABET_MAPPING[phone_number[digit]]:
#                 tmp[digit] = char
#                 find_candidate_alphabet(digit+1)
#
#     find_candidate_alphabet()
#     return candidate


def phone_mnemonic_v2(phone_number: str) -> List[str]:
    phone_number = [int(s) for s in phone_number.replace('-', '')]
    candidate = []
    stack = ['']

    while len(stack) != 0:
        alphabets = stack.pop()
        if len(alphabets) == len(phone_number):
            candidate.append(alphabets)
        else:
            for char in NUM_ALPHABET_MAPPING[phone_number[len(alphabets)]]:
                stack.append(alphabets + char)
    return candidate


# def phone_mnemonic_v2(phone_number: str) -> List[str]:
#     phone_number: List[int] = [int(s) for s in phone_number.replace('-', '')]
#     candidate: List[PhoneAlphabet] = []
#     stack: List[PhoneAlphabet] = [PhoneAlphabet('')]
#
#     while len(stack) != 0:
#         alphabets = stack.pop()
#         if len(alphabets) == len(phone_number):
#             candidate.append(alphabets)
#         else:
#             for char in NUM_ALPHABET_MAPPING[phone_number[len(alphabets)]]:
#                 stack.append(PhoneAlphabet(alphabets + char))
#     return candidate


if __name__ == '__main__':
    for s in phone_mnemonic_v2('23'):
            print(s)

    for s in phone_mnemonic_v1('568-379-8466'):
        if 'LOVEPYTHON' in s:
            print(s)

    for s in phone_mnemonic_v2('568-379-8466'):
        if 'LOVEPYTHON' in s:
            print(s)


