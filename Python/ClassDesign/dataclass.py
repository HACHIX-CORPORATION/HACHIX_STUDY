from dataclasses import dataclass
from datetime import date


@dataclass
class User:
    username: int
    email: str
    last_name: str
    first_name: str
    role: str
    mail_confirmed: bool=False


user = User('A', 'B', 'C', 'D', 'E')





