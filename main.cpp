#include "Cart.h"
#include "Order.h"

#include <charconv>
#include <cctype>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <system_error>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

namespace {

string trim(const string& input) {
    const string whitespace = " \t\r\n";
    size_t first = input.find_first_not_of(whitespace);
    if (first == string::npos) return "";
    size_t last = input.find_last_not_of(whitespace);
    return input.substr(first, last - first + 1);
}

string readLine(const string& prompt) {
    cout << prompt << flush;
    string line;
    if (!getline(cin, line)) {
        throw runtime_error("Không còn dữ liệu nhập (EOF).");
    }
    return line;
}

long long readNumber(const string& prompt, long long minimum, long long maximum) {
    while (true) {
        string line = trim(readLine(prompt));
        if (line.empty()) {
            cout << "Vui lòng nhập một số nguyên.\n";
            continue;
        }
        long long value = 0;
        const char* first = line.data();
        const char* last = first + line.size();
        auto result = from_chars(first, last, value);
        if (result.ec != errc{} || result.ptr != last) {
            cout << "Vui lòng nhập số nguyên hợp lệ, không kèm ký tự thừa!\n";
            continue;
        }
        if (value < minimum || value > maximum) {
            cout << "Giá trị phải nằm trong khoảng [" << minimum << ", " << maximum << "].\n";
            continue;
        }
        return value;
    }
}

string readText(const string& prompt) {
    while (true) {
        string value = trim(readLine(prompt));
        if (!value.empty()) return value;
        cout << "Nội dung không được để trống.\n";
    }
}

bool confirm(const string& question) {
    while (true) {
        string answer = trim(readLine(question + " (y/n): "));
        if (answer == "y" || answer == "Y") return true;
        if (answer == "n" || answer == "N") return false;
        cout << "Vui lòng nhập 'y' (đồng ý) hoặc 'n' (hủy).\n";
    }
}

void searchProduct(const Cart& cart) {
    string id = readText("Nhập mã sản phẩm cần tìm: ");
    for (const Node* node = cart.getHead(); node != nullptr; node = node->next) {
        if (node->data.id == id) {
            cout << "\n--- THÔNG TIN SẢN PHẨM ---\n"
                 << "  Mã SP     : " << node->data.id << '\n'
                 << "  Tên SP    : " << node->data.name << '\n'
                 << "  Đơn giá   : " << node->data.price << " VND\n"
                 << "  Số lượng  : " << node->data.quantity << '\n'
                 << "  Thành tiền: " << node->data.price * node->data.quantity << " VND\n";
            return;
        }
    }
    cout << "=> Không tìm thấy sản phẩm có mã \"" << id << "\".\n";
}

void showMenu() {
    cout << "\n================ QUẢN LÝ GIỎ HÀNG ONLINE ================\n"
         << "1. Thêm sản phẩm vào giỏ hàng\n"
         << "2. Xem danh sách giỏ hàng\n"
         << "3. Cập nhật số lượng sản phẩm\n"
         << "4. Xóa sản phẩm khỏi giỏ hàng\n"
         << "5. Tạo đơn hàng (Thanh toán / In hóa đơn)\n"
         << "6. Xóa toàn bộ giỏ hàng\n"
         << "7. Tìm sản phẩm theo mã\n"
         << "0. Thoát chương trình\n"
         << "=========================================================\n";
}

void setupConsoleVietnamese() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
}

} // namespace

int main() {
    setupConsoleVietnamese();

    Cart cart;
    cout << "CHƯƠNG TRÌNH QUẢN LÝ GIỎ HÀNG ONLINE\n";

    try {
        while (true) {
            showMenu();
            int choice = static_cast<int>(readNumber("Lựa chọn của bạn (0-7): ", 0, 7));
            if (choice == 0) {
                cout << "\nCảm ơn bạn đã sử dụng chương trình!\n";
                break;
            }

            try {
                switch (choice) {
                    case 1: {
                        Product product;
                        cout << "\n--- THÊM SẢN PHẨM ---\n";
                        product.id = readText("Nhập mã sản phẩm (ID): ");
                        product.name = readText("Nhập tên sản phẩm: ");
                        product.price = readNumber("Nhập đơn giá (VND): ", 1, numeric_limits<long long>::max());
                        product.quantity = static_cast<int>(readNumber("Nhập số lượng: ", 1, numeric_limits<int>::max()));
                        if (cart.addItem(product)) {
                            cout << "=> Thêm vào giỏ hàng thành công!\n";
                        } else {
                            cout << "=> Thêm thất bại! Dữ liệu không hợp lệ hoặc tổng tiền vượt giới hạn.\n";
                        }
                        break;
                    }
                    case 2:
                        cout << "\n--- DANH SÁCH GIỎ HÀNG ---\n";
                        cart.displayCart();
                        break;
                    case 3: {
                        cout << "\n--- CẬP NHẬT SỐ LƯỢNG ---\n";
                        string id = readText("Nhập mã sản phẩm cần sửa: ");
                        int quantity = static_cast<int>(readNumber("Nhập số lượng mới: ", 1, numeric_limits<int>::max()));
                        cout << (cart.updateQuantity(id, quantity)
                                     ? "=> Cập nhật số lượng thành công!\n"
                                     : "=> Không tìm thấy sản phẩm hoặc số lượng không hợp lệ!\n");
                        break;
                    }
                    case 4: {
                        cout << "\n--- XÓA SẢN PHẨM ---\n";
                        string id = readText("Nhập mã sản phẩm cần xóa: ");
                        cout << (cart.removeItem(id)
                                     ? "=> Đã xóa sản phẩm khỏi giỏ hàng!\n"
                                     : "=> Không tìm thấy sản phẩm có mã này!\n");
                        break;
                    }
                    case 5:
                        cout << "\n--- XÁC NHẬN TẠO ĐƠN HÀNG ---\n";
                        if (createOrder(cart)) {
                            cout << "=> Đơn hàng đã được tạo thành công!\n";
                        }
                        break;
                    case 6:
                        cout << "\n--- XÓA TOÀN BỘ GIỎ HÀNG ---\n";
                        if (cart.isEmpty()) {
                            cout << "=> Giỏ hàng hiện đang trống.\n";
                        } else if (confirm("Bạn có chắc muốn xóa TOÀN BỘ giỏ hàng?")) {
                            cart.clear();
                            cout << "=> Đã xóa toàn bộ giỏ hàng.\n";
                        } else {
                            cout << "=> Đã hủy thao tác xóa.\n";
                        }
                        break;
                    case 7:
                        cout << "\n--- TÌM SẢN PHẨM THEO MÃ ---\n";
                        searchProduct(cart);
                        break;
                }
            } catch (const overflow_error&) {
                cout << "=> Lỗi: số tiền vượt giới hạn lưu trữ.\n";
            }
        }
    } catch (const runtime_error& e) {
        cout << "\nChương trình kết thúc: " << e.what() << '\n';
    }

    return 0;
}
