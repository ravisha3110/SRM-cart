/*
 * ============================================================
 *  FILE: User.h
 *  OOP CONCEPT: ENCAPSULATION
 *  - Private data members (name, email) hidden from outside
 *  - Public getter / setter methods control access
 *  - Virtual login() enables POLYMORPHISM in child classes
 * ============================================================
 */

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// BASE CLASS: User
// Demonstrates ENCAPSULATION (private attributes + public access)
// ---------------------------------------------------------------
class User {
private:
    // Private attributes — cannot be accessed directly from outside
    string name;
    string email;

public:
    // Constructor
    User(string name, string email) {
        this->name  = name;
        this->email = email;
    }

    // --- Getters (Encapsulation: controlled read access) ---
    string getName()  const { return name;  }
    string getEmail() const { return email; }

    // --- Setters (Encapsulation: controlled write access) ---
    void setName(string newName)   { name  = newName;  }
    void setEmail(string newEmail) { email = newEmail; }

    // Virtual login() — overridden in Customer (POLYMORPHISM)
    virtual void login() {
        cout << "[User] " << name << " logged in with email: " << email << endl;
    }

    // Virtual destructor (good practice with inheritance)
    virtual ~User() {}
};

#endif // USER_H
