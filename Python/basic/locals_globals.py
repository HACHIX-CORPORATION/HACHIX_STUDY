animal = "cat"


def test(a, b):
    """
    :param a:
    :type a:
    :param b:
    :type b:
    :return:
    :rtype:
    """
    print(locals())
    print(test.__doc__)
    return a + b


test(1, 2)
print(globals())
