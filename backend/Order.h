/*
 * ============================================================
 *  FILE: Order.h
 *  OOP CONCEPT: ENCAPSULATION
 *  - Represents a confirmed order with an ID, items, total
 *  - placeOrder() method processes the cart into an order
 * ============================================================
 */

#ifndef ORDER_H
#define ORDER_H

#include "Cart.h"
#include <ctime>

// ---------------------------------------------------------------
// CLASS: Order
// Stores order details after the customer confirms purchase
// Demonstrates ENCAPSULATION
// ---------------------------------------------------------------
class Order {
private:
    int              orderId;
    vector<Product*> products;   // Snapshot of cart items
    double           totalAmount;
    string           status;

public:
    // Constructor — copies cart items and computes total
    Order(int orderId, const Cart& cart) {
        this->orderId     = orderId;
        this->products    = cart.getItems();   // Copy cart snapshot
        this->totalAmount = cart.calculateTotal();
        this->status      = "Pending";
    }

    // --- Getters ---
    int    getOrderId()     const { return orderId;     }
    double getTotalAmount() const { return totalAmount; }
    string getStatus()      const { return status;      }

    // Place / confirm the order
    void placeOrder() {
        if (products.empty()) {
            cout << "[Order] Cannot place order — cart is empty!" << endl;
            return;
        }
        status = "Confirmed";
        cout << "\n===== ORDER PLACED =====" << endl;
        cout << "Order ID   : ORD-" << orderId << endl;
        cout << "Items      : " << products.size() << endl;
        cout << "Total      : Rs." << totalAmount << endl;
        cout << "Status     : " << status << endl;
        cout << "========================" << endl;
    }

    // Display order summary
    void displayOrder() const {
        cout << "\n----- Order Summary -----" << endl;
        cout << "Order ID : ORD-" << orderId << endl;
        for (const auto& p : products) {
            p->displayInfo();
        }
        cout << "Total    : Rs." << totalAmount << endl;
        cout << "Status   : " << status << endl;
        cout << "-------------------------" << endl;
    }
};

#endif // ORDER_H
