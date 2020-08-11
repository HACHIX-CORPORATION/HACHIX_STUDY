import datetime
from datetime import date


class User:
    def __init__(self, username, birthday):
        self.username = username
        self.birthday = birthday
        self.age = None

    def cal_age(self):
        # today = date.today()
        #
        # age = today.year - self.birthday.year
        #
        # self.age = age

        self.age = date.today() - self.birthday.year

    def age_display(self):
        print(self.age)


user1 = User('thanh', datetime.datetime.strptime('1984-02-15', '%Y-%m-%d').date())
user1.age_display()

# Duy: thiếu comment và check type của birthday
# Trung: muốn chạy age_display thì phải chạy cal_age -> tính độc lập của age_display bị thiếu
# Thành: cal_age có thể viết ngắn hơn
# Khon
#


