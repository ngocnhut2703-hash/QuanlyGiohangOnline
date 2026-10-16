#ifndef ONLINE_SHOPPING_CART_PRODUCT_H
#define ONLINE_SHOPPING_CART_PRODUCT_H
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

#endif
