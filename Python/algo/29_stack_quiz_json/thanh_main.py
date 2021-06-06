"""
Input {'key1': 'value1', 'key2': [1, 2, 3], 'key3': (1, 2, 3)}  Output True
Input [{'key1': 'value1', 'key2': [1, 2, 3], 'key3': (1, 2, 3)} Output False
"""


def validate_format(chars: str) -> bool:
    return False


if __name__ == '__main__':
    import json
    d = {'key1': 'value1', 'key2': [1, 2, 3], 'key3': (1, 2, 3)}
    s = json.dumps(d)
    print(s)
    print(validate_format(s))
    s += '('
    print(s)
    print(validate_format(s))
