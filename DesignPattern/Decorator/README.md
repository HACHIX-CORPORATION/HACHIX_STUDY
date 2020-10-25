# Decorator 

![real world analogy](https://refactoring.guru/images/patterns/content/decorator/decorator-comic-1.png)

Thuộc trong nhóm các mô hình cấu trúc (Structural Pattern), Decorator cung cấp 
công cụ để thêm vào đối tượng những chức năng mới. 

Cách thức thực hiện: Đặt đối tượng vào những cái bọc (wrapper) đặc biệt đã được chuẩn
bị sẵn những chức  muốn thêm. 

## Mô hình cấu trúc (Structural Pattern)

Mô hình giải thích cách để tập hợp đối tượng và lớp thành một cấu trúc lớn, đồng thời 
duy trì sự linh hoạt và tính hiệu quả.

## Phân biệt Python's Decorators và Decorator Pattern

Decorator Pattern giúp lập trình viên thêm các chức năng mới vào một đối tượng có 
trước một cách linh động. Khi bạn "trang trí" một đối tượng (instance), bạn chỉ mở rộng chức 
năng của đối tượng đó chức không ảnh hưởng tới các đối tượng khác có cùng lớp (class)

Trong khi đó, Python Decorators thêm chức năng vào các hàm tại thời điểm định nghĩa hàm, 
thường không được sử dụng trong thời gian chạy. 

```python 
def identity(ob):
    return ob

@identity
def myfunc():
    print "my function"

myfunc()
print(myfunc)

# Output:
# my function
# <function myfunc at 0xb76db17c>
```

![decorator illustrator](https://refactoring.guru/images/patterns/diagrams/decorator/structure.png)

## Example 

Ví dụ lấy từ nguồn: https://www.geeksforgeeks.org/decorator-method-python-design-patterns/

### Formatting tool for Text

![Normal](https://media.geeksforgeeks.org/wp-content/uploads/20200202224344/Decorator-1.png)

![Bold](https://media.geeksforgeeks.org/wp-content/uploads/20200202224449/Decorator-2.png)

![Bold & Underline](https://media.geeksforgeeks.org/wp-content/uploads/20200202224528/Decorator-3.png)

###Advantage
- ***Quy tắc đơn trách nghiệm***： Chia một lớp với nhiều chức năng phức tạp thành những chức
năng đơn giản được gói lại trong các Decorator Pattern.
- ***Khả năng xử lí trong thời gian chạy***: Có thể thêm hoặc xoá Decorate Pattern.
- ***Thay thấy việc lớp con (Sub Classing)***: Thay vì thêm các lớp con tại thời điểm định dạng đối tượng, 
Decorator Pattern có thể dùng trong thời gian chạy.

###Disadvantage
- ***Phức tạp***: Cấu trúc lớp xếp lớp của một chuỗi Decorate Pattern sẽ khiến phần đối tượng ban đầu bị 
thay đổi quá nhiều. 
- ***Không gọn gàng***

###Ứng dụng 
- ***Không thể kế thừa***: Decorate Pattern sẽ được sử dụng trong các trường hợp không thể kế thừa để mở 
rộng chức năng của đối tượng. 

- ***Sử dụng trong thời gian chạy***: có thể gán các chức năng khác nhau và độc lập cho đối tượng. 
