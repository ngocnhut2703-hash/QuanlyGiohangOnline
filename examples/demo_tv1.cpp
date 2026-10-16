#include "../Cart.h"
#include <iostream>
using namespace std;

int main() {
    Cart cart;
    if (!cart.isEmpty() || cart.getHead() != nullptr) {
        cerr << "LOI: Gio moi khoi tao phai rong.\n";
        return 1;
    }

    Product keyboard{"SP001", "Ban phim co", 650000, 3};
    Product mouse{"SP002", "Chuot", 150000, 1};

    // Hai node cuc bo chi de minh hoa prev/next, chua them vao Cart.
    // Khong dung delete cho hai node nay vi chung khong duoc tao bang new.
    Node first(keyboard);
    Node second(mouse);
    first.next = &second;
    second.prev = &first;

    cout << "1. Gio moi khoi tao: RONG\n";
    cout << "2. San pham mau: " << keyboard.id << " | "
              << keyboard.name << " | " << keyboard.price
              << " VND | So luong: " << keyboard.quantity << '\n';
    cout << "3. Di toi bang next: " << first.next->data.id << '\n';
    cout << "4. Di lui bang prev: " << second.prev->data.id << '\n';

    cart.clear();
    if (!cart.isEmpty() || cart.getHead() != nullptr) {
        cerr << "LOI: Gio phai rong sau clear().\n";
        return 1;
    }

    cout << "KET QUA: KHUNG TV1 CHAY DUOC.\n";
    return 0;
}
