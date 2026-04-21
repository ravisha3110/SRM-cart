/*
 * ============================================================
 *  FILE: Clothing.h
 *  OOP CONCEPTS: INHERITANCE + POLYMORPHISM
 *  - Inherits from Product
 *  - Adds extra attribute: size (S / M / L / XL)
 *  - Provides concrete implementation of displayInfo()
 * ============================================================
 */

#ifndef CLOTHING_H
#define CLOTHING_H

#include "Product.h"

// ---------------------------------------------------------------
// CHILD CLASS: Clothing  (INHERITS from Product)
// ---------------------------------------------------------------
class Clothing : public Product {   // <-- INHERITANCE
private:
    string size;   // Extra attribute specific to clothing

public:
    // Constructor passes Product fields to base class
    Clothing(int id, string name, double price, string size)
        : Product(id, name, price) {
        this->size = size;
    }

    string getSize() const { return size; }

    // POLYMORPHISM — concrete implementation of abstract displayInfo()
    void displayInfo() const override {
        cout << "[Clothing]    ID: " << getId()
             << " | Name: "    << getName()
             << " | Price: Rs." << getPrice()
             << " | Size: "    << size << endl;
    }
};

#endif // CLOTHING_H
