/*
 * ============================================================
 *  FILE: CardPayment.h
 *  OOP CONCEPTS: INHERITANCE + POLYMORPHISM
 *  - Inherits from abstract Payment class
 *  - Implements pay() using Card-specific logic (different from UPI)
 * ============================================================
 */

#ifndef CARDPAYMENT_H
#define CARDPAYMENT_H

#include "Payment.h"

// ---------------------------------------------------------------
// CHILD CLASS: CardPayment  (INHERITS from Payment)
// POLYMORPHISM — implements pay() differently from UPIPayment
// ---------------------------------------------------------------
class CardPayment : public Payment {   // <-- INHERITANCE
private:
    string cardNumber;   // Last 4 digits for display
    string cardHolder;

public:
    CardPayment(double amount, string cardNumber, string cardHolder)
        : Payment(amount) {
        this->cardNumber = cardNumber;
        this->cardHolder = cardHolder;
    }

    // POLYMORPHISM — concrete implementation of abstract pay()
    void pay() override {
        cout << "\n[CardPayment] Processing Card payment..." << endl;
        cout << "  Card Holder : " << cardHolder << endl;
        cout << "  Card No.    : **** **** **** " << cardNumber << endl;
        cout << "  Amount      : Rs." << amount << endl;
        cout << "  Status      : SUCCESS — Payment completed via Card!" << endl;
        printReceipt();
    }
};

#endif // CARDPAYMENT_H
