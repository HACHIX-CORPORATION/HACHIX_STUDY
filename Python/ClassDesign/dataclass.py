from dataclasses import dataclass
from datetime import date


@dataclass
class User:
    username: str
    email: str
    last_name: str
    first_name: str
    role: str
    mail_confirmed: bool=False

    def print_full_name(self):
        print(self.first_name + self.last_name)


user = User('A', 'B', 'C', 'D', 'E')
user.print_full_name()




