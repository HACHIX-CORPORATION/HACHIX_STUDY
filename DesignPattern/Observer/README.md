# Observer

## 説明

Observerパターンとは、プログラム内のオブジェクトのイベント( 事象 )を
他のオブジェクトへ通知する処理で使われるデザインパターンの一種。




![observer](https://refactoring.guru/images/patterns/content/observer/observer.png)

Thuộc trong nhóm các mô hình chức năng, cung cấp một **cơ chế đăng kí** nhằm thông báo cho
nhiều đối tượng đang về bất cứ sự kiện xảy ra đối với đối tượng đang bị theo dõi. 

Observer miêu tả mối quan hệ giữa một publisher, có thể biết đến như observable và nhiều subscriber, 
hay còn được gọi với cái tên khác là Observer. 

## Mô hình chức năng 

Bao gồm các mô hình liên quan đến các thuật toán và phép gán trách nghiệm giữa các dối tượng. 

![observer](https://refactoring.guru/images/patterns/diagrams/observer/structure.png)

## Ứng dụng 
- ***Mô hình Model-View-Controller (MVC)***: Giả sử hai View hoặc nhiều hơn dùng chung dữ liệu từ một Model, 
ví dụ như một biều đồ và một tệp excel. Trong trường hợp này, khi phần Model được cập nhật, cả hai View 
cần được cập nhập theo. -> Observer Pattern 

- ***Dash***: Dash sử dụng các hàm callbacks để kiểm soát sự thay đổi của các thành phần\ 
Layout(field) = Observable \
Callbacks     = Observer

- ***Django-observer***: Ghi vào đây để sau dùng. 

## Advantages 
- ***Kết nối trong thời gian chạy***: 
- ***Quy tắc đóng/mở***: Có thể thêm/xoá các subscriber mà không làm ảnh hưởng đến các publisher 

## Disadvantages 
- ***Thứ tự***: Thứ tự xử lí của các subscriber là ngẫu nhiên. 
