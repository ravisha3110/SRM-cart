/*
 * ============================================================
 *  FILE: main.cpp
 *  SRM CART — C++ OOP Demo Entry Point
 *
 *  This file demonstrates ALL four OOP concepts:
 *    1. ENCAPSULATION  — User, Product, Cart (private members)
 *    2. INHERITANCE    — Customer < User, Electronics/Clothing < Product
 *    3. ABSTRACTION    — Payment (pure virtual pay())
 *    4. POLYMORPHISM   — displayInfo(), pay(), login() called
 *                        through base-class pointers/references
 *
 *  Compile:  g++ -o srmcart main.cpp
 *  Run:      ./srmcart   (Linux/Mac)  |  srmcart.exe  (Windows)
 * ============================================================
 */

#include <iostream>
#include <vector>
#include "User.h"
#include "Customer.h"
#include "Product.h"
#include "Electronics.h"
#include "Clothing.h"
#include "Cart.h"
#include "Order.h"
#include "Payment.h"
#include "UPIPayment.h"
#include "CardPayment.h"

using namespace std;

// ---------------------------------------------------------------
// Customer method implementations (defined here to avoid
// circular dependency between Customer.h, Cart.h, Order.h)
// ---------------------------------------------------------------
void Customer::addToCart(Cart& cart, int productId) {
    cout << "[Customer] " << getName()
         << " is adding product ID " << productId << " to cart." << endl;
}

void Customer::placeOrder(Cart& cart) {
    cout << "[Customer] " << getName() << " is placing an order." << endl;
}

// ---------------------------------------------------------------
// Helper: separator line
// ---------------------------------------------------------------
void separator(const string& title) {
    cout << "\n===========================================" << endl;
    cout << "  " << title << endl;
    cout << "===========================================" << endl;
}

// ---------------------------------------------------------------
// MAIN — Demonstration of all OOP concepts
// ---------------------------------------------------------------
int main() {

    cout << "============================================" << endl;
    cout << "   Welcome to SRM Cart — OOP Demo (C++)    " << endl;
    cout << "============================================" << endl;

    // ===========================================================
    // 1. ENCAPSULATION + INHERITANCE — User & Customer
    // ===========================================================
    separator("1. ENCAPSULATION + INHERITANCE: User & Customer");

    // Base class pointer holding a Customer object (POLYMORPHISM)
    User* user1 = new Customer("Ravi Kumar", "ravi@srmist.edu.in");

    // Calling login() — Customer's version runs (POLYMORPHISM)
    user1->login();

    // Accessing private data via getters (ENCAPSULATION)
    cout << "Name  : " << user1->getName()  << endl;
    cout << "Email : " << user1->getEmail() << endl;

    // Also create a plain User object for comparison
    User user2("Professor Sharma", "sharma@srmist.edu.in");
    user2.login();   // Calls User::login() — different output

    // ===========================================================
    // 2. INHERITANCE + POLYMORPHISM — Product types
    // ===========================================================
    separator("2. INHERITANCE + POLYMORPHISM: Product Subclasses");

    // Create product objects (Electronics and Clothing inherit Product)
    Electronics* laptop  = new Electronics(101, "Dell Laptop",   55000.0, 24);
    Electronics* phone   = new Electronics(102, "Samsung Phone",  18000.0, 12);
    Clothing*    tshirt  = new Clothing   (201, "SRM T-Shirt",     499.0, "L");
    Clothing*    jeans   = new Clothing   (202, "Blue Jeans",     1299.0, "M");
    Electronics* webcam  = new Electronics(103, "HD Webcam",      2500.0,  6);

    // Store in a vector of BASE CLASS pointers
    vector<Product*> catalogue = { laptop, phone, tshirt, jeans, webcam };

    cout << "\n--- Product Catalogue (Polymorphic displayInfo()) ---" << endl;
    for (Product* p : catalogue) {
        p->displayInfo();   // POLYMORPHISM: correct version called at runtime
    }

    // ===========================================================
    // 3. ENCAPSULATION — Cart
    // ===========================================================
    separator("3. ENCAPSULATION: Cart Class");

    Cart cart;
    cart.addProduct(laptop);
    cart.addProduct(tshirt);
    cart.addProduct(phone);

    cart.displayCart();

    // Remove a product
    cart.removeProduct(102);   // Remove Samsung Phone
    cart.displayCart();

    // ===========================================================
    // 4. INHERITANCE — Customer using Cart
    // ===========================================================
    separator("4. INHERITANCE: Customer Methods");

    Customer* customer = dynamic_cast<Customer*>(user1);
    if (customer) {
        customer->addToCart(cart, 202);
        cart.addProduct(jeans);
        cart.displayCart();
        customer->placeOrder(cart);
    }

    // ===========================================================
    // 5. ENCAPSULATION — Order
    // ===========================================================
    separator("5. ENCAPSULATION: Order Class");

    Order order(1001, cart);
    order.placeOrder();
    order.displayOrder();

    // ===========================================================
    // 6. ABSTRACTION + POLYMORPHISM — Payment
    // ===========================================================
    separator("6. ABSTRACTION + POLYMORPHISM: Payment Classes");

    double total = order.getTotalAmount();

    // Payment pointer holds different concrete types (POLYMORPHISM)
    Payment* payment1 = new UPIPayment (total, "ravi@okhdfcbank");
    Payment* payment2 = new CardPayment(total, "7842", "Ravi Kumar");

    cout << "\n--- Paying via UPI ---" << endl;
    payment1->pay();   // Calls UPIPayment::pay()

    cout << "\n--- Paying via Card ---" << endl;
    payment2->pay();   // Calls CardPayment::pay()

    // ===========================================================
    // Summary
    // ===========================================================
    separator("OOP CONCEPTS DEMONSTRATED");
    cout << "  ENCAPSULATION  : User, Product, Cart, Order" << endl;
    cout << "  INHERITANCE    : Customer<-User, Electronics<-Product, Clothing<-Product" << endl;
    cout << "  ABSTRACTION    : Payment (pure virtual pay())" << endl;
    cout << "  POLYMORPHISM   : login(), displayInfo(), pay()" << endl;

    // Clean up dynamic memory
    delete user1;
    delete laptop;
    delete phone;
    delete tshirt;
    delete jeans;
    delete webcam;
    delete payment1;
    delete payment2;

    cout << "\n[SRM Cart] Demo complete. Thank you!\n" << endl;
    return 0;
}
