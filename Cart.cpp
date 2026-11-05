#include "Cart.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <new>

using namespace std;
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

        current->data.quantity += product.quantity;
        return true;
    }

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

    Node* current = head;
    double total = 0;

    while (current != nullptr) {
        double itemTotal = current->data.price * current->data.quantity;
        total += itemTotal;

        cout << left << setw(10) << current->data.id
             << setw(20) << current->data.name
             << setw(12) << current->data.price
             << setw(10) << current->data.quantity
             << setw(15) << itemTotal << endl;

        current = current->next;
    }

    cout << "------------------------------------------------------------\n";
    cout << "TONG CONG: " << total << " VND\n";
    cout << "============================================================\n\n";
}

// 2. Hàm tính tổng tiền
long long Cart::calculateTotal() const {
    long long total = 0;
    Node* current = head;

    while (current != nullptr) {
        total += (current->data.price * current->data.quantity);
        current = current->next;
    }

    return total;
}
// TV4: bool Cart::updateQuantity(const std::string& id, int newQuantity)
// TV4: bool Cart::removeItem(const std::string& id)
//
// Co the dinh nghia cac ham nay trong cac file .cpp rieng, moi file
// #include "Cart.h". Chi dinh nghia moi ham o mot noi.
