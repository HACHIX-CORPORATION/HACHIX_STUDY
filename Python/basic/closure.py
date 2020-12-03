def outer(a, b):
    def inner():
        # この関数は外部の引数の値を参照することができる。
        return a + b

    return inner


f = outer(1, 2)  # この時、innerの関数はまだ実行されていない
r = f()  # この時、初めて、innerの関数を実行する
print(r)


# Ex2
def circle_area_func(pi):
    def cicle_area(radius):
        return pi * radius * radius

    return cicle_area


ca1 = circle_area_func(3.14)
ca2 = circle_area_func(3.1459)

print(ca1(10))
print(ca2(20))

