#include <iostream>
#include <string>
#include <windows.h> // Thu vien tu dong chuyen bang ma UTF-8 tren Windows

#include "Cart.h"
#include "Order.h"

using namespace std;

void printMenu() {
    cout << "\n================ CỬA HÀNG ONLINE ================\n";
    cout << "1. Thêm sản phẩm vào giỏ hàng\n";
    cout << "2. Xem danh sách giỏ hàng\n";
    cout << "3. Cập nhật số lượng sản phẩm\n";
    cout << "4. Xóa sản phẩm khỏi giỏ hàng\n";
    cout << "5. Tạo đơn hàng (Thanh toán)\n";
    cout << "0. Thoát chương trình\n";
    cout << "=================================================\n";
    cout << "Lựa chọn của bạn: ";
}

int main() {
    // Thiet lap hien thi Tieng Viet UTF-8 tu dong cho Windows Console
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Cart myCart;
    int choice;

    do {
        printMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Lựa chọn không hợp lệ! Vui lòng nhập số.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                Product p;
                cout << "\n--- THÊM SẢN PHẨM ---\n";
                cout << "Nhập Mã SP (ID): ";
                cin >> p.id;
                cin.ignore();
                cout << "Nhập Tên SP: ";
                getline(cin, p.name);
                cout << "Nhập Đơn giá (VND): ";
                cin >> p.price;
                cout << "Nhập Số lượng: ";
                cin >> p.quantity;

                if (myCart.addItem(p)) {
                    cout << "=> Thêm vào giỏ hàng thành công!\n";
                } else {
                    cout << "=> Thêm thất bại! Dữ liệu không hợp lệ hoặc lỗi bộ nhớ.\n";
                }
                break;
            }
            case 2: {
                myCart.displayCart();
                break;
            }
            case 3: {
                string id;
                int newQty;
                cout << "\n--- CẬP NHẬT SỐ LƯỢNG ---\n";
                cout << "Nhập Mã SP cần sửa: ";
                cin >> id;
                cout << "Nhập Số lượng mới: ";
                cin >> newQty;

                if (myCart.updateQuantity(id, newQty)) {
                    cout << "=> Cập nhật số lượng thành công!\n";
                } else {
                    cout << "=> Không tìm thấy sản phẩm hoặc số lượng không hợp lệ!\n";
                }
                break;
            }
            case 4: {
                string id;
                cout << "\n--- XÓA SẢN PHẨM ---\n";
                cout << "Nhập Mã SP cần xóa: ";
                cin >> id;

                if (myCart.removeItem(id)) {
                    cout << "=> Đã xóa sản phẩm khỏi giỏ hàng!\n";
                } else {
                    cout << "=> Không tìm thấy sản phẩm có mã này!\n";
                }
                break;
            }
            case 5: {
                cout << "\n--- XÁC NHẬN TẠO ĐƠN HÀNG ---\n";
                if (createOrder(myCart)) {
                    cout << "=> Đơn hàng đã được tạo thành công!\n";
                }
                break;
            }
            case 0:
                cout << "\nCảm ơn bạn đã sử dụng chương trình!\n";
                break;
            default:
                cout << "Lựa chọn không có trong menu!\n";
        }
    } while (choice != 0);

    return 0;
}
