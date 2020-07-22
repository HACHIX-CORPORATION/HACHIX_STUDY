from contracts import pre, post
from contracts import natural, integer


@pre(val=integer)
def func(val):
    #return val * 2
    pass


func('a')


