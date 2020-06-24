# Hoc Về Function, Return
# 1. Định nghĩa
# 2. Thành phần trong function (Return)

# Tuệ: Function là trong đấy chứa những method
# Tuấn, Duy: Function là cái thực hiện hành động
# Cấu tạo của function
# tên:
# tham số:
# Giá trị trả lại: kết quả

money = 1000


def danhBac(danh_vơi_ai, bet_money):
    left_money = money - bet_money

    return left_money

# Bài toán lớn
# Bài toán nhỏ

# Task1: đọc file csv và vẽ biểu đồ

# money
# 1 100
# 2 200
# 3 300


def task1():
    # doc file csv
    print("task1 called")
    data = read_csv()
    print(type(data))
    print("hoge")
    print(data[0])  # Tue

    # ve bieu do
    render_graph(data, 'Graph')


def read_csv():
    print("read_csv called")
    column1_name = "gai"
    column2_money = 1000

    return column1_name, column2_money


def render_graph(graph_data, title):
    print("render_graph called")
    print(graph_data)   # abc
    print(title)     # Graph


if __name__ == "__main__":
    print("Start")
    task1()








