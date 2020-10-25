# def is_valid(article):
#     if article.title == "":
#         return False    # đến đoạn này thì rời khỏi function
#
#     article.valid = True
#     article.save()
#
#     return True
#
# # Tuấn: ok
# # Thành: chưa ok lắm: return tại 2 chỗ khác nhau ko tốt
#
#
# def is_valid2(article):
#     ret = True
#     if article.title == "":
#         ret = False
#
#     article.valid = True
#     article.save()  # thao tác ko suy diến được từ tên fu
#
#     return ret


def foo(values=[]):
    values.append("Hi")
    print(values)
    return values

# Tuệ: tên function ko rõ ý nghĩa

foo()   # "Hi"
foo()   # "Hi"

# def append_value(values=None):
#     if values is None:
#         values = []
#     values.append("Hi")
#     print(values)
#     return values
#
# append_value()   # "Hi"
# append_value()   # "Hi"


def calc_tax_included(item, tax_rate=0.1):
    return item['price'] * (1 + tax_rate)

# Duy: thêm chức năng check key price có tồn tại hay ko?
# check type data of item['price']
# check type data of tax_rate
# để tăng tính reuse cho function có thể viết như sau
def calc_tax_included(price, tax_rate=0.1):
    return price * (1 + tax_rate)
