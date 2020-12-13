import string
from typing import List


ALPHABET = string.ascii_uppercase


class PlugBoard(object):

    def __init__(self, map_alphabet: str) -> None:
        self.alphabet = ALPHABET
        self.forward_map = {}
        self.backward_map = {}
        self.mapping(map_alphabet)

    def mapping(self, map_alphabet: str) -> None:
        self.forward_map = dict(zip(self.alphabet, map_alphabet))
        self.backward_map = {v: k for k, v in self.forward_map.items()}

    def forward(self, index_num: int) -> int:
        char = self.alphabet[index_num]
        char = self.forward_map[char]
        return self.alphabet.index(char)

    def backward(self, index_num: int) -> int:
        char = self.alphabet[index_num]
        char = self.backward_map[char]
        return self.alphabet.index(char)


class Rotor(PlugBoard):

    def __init__(self, map_alphabet: str, offset: int = 1) -> None:
        super().__init__(map_alphabet)
        self.offset = offset
        self.rotations = 0

    def rotate(self, offset: int =None) -> int:
        if offset is None:
            offset = self.offset
        self.alphabet = self.alphabet[offset:] + self.alphabet[:offset]
        self.rotations += offset
        return self.rotations

    def reset(self) -> None:
        self.rotations = 0
        self.alphabet = ALPHABET


class Reflector(object):

    def __init__(self, map_alphabet: str) -> None:
        self.map = dict(zip(ALPHABET, map_alphabet))
        for x, y in self.map.items():
            if x != self.map[y]:
                raise ValueError(x, y)

    def reflect(self, index_num: int) -> int:
        reflected_char = self.map[ALPHABET[index_num]]
        return ALPHABET.index(reflected_char)


class EnigmaMachine(object):

    def __init__(self, plug_board: PlugBoard, rotors: List[Rotor], reflector: Reflector) -> None:
        self.plug_board = plug_board
        self.rotors = rotors
        self.reflector = reflector

    def encrypt(self, text: str) -> str:
        return ''.join([self.go_through(c) for c in list(text)])

    def decrypt(self, text: str) -> str:
        for rotor in self.rotors:
            rotor.reset()

        return ''.join([self.go_through(c) for c in list(text)])

    def go_through(self, char: str) -> str:
        char = char.upper()
        if char not in ALPHABET:
            return char

        index_num = ALPHABET.index(char)
        index_num = self.plug_board.forward(index_num)

        for rotor in self.rotors:
            index_num = rotor.forward(index_num)

        index_num = self.reflector.reflect(index_num)

        for rotor in reversed(self.rotors):
            index_num = rotor.backward(index_num)

        index_num = self.plug_board.backward(index_num)

        char = ALPHABET[index_num]

        for rotor in reversed(self.rotors):
            if rotor.rotate() % len(ALPHABET) != 0:
                break

        return char
