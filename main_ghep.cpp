// QUAN LY GIO HANG ONLINE - BAN GHEP DOC LAP
// Gop Product.h, Cart.h, Cart.cpp, CartTV4.cpp, Order.cpp va main.cpp
// Bien dich: g++ -std=c++17 -Wall -Wextra -pedantic main_ghep.cpp -o giohang
#include <iostream>
#include <iomanip>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>
using namespace std;

// ===== 1. PRODUCT + NODE =====
#include <string>
using namespace std;
// Thong tin cua mot mat hang trong gio.
struct Product {
    string id;       // Vi du: "SP001".
    string name;     // Ten san pham.
    long long price = 0;  // Don gia nguyen, don vi VND.
    int quantity = 0;     // So luong; du lieu hop le phai > 0.
};

// Mot node cua danh sach lien ket doi.
struct Node {
    Product data;
    Node* prev;
    Node* next;

    explicit Node(const Product& product)
        : data(product), prev(nullptr), next(nullptr) {
    }
};


// ===== 2. KHAI BAO CART =====
using namespace std;
class Cart {
private:
    Node* head;  // Node dau tien; nullptr neu gio rong.
    Node* tail;  // Node cuoi cung; nullptr neu gio rong.

    // Ham ho tro: tim theo ID; tra nullptr neu khong tim thay.
    Node* findItem(const string& id);
    const Node* findItem(const string& id) const;

public:
    // TV1: khoi tao, giai phong bo nho va cac ham ho tro.
    Cart();
    ~Cart();

    // Cart so huu cac node: chan copy de tranh giai phong trung bo nho.
    Cart(const Cart&) = delete;
    Cart& operator=(const Cart&) = delete;

    bool isEmpty() const;
    void clear();

    // Ho tro TV5 doc cac mat hang khi in hoa don.
    // Nguoi goi chi doc; khong sua, delete hoac luu node sau khi gio doi.
    const Node* getHead() const;

    // TV2: them moi; ID trung thi tang so luong theo quy uoc README.
    // Moi khai bao: TV2 se viet phan dinh nghia.
    bool addItem(const Product& product);

    // TV3: hien thi gio va tinh tong tien VND.
    // Moi khai bao: TV3 se viet phan dinh nghia.
    void displayCart() const;
    long long calculateTotal() const;

    // TV4: cap nhat so luong va xoa mat hang theo ID.
    // Moi khai bao: TV4 se viet phan dinh nghia.
    bool updateQuantity(const string& id, int newQuantity);
    bool removeItem(const string& id);
};


// ===== 3. CAI DAT CART (TV1, TV2, TV3) =====
#include <iostream>
#include <iomanip>
#include <limits>
#include <new>

using namespace std;

static long long checkedMultiply(long long price, int quantity) {
    if (price < 0 || quantity < 0 ||
        (price > 0 && quantity > numeric_limits<long long>::max() / price))
        throw overflow_error("Thanh tien vuot gioi han long long");
    return price * quantity;
}
Cart::Cart() : head(nullptr), tail(nullptr) {
}

Cart::~Cart() {
    clear();
}

bool Cart::isEmpty() const {
    return head == nullptr;
}

const Node* Cart::getHead() const {
    return head;
}

Node* Cart::findItem(const std::string& id) {
    Node* current = head;

    while (current != nullptr) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

const Node* Cart::findItem(const std::string& id) const {
    const Node* current = head;

    while (current != nullptr) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

void Cart::clear() {
    Node* current = head;

    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
    tail = nullptr;
}

// CAC PHAN CAC THANH VIEN SE BO SUNG SAU KHI CHOT GIAO DIEN:
// TV2: bool Cart::addItem(const Product& product)

bool Cart::addItem(const Product& product) {
    // Kiem tra du lieu
    if (product.id.empty() ||
        product.name.empty() ||
        product.price <= 0 ||
        product.quantity <= 0) {
        return false;
    }

    // Tim san pham theo id
    Node* current = findItem(product.id);

    // Neu ID da ton tai, tang so luong
    if (current != nullptr) {
        if (current->data.quantity <= 0 ||
            product.quantity >
                std::numeric_limits<int>::max()- current->data.quantity) {
            return false;
        }

        try {
            long long before = calculateTotal();
            long long oldAmount = checkedMultiply(current->data.price, current->data.quantity);
            long long newAmount = checkedMultiply(current->data.price, current->data.quantity + product.quantity);
            if (newAmount > numeric_limits<long long>::max() - (before - oldAmount)) return false;
        } catch (const overflow_error&) { return false; }
        current->data.quantity += product.quantity;
        return true;
    }

    try {
        long long before = calculateTotal();
        long long amount = checkedMultiply(product.price, product.quantity);
        if (amount > numeric_limits<long long>::max() - before) return false;
    } catch (const overflow_error&) { return false; }

    // Tao node moi
    Node* newNode = new (std::nothrow) Node(product);

    if (newNode == nullptr) {
        return false;
    }

    // Them vao cuoi danh sach
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    return true;
}

// TV3: void Cart::displayCart() const
// TV3: long long Cart::calculateTotal() const
// 1. Hàm xem giỏ hàng
void Cart::displayCart() const {
    if (head == nullptr) {
        cout << "\n----------------------------------------\n";
        cout << "Gio hang hien tai dang trong!\n";
        cout << "----------------------------------------\n";
        return;
    }

    cout << "\n================ DS GIO HANG ================\n";
    cout << left << setw(10) << "ID" 
         << setw(20) << "Ten SP" 
         << setw(12) << "Don gia" 
         << setw(10) << "So luong" 
         << setw(15) << "Thanh tien" << endl;
    cout << "------------------------------------------------------------\n";

    const Node* current = head;
    while (current != nullptr) {
        long long itemTotal = checkedMultiply(current->data.price, current->data.quantity);
        cout << left << setw(10) << current->data.id
             << setw(20) << current->data.name
             << setw(12) << current->data.price
             << setw(10) << current->data.quantity
             << setw(15) << itemTotal << endl;
        current = current->next;
    }
    cout << "------------------------------------------------------------\n";
    cout << "TONG CONG: " << calculateTotal() << " VND\n";
    cout << "============================================================\n\n";
}

// 2. Hàm tính tổng tiền
long long Cart::calculateTotal() const {
    long long total = 0;
    for (const Node* current = head; current != nullptr; current = current->next) {
        long long amount = checkedMultiply(current->data.price, current->data.quantity);
        if (amount > numeric_limits<long long>::max() - total)
            throw overflow_error("Tong tien vuot gioi han long long");
        total += amount;
    }
    return total;
}
// TV4: bool Cart::updateQuantity(const std::string& id, int newQuantity)
// TV4: bool Cart::removeItem(const std::string& id)
//
// Co the dinh nghia cac ham nay trong cac file .cpp rieng, moi file
// #include "Cart.h". Chi dinh nghia moi ham o mot noi.

// ===== 4. CAP NHAT / XOA (TV4) =====
#include <limits>
#include <stdexcept>

bool Cart::updateQuantity(const std::string& id, int newQuantity) {
    if (newQuantity <= 0) {
        return false;
    }

    Node* target = findItem(id);
    if (target == nullptr) {
        return false;
    }

    if (target->data.price > 0) {
        long long maxVal = std::numeric_limits<long long>::max();
        if (maxVal / target->data.price < newQuantity) {
            return false;
        }
    }

    try {
        long long total = calculateTotal();
        long long oldAmount = target->data.price * target->data.quantity;
        long long newAmount = target->data.price * newQuantity;
        if (newAmount > std::numeric_limits<long long>::max() - (total - oldAmount)) return false;
    } catch (const std::overflow_error&) { return false; }
    target->data.quantity = newQuantity;
    return true;
}

bool Cart::removeItem(const std::string& id) {
    Node* target = findItem(id);
    if (target == nullptr) {
        return false;
    }

    if (target == head) {
        head = target->next;
    } else {
        target->prev->next = target->next;
    }

    if (target == tail) {
        tail = target->prev;
    } else {
        target->next->prev = target->prev;
    }

    delete target;
    return true;
}

// ===== 5. TAO HOA DON (TV5) =====
#include <iostream>
#include <iomanip>
#include <stdexcept>

bool createOrder(const Cart& cart) {
    if (cart.isEmpty()) {
        cout << "Gio hang trong, khong the tao don hang!\n";
        return false;
    }

    long long total = 0;
    try {
		total = cart.calculateTotal();   // Ngan overflow_error neu tong tien qua lon
    }
    catch (const overflow_error&) {
        cout << "Tong tien qua lon, khong the tao don hang!\n";
        return false;
    }

    cout << "=================== HOA DON ===================\n";
    cout << left
        << setw(10) << "ID"
        << setw(20) << "Ten hang"
        << setw(6) << "SL"
        << setw(14) << "Don gia"
        << setw(14) << "Thanh tien" << "\n";
    cout << "-----------------------------------------------\n";

    const Node* current = cart.getHead();
    while (current != nullptr) {
        long long subtotal = current->data.price * current->data.quantity;

        cout << left
            << setw(10) << current->data.id
            << setw(20) << current->data.name
            << setw(6) << current->data.quantity
            << setw(14) << current->data.price
            << setw(14) << subtotal << "\n";

        current = current->next;
    }

    cout << "-----------------------------------------------\n";
    cout << "TONG CONG: " << total << " VND\n";
    return true;
}

// ===== 6. MENU MAIN (TV6) =====
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
using namespace std;

// Doc so nguyen trong khoang, khong de du lieu nhap sai lam hong menu.
long long readNumber(const string& prompt, long long minimum, long long maximum) {
    while (true) {
        cout << prompt;
        long long value;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= minimum && value <= maximum) return value;
            cout << "Gia tri phai nam trong [" << minimum << ", " << maximum << "].\n";
        } else {
            if (cin.eof()) throw runtime_error("Da dong luong nhap.");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap so nguyen hop le!\n";
        }
    }
}

string readText(const string& prompt) {
    while (true) {
        cout << prompt;
        string value;
        if (!getline(cin, value)) throw runtime_error("Da dong luong nhap.");
        if (value.find_first_not_of(" \t\r\n") != string::npos) return value;
        cout << "Khong duoc de trong.\n";
    }
}

int main() {
    Cart cart;
    cout << "===== CHUONG TRINH QUAN LY GIO HANG ONLINE =====\n";
    try {
        while (true) {
            cout << "\n1. Them san pham vao gio\n"
                 << "2. Xem gio hang\n"
                 << "3. Cap nhat so luong san pham\n"
                 << "4. Xoa san pham khoi gio\n"
                 << "5. Tao / in hoa don\n"
                 << "6. Xoa toan bo gio hang\n"
                 << "0. Thoat\n";
            int choice = static_cast<int>(readNumber("Chon chuc nang: ", 0, 6));
            if (choice == 0) {
                cout << "Da thoat chuong trinh.\n";
                break;
            }
            try {
                switch (choice) {
                    case 1: {
                        Product product;
                        product.id = readText("Ma san pham: ");
                        product.name = readText("Ten san pham: ");
                        product.price = readNumber("Don gia (VND): ", 1, numeric_limits<long long>::max());
                        product.quantity = static_cast<int>(readNumber("So luong: ", 1, numeric_limits<int>::max()));
                        cout << (cart.addItem(product) ? "Them san pham thanh cong!\n" : "Them that bai (du lieu sai hoac tran so).\n");
                        break;
                    }
                    case 2:
                        cart.displayCart();
                        break;
                    case 3: {
                        string id = readText("Ma san pham can sua: ");
                        int qty = static_cast<int>(readNumber("So luong moi: ", 1, numeric_limits<int>::max()));
                        cout << (cart.updateQuantity(id, qty) ? "Cap nhat thanh cong!\n" : "Khong tim thay ma hoac gia tri khong hop le.\n");
                        break;
                    }
                    case 4: {
                        string id = readText("Ma san pham can xoa: ");
                        cout << (cart.removeItem(id) ? "Xoa thanh cong!\n" : "Khong tim thay ma san pham.\n");
                        break;
                    }
                    case 5:
                        createOrder(cart);
                        break;
                    case 6:
                        cart.clear();
                        cout << "Da xoa toan bo gio hang.\n";
                        break;
                }
            } catch (const overflow_error& e) {
                cout << "Loi: Tong tien qua lon, khong the bieu dien.\n";
            }
        }
    } catch (const runtime_error&) {
        cout << "\nKet thuc do luong nhap da dong.\n";
    }
    return 0;
}
