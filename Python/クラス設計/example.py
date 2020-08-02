# ref: https://qiita.com/tag1216/items/13b032348c893667862a

from dataclasses import dataclass
from datetime import date


@dataclass
class User:
    last_name: str
    first_name: str
    birthday: date

