class Cooker():
    def __init__(self, dung_cu, money):
        self.dung_cu = dung_cu
        self.money = money

    def di_cho(self, ten_mon, so_luong, gia_tien):

        money = self.money - gia_tien * so_luong

        return money

