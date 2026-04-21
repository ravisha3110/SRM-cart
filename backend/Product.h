/*
 * ============================================================
 *  FILE: Product.h
 *  OOP CONCEPTS: ENCAPSULATION + ABSTRACTION
 *  - Private attributes (id, name, price) with getters
 *  - Pure virtual displayInfo() forces child classes to implement
 *    their own version — this is ABSTRACTION
 * ============================================================
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// BASE CLASS: Product
// Encapsulation: private fields, public getters
// Abstraction:  displayInfo() is pure virtual (= 0)
// ---------------------------------------------------------------
class Product {
private:
    int    id;
    string name;
    double price;

public:
    // Constructor
    Product(int id, string name, double price) {
        this->id    = id;
        this->name  = name;
        this->price = price;
    }

    // --- Getters ---
    int    getId()    const { return id;    }
    string getName()  const { return name;  }
    double getPrice() const { return price; }

    // ABSTRACTION — pure virtual method: must be implemented by subclasses
    // This makes Product an ABSTRACT CLASS (cannot be instantiated directly)
    virtual void displayInfo() const = 0;

    // Virtual destructor
    virtual ~Product() {}
};

#endif // PRODUCT_H
