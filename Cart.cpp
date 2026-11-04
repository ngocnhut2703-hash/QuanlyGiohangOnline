#include "Cart.h"
#include <limits>
#include <new>

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
// TV4: bool Cart::updateQuantity(const std::string& id, int newQuantity)
// TV4: bool Cart::removeItem(const std::string& id)
//
// Co the dinh nghia cac ham nay trong cac file .cpp rieng, moi file
// #include "Cart.h". Chi dinh nghia moi ham o mot noi.
