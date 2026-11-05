#include "Cart.h"
#include <limits>

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