#include "Order.h"
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