import datetime
from datetime import date


class User:
    def __init__(self, username, birthday):
        self.username = username
        self.birthday = birthday
        self.age = None

    def cal_age(self):
        today = date.today()

        age = today.year - self.birthday.year

        self.age = age

    def age_display(self):
        print(self.age)


user1 = User('thanh', datetime.datetime.strptime('1984-02-15', '%Y-%m-%d').date())
user1.age_display()


