/*
 * ============================================================
 *  FILE: Electronics.h
 *  OOP CONCEPTS: INHERITANCE + POLYMORPHISM
 *  - Inherits from Product
 *  - Adds extra attribute: warranty (in months)
 *  - Provides concrete implementation of displayInfo()
 * ============================================================
 */

#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Product.h"

// ---------------------------------------------------------------
// CHILD CLASS: Electronics  (INHERITS from Product)
// ---------------------------------------------------------------
class Electronics : public Product {   // <-- INHERITANCE
private:
    int warrantyMonths;   // Extra attribute specific to electronics

public:
    // Constructor passes Product fields to base class
    Electronics(int id, string name, double price, int warrantyMonths)
        : Product(id, name, price) {
        this->warrantyMonths = warrantyMonths;
    }

    int getWarranty() const { return warrantyMonths; }

    // POLYMORPHISM — concrete implementation of abstract displayInfo()
    void displayInfo() const override {
        cout << "[Electronics] ID: " << getId()
             << " | Name: "    << getName()
             << " | Price: Rs." << getPrice()
             << " | Warranty: " << warrantyMonths << " months" << endl;
    }
};

#endif // ELECTRONICS_H
