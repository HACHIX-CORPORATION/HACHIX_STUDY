# Memo: 内部関数を利用する場合
# 定義する関数は外部の関数だけを利用したい時


def outer(a, b):
    def plus(c, d):
        return c + d

    r1 = plus(a, b)
    r2 = plus(b, a)
    print(r1 + r2)


outer(1, 2)
