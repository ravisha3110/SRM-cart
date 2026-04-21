/*
 * ============================================================
 *  FILE: Payment.h
 *  OOP CONCEPTS: ABSTRACTION
 *  - Payment is an ABSTRACT BASE CLASS
 *  - pay() is a PURE VIRTUAL METHOD (= 0)
 *  - Cannot instantiate Payment directly
 *  - Forces child classes (UPI, Card) to implement pay()
 * ============================================================
 */

#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// ABSTRACT CLASS: Payment
// ABSTRACTION — defines WHAT to do (pay), not HOW to do it
// ---------------------------------------------------------------
class Payment {
protected:
    double amount;   // Protected: accessible by child classes

public:
    Payment(double amount) {
        this->amount = amount;
    }

    // PURE VIRTUAL METHOD — makes Payment an abstract class
    // Every concrete payment type MUST implement this method
    virtual void pay() = 0;

    // Virtual method with default behaviour
    virtual void printReceipt() {
        cout << "[Payment] Amount: Rs." << amount << " — Receipt generated." << endl;
    }

    // Virtual destructor
    virtual ~Payment() {}
};

#endif // PAYMENT_H
