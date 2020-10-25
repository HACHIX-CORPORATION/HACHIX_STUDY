＃CSS Best Practices
Author: Trung Pham - Date: 2020/08/07


## Thường xuyên dùng comment cho mỗi block/session code

- Lý do:
   - Để người khác biết mình đang làm gì
   - Dễ tìm kiếm khi scroll
- Examples:

```
/* */

```

## Sắp xếp thứ tự Top-Down

- Đi từ lớn dần đến nhỏ dần
- Lý do:
   - Dễ tìm vị trí của element cần xử lý 
   - Theo quy tắc cứ thằng sau sẽ đè thằng trước nên những style các specific(dành riêng) thì càng nên viết cuối.
- Examples:
```
.Generic classes (body, a, p, h1, etc.)
#header
#nav-menu
#main-content
```


## Hạn chế tối đa sử dụng <style> --> class

- Lý do:
   - Sẽ có những chỗ thay đổi mà không biết fix ở đâu. 
   - Mỗi element sẽ có 1 kiểu hiển thị khác nhau, không thống nhất
   - Mỗi khi sửa phải tìm về file html --> Html chỉ dùng để quy định cấu trúc, không phải quy định style


## Sử dụng multi classes --> class dùng chung và class riêng

- Lý do:
  - Share những thuộc tính giữa các element nhưng vẫn đảm bảo thuộc tính riêng nếu cần --> Class sau đè class trước. 

- Examples:
```
<div class="container container-disable"> </div>

```

## Cách đặt tên class --> Sử dụng BEM 

- http://getbem.com/naming/
- BEM = Block + Element + Modified
- Examples:

```
.container {
	...
}

.container__input {
	...
}

.container--disable {
	...
}

```

## Sử dụng nhiều stylesheets 

- Lý do:
   - Tương tự như code, một file css quá lớn thường khó đọc và chỉnh sửa
   --> Mỗi screens có thể có một .css file bên cạnh một file .css chung 

- Nhược điểm: 
   - Khi sử dụng app có thể sẽ cần nhiều HTTP requests
   --> Khắc phục bằng minification 


## Tránh sử dụng px --> dùng em, vh, vw 

- Lý do:
   - pixel (px) là đơn vị --> kém linh hoạt khi kích thước màn hình/ trình duyệt thay đổi.
   - vh, vw --> Sử dụng tỷ lệ tương đối so với kích thước hiện tại của viewport
   - em --> Sử dụng tỷ lệ tương đối với font mặc định của viewport


## Tránh sử dụng selector quá đặc biệt nếu có thể dùng selector ngắn gọn

- Lý do:
   - Thêm nhiều selector không làm cho code bị lỗi, tuy nhiên khó đọc và "bẩn" --> KISS

- Examples:
```
/* BAD */
body #container .someclass ul li {....}

/* GOOD */
.someclass li {...}
```


## Sử dụng element đúng chỗ, đúng lúc

- Lý do:
   - Để thêm class cho một element, có cách đơn giản là thêm 1 div bao lấy element đó rồi set class --> Code rườm rà và khó nhìn --> KISS

- Examples:
```
/* BAD */
<div class="header-text"><h1>Header Text</h1></div>


/* GOOD */
<h1>Header Text</h1>
```