import unittest

from main import is_prime_v4 as is_prime
from array import order_even_first_odd_last


class Test(unittest.TestCase):

    def test_order_even_first_odd_last_ok(self):
        l = [1, 3, 2, 4, 11, 29, 8]
        order_even_first_odd_last(l)
        self.assertListEqual(l, [8, 4, 2, 11, 29, 3, 1])


if __name__ == '__main__':
    unittest.main()
