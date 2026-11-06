#ifndef ONLINE_SHOPPING_CART_ORDER_H
#define ONLINE_SHOPPING_CART_ORDER_H
#include "Cart.h"
using namespace std;
// Chi doc gio hang, khong xoa gio.
// Tra ve false neu gio trong (hoac khong tinh duoc tong tien); true neu in don thanh cong.
bool createOrder(const Cart& cart);

#endif
