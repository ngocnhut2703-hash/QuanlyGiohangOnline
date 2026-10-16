#ifndef ONLINE_SHOPPING_CART_CART_H
#define ONLINE_SHOPPING_CART_CART_H
#include "Product.h"
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

#endif
