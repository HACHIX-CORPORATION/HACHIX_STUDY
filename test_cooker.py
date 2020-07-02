# Step1
import unittest
from cooker import Cooker


# Step2: Tao Class Test
class TestCooker(unittest.TestCase):
    @classmethod
    def setUpClass(cls) -> None:
        # goi 1 lan duy nhat khi chay file Test
        # tao ra object/instance de test
        cls.obj = Cooker(dung_cu='Chao', money=10000)

    @classmethod
    def tearDownClass(cls) -> None:
        pass

    # Step3: tao test case
    # 手順: di_cho('vit', soluong=2, gia_tien=1000)
    # 期待結果: sau khi di cho con lai bao nhieu tien 8000
    def test_di_cho_01(self):
        money = self.obj.di_cho(ten_mon='vit', so_luong=2, gia_tien=1000)
        expectation = 8000
        self.assertEqual(money, expectation)

    def test_mua_dung_cu_01(self):
        self.obj.di_cho(ten_mon='vit', so_luong=2, gia_tien=1000)
        money2 = self.obj.mua_dung_cu(ten_dung_cu='noi', so_luong=1, gia_tien=2300)
        expectation = 8000 - 4300
        self.assertEqual(money2, expectation)


# Step4: chay test case
if __name__ == '__main__':
    unittest.main(failfast=True)

# Step5: pip install coverage

# Step6: coverage run test_cooker.py

# Step7: coverage html




