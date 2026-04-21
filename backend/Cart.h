/*
 * ============================================================
 *  FILE: Cart.h
 *  OOP CONCEPT: ENCAPSULATION
 *  - Stores a private list of Product pointers
 *  - Exposes controlled methods: addProduct(), removeProduct(),
 *    calculateTotal(), displayCart()
 * ============================================================
 */

#ifndef CART_H
#define CART_H

#include "Product.h"
#include <vector>
#include <algorithm>

// ---------------------------------------------------------------
// CLASS: Cart
// Manages a collection of products for a customer
// Demonstrates ENCAPSULATION (private data, public interface)
// ---------------------------------------------------------------
class Cart {
private:
    vector<Product*> items;   // Private list of products

public:
    // Add a product to the cart
    void addProduct(Product* p) {
        items.push_back(p);
        cout << "[Cart] Added: " << p->getName()
             << " (Rs." << p->getPrice() << ")" << endl;
    }

    // Remove a product by ID
    void removeProduct(int productId) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getId() == productId) {
                cout << "[Cart] Removed: " << (*it)->getName() << endl;
                items.erase(it);
                return;
            }
        }
        cout << "[Cart] Product ID " << productId << " not found in cart." << endl;
    }

    // Calculate and return total price
    double calculateTotal() const {
        double total = 0.0;
        for (const auto& p : items) {
            total += p->getPrice();
        }
        return total;
    }

    // Display all products in the cart
    void displayCart() const {
        if (items.empty()) {
            cout << "[Cart] Your cart is empty." << endl;
            return;
        }
        cout << "\n===== CART CONTENTS =====" << endl;
        for (const auto& p : items) {
            p->displayInfo();   // Polymorphic call
        }
        cout << "Total: Rs." << calculateTotal() << endl;
        cout << "=========================" << endl;
    }

    // Getter for items (used by Order)
    const vector<Product*>& getItems() const { return items; }

    // Clear the cart after order placement
    void clear() { items.clear(); }

    int size() const { return items.size(); }
};

#endif // CART_H
