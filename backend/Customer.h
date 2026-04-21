/*
 * ============================================================
 *  FILE: Customer.h
 *  OOP CONCEPTS: INHERITANCE + POLYMORPHISM
 *  - Customer INHERITS from User (gets name, email, login)
 *  - Overrides login() to show polymorphic behaviour
 *  - Adds customer-specific methods: addToCart(), placeOrder()
 * ============================================================
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <vector>

// Forward declare Cart and Order so we don't need full includes here
class Cart;
class Order;

// ---------------------------------------------------------------
// CHILD CLASS: Customer  (INHERITS from User)
// ---------------------------------------------------------------
class Customer : public User {   // <-- INHERITANCE

public:
    // Constructor passes base-class data to User
    Customer(string name, string email) : User(name, email) {}

    // POLYMORPHISM — overrides User::login() with different behaviour
    void login() override {
        cout << "[Customer] Welcome back, " << getName()
             << "! You are logged in as a Customer." << endl;
    }

    // Add a product to the customer's cart
    void addToCart(Cart& cart, int productId);

    // Place an order from the cart
    void placeOrder(Cart& cart);
};

// ---------------------------------------------------------------
// Method implementations are in main.cpp to avoid circular deps
// ---------------------------------------------------------------

#endif // CUSTOMER_H
