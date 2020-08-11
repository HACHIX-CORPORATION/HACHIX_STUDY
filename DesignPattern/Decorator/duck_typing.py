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

class Specialstring:
    def __len__(self):
        return 21


# Driver's code
if __name__ == "__main__":
    string = Specialstring()
    print(len(string))
