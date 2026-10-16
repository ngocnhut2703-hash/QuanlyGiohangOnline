# Bộ khung TV1 - Quản lý giỏ hàng online

Đây là bản thiết kế đề xuất cho phần **thiết kế cấu trúc dữ liệu và khai báo
hàm**. Đã có cấu trúc Product, Node, Cart và phần hỗ trợ quản lý bộ nhớ.
Nhóm cần thống nhất giao diện này trước khi các thành viên viết chức năng.

## 1. Làm ngay trên Windows bằng VS Code

1. Giải nén để có thư mục `D:\OnlineShoppingCart_TV1` chứa `Product.h`,
   `Cart.h`, `Cart.cpp`, `README.md` và thư mục `examples`.
2. Mở VS Code, chọn **File > Open Folder**, mở `D:\OnlineShoppingCart_TV1`.
3. Chọn **Terminal > New Terminal**. Với PowerShell, chạy lần lượt:

```powershell
cd D:\OnlineShoppingCart_TV1
g++ --version
g++ -std=c++17 -Wall -Wextra -pedantic examples/demo_tv1.cpp Cart.cpp -o demo_tv1.exe
.\demo_tv1.exe
```

Chỉ chạy lệnh tiếp theo khi lệnh trước không báo lỗi. Nếu `g++` không được
nhận diện, cần kiểm tra bộ biên dịch C++ và PATH trước khi chạy tiếp.
Nút Run chỉ biên dịch file đang mở có thể bỏ sót `Cart.cpp`; dùng đúng lệnh
trên để biên dịch cả hai file.

Kết quả mong đợi:

```text
1. Gio moi khoi tao: RONG
2. San pham mau: SP001 | Ban phim | 250000 VND | So luong: 2
3. Di toi bang next: SP002
4. Di lui bang prev: SP001
KET QUA: KHUNG TV1 CHAY DUOC.
```

Demo chỉ kiểm tra và minh họa bộ khung TV1. Hai node trong demo chưa thuộc
giỏ hàng. Chương trình đầy đủ sẽ được ghép sau khi các thành viên hoàn tất
phần cài đặt của mình.

## 2. Đọc và thực hành theo thứ tự

1. **Product.h**: đọc `Product` trước. Đổi tên sản phẩm mẫu trong demo,
   biên dịch và chạy lại để thấy giá trị thay đổi.
2. **Node trong Product.h**: xem `data`, `prev`, `next`. Theo dõi tại sao
   `first.next` đi tới SP002 và `second.prev` quay về SP001.
3. **Cart.h**: xem `head`, `tail`, `private`, `public` và các khai báo hàm.
4. **Cart.cpp**: xem khởi tạo giỏ rỗng, tìm ID và giải phóng node.

Khai báo như `bool addItem(const Product& product);` cho biết tên hàm,
tham số và kiểu trả về. Phần định nghĩa chứa các lệnh xử lý sẽ do TV2 viết.
Từ khóa `const` sau hàm như `calculateTotal() const` có nghĩa hàm không
thay đổi các thành viên của đối tượng Cart thông qua `this`; người cài đặt
cũng cần giữ nguyên dữ liệu các node khi viết các hàm chỉ đọc.

## 3. Thiết kế dữ liệu đề xuất

| Thành phần | Kiểu | Ý nghĩa |
| --- | --- | --- |
| Product.id | string | Mã hàng, ví dụ SP001; phân biệt hoa/thường |
| Product.name | string | Tên mặt hàng |
| Product.price | long long | Đơn giá nguyên theo VND |
| Product.quantity | int | Số lượng trong giỏ |
| Node.data | Product | Thông tin mặt hàng của node |
| Node.prev / Node.next | Node* | Liên kết trước / sau |
| Cart.head / Cart.tail | Node* | Node đầu / cuối |

Các quy tắc đề xuất để cả nhóm xác nhận:

- ID và tên không được rỗng hoặc chỉ gồm khoảng trắng; giá và số lượng > 0.
- Thêm trùng ID: cộng số lượng vào node cũ, giữ nguyên tên và giá đang có.
- Sửa số lượng chỉ nhận giá trị > 0. Muốn bỏ mặt hàng thì gọi `removeItem`.
- Các phép cộng số lượng và tính tiền phải kiểm tra tràn kiểu số trước khi
  cập nhật. Nếu không thể biểu diễn bằng kiểu đã chọn, báo lỗi thay vì
  tiếp tục tính sai. `calculateTotal` có thể ném `std::overflow_error`;
  TV6 cần bắt ngoại lệ và thông báo khi tích hợp menu.
- Giỏ rỗng: cả head và tail bằng nullptr. Giỏ có hàng: head->prev và
  tail->next bằng nullptr; hai node liền nhau phải nối đúng cả hai chiều.
- Cart sở hữu các node tạo bằng `new`; `clear()` và destructor giải phóng
  chúng. Không gán node cục bộ trong demo vào Cart.
- Chặn sao chép Cart để tránh hai giỏ cùng sở hữu và giải phóng một node.
  Khi truyền giỏ cho chức năng khác, dùng tham chiếu `Cart&` hoặc `const Cart&`.

## 4. Giao diện bàn giao cho các thành viên

| Thành viên | Chữ ký hàm cần cài đặt | Quy ước |
| --- | --- | --- |
| TV2 | bool Cart::addItem(const Product& product) | true khi thêm/cộng số lượng thành công; false nếu dữ liệu không hợp lệ hoặc số lượng/tổng tiền không thể biểu diễn; thất bại phải giữ nguyên giỏ |
| TV3 | void Cart::displayCart() const | In thông tin, thành tiền, tổng tiền; xử lý giỏ trống |
| TV3 | long long Cart::calculateTotal() const | Tổng giá × số lượng; giỏ trống trả 0; phát hiện tràn số |
| TV4 | bool Cart::updateQuantity(const std::string& id, int newQuantity) | true khi cập nhật; false nếu không tìm thấy, số lượng sai hoặc tổng tiền không thể biểu diễn; thất bại giữ nguyên giỏ |
| TV4 | bool Cart::removeItem(const std::string& id) | true khi xóa; false nếu không tìm thấy ID |
| TV5 | bool createOrder(const Cart& cart) | Hàm tự do đề xuất trong Order.h/Order.cpp; false nếu giỏ trống; true khi tạo/in đơn thành công |
| TV6 | int main() | Viết menu, kiểm tra nhập liệu và tích hợp |

Chữ ký tạo đơn của TV5 là đề xuất cần thống nhất. TV5 có thể đọc danh sách
qua `getHead()` và gọi `calculateTotal()` sau khi TV3 cài đặt. Với chữ ký
`const Cart&`, chức năng tạo đơn chỉ đọc giỏ; nếu nhóm muốn xóa giỏ sau khi
tạo đơn, cần thống nhất lại chữ ký và hành vi trước khi viết.

TV2/TV3/TV4 có thể định nghĩa hàm trong `CartAdd.cpp`, `CartView.cpp`,
`CartEditDelete.cpp`, mỗi file `#include "Cart.h"`. Hàm thành viên của Cart
vẫn truy cập được head, tail và findItem dù định nghĩa ở file .cpp riêng.
Mỗi hàm chỉ được định nghĩa một lần trong toàn chương trình.

**Các hàm TV2/TV3/TV4 hiện chỉ được khai báo**, chưa có phần xử lý hoặc
giá trị giả để che việc thiếu chức năng. Nếu gọi chúng trước khi bổ sung
phần định nghĩa, bộ liên kết sẽ báo lỗi `undefined reference`.

TV6 tạo `main.cpp` riêng ở thư mục gốc. `examples/demo_tv1.cpp` có `main`
riêng nên chỉ biên dịch nó cho demo TV1; không ghép nó với `main.cpp` của TV6.
Khi ghép dự án, biên dịch tất cả file cài đặt cần dùng cùng `main.cpp`.

## 5. Tiêu chí hoàn thành phần TV1

- Product, Node, head, tail và các khai báo hàm nhất quán.
- Đã có khởi tạo, giải phóng bộ nhớ và hàm tìm theo ID dùng chung.
- Demo TV1 biên dịch và chạy được bằng lệnh ở mục 1.
- Cả nhóm đã xác nhận kiểu dữ liệu, chữ ký hàm và các quy tắc ở mục 3-4.
- Bạn giải thích được Product, Node, prev/next, head/tail và khai báo hàm.

Phần thêm, xem, sửa/xóa, tạo đơn, menu và các kiểm thử nghiệp vụ của toàn
dự án sẽ được thực hiện tiếp theo theo phân công.
