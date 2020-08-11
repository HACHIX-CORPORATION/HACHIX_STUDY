# coding: utf-8
"""

Abstract::
    - 
History::
    - Ver.      Date            Author        History
    - 
Copyright (C) 2020 HACHIX Corporation. All Rights Reserved.
"""
# 標準ライブラリ


# 関連外部ライブラリ


# 内部ライブラリ

def function(string):
    return string


def decorator(wrapped):
    def wrap(string):
        # Assume that this is something useful
        return wrapped(string.upper())
    return wrap


def method_decorator(wrapped):
    def wrap(instance, string):
        # Assume that this is something useful
        return wrapped(instance, string.upper())
    return wrap


@decorator
def decorated_function(string):
    print('! '.join(string.split(' ')))


if __name__ == '__main__':
    string = 'Học ăn học nói học gói mang về'
    print("Plain function: ", function(string))               # Plain function
    print("\nPython decorators")
    print("at run time: ", decorator(function)(string))       # Python decorator at run time
    print("at definition time", decorated_function(string))   # Python decorator at definition time

