class Cooker():
    def __init__(self, dung_cu, money):
        self.dung_cu = dung_cu
        self.money = money

    def di_cho(self, ten_mon, so_luong, gia_tien):
        self.money = self.money - gia_tien * so_luong

        return self.money

    def mua_dung_cu(self, ten_dung_cu, so_luong, gia_tien):

        if ten_dung_cu == 'BepGa':
            return

        self.money = self.money - gia_tien * so_luong

        return self.money

