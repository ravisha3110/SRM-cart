/*
 * ============================================================
 *  FILE: UPIPayment.h
 *  OOP CONCEPTS: INHERITANCE + POLYMORPHISM
 *  - Inherits from abstract Payment class
 *  - Implements pay() using UPI-specific logic
 * ============================================================
 */

#ifndef UPIPAYMENT_H
#define UPIPAYMENT_H

#include "Payment.h"

// ---------------------------------------------------------------
// CHILD CLASS: UPIPayment  (INHERITS from Payment)
// POLYMORPHISM — implements pay() differently from CardPayment
// ---------------------------------------------------------------
class UPIPayment : public Payment {   // <-- INHERITANCE
private:
    string upiId;   // Extra attribute: UPI ID (e.g., user@upi)

public:
    UPIPayment(double amount, string upiId) : Payment(amount) {
        this->upiId = upiId;
    }

    // POLYMORPHISM — concrete implementation of abstract pay()
    void pay() override {
        cout << "\n[UPIPayment] Processing UPI payment..." << endl;
        cout << "  UPI ID  : " << upiId << endl;
        cout << "  Amount  : Rs." << amount << endl;
        cout << "  Status  : SUCCESS — Payment completed via UPI!" << endl;
        printReceipt();
    }
};

#endif // UPIPAYMENT_H
