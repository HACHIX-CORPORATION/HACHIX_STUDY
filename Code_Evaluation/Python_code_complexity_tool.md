#  Python_code_complexity_tool
Author: TrungPham - 2020/08/07

## 1. Một số công cụ Coverage

- Coveralls:
  - Hiển thị thông số coverage ngay trên github
  - Hỗ trợ nhiều ngôn ngữ
  - Nhiều công ty lớn sử dụng: Amazon, Google,...
  - Chi phí: 
     - 25$/tháng 10 private repos
     - 100$/tháng unlimited
  - Đánh giá:
     - Giá không quá cao
     - Phù hợp với các dự án mở, nhiều khách hàng sử dụng hơn

- Codecov:
   - Tích hợp dễ dàng vào Workflow CI
   - Tương tự coveralls
   - Chi phí:
      - Miễn phí cho tối đa 5 user 
      - 10$/user cho bản Pro
   - Đánh giá:
      - Giá rẻ (miễn phí)
      - Phù hợp các dự án nhỏ, ít user 
      - Có biểu đồ thể hiện thay đổi mức độ coverage đàng hoàng.


 ## 2. Một số metrics
https://realpython.com/python-refactoring/#code-complexity-in-python
https://radon.readthedocs.io/en/latest/intro.html

 - **Lines of Code (LOC)**
    - Càng dài càng phức tạp
 - **Cyclomatic Complexity (CC)**
    - Đo xem có bao nhiêu đường/ ngã rẽ (path) trong app
    - Càng nhiều thì càng phức tạp
 - Halstead Metrics (HMs)
    - Đo về kích thước của codebase
    - Có 4 (+3) chỉ số
       - Độ dài (N) = số thao tác + số biến 
       - Từ vựng (V (?)) = số thao tác unique + số biến unique
       - Thể tích = N * V
       - Độ khó (D) = 1/2 số thao tác * số lần tái sử dụng của biến
       - Công sức (E) = V * D
    - Càng nhiều thao tác + biến unique --> E càng to và ngược lại
    - Được đề xuất từ 1977, có nhiều thông số không còn chính xác với Python
 - **Maintainability Index (MI)**
    - Đang thử nghiệm là chính
    - Đo khả năng scale dựa trên HMs và CC
    - Thang từ 0-100
       - > 75: Dễ maintain
       - < 25: Khó maintain 
 - Time Complexity (big O) 
    --> không có module sẵn, phải tự code

 ## 3. Final choice:

 - Radon:
 	- https://radon.readthedocs.io/en/latest/index.html
 	- Có tất cả các metrics ở trên
 	- Chỉ phù hợp để đo nhanh, không phù hợp để theo dõi (monitoring)

 - **Willy**: 
    - https://github.com/tonybaloney/wily
    - Có tất cả các metrics ở trên
    - Có thể tích hợp vào CI
       - Phù hợp để theo dõi thay đổi (monitoring)


## 4. Comment:

 - Những công cụ này nên dùng để đánh giá vào phút cuối hoặc refactoring, không nên lúc nào cũng test 
 --> Ảnh hưởng đến productivity   