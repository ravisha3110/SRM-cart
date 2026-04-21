/*
 * ============================================================
 *         SRM CART — E-Commerce Application
 *         Single File C++ Version (All-in-One)
 *
 *  Run this file in any C++ compiler:
 *    - OnlineGDB  : https://www.onlinegdb.com
 *    - Replit     : https://replit.com
 *    - CodingGround: https://www.tutorialspoint.com/compile_cpp_online.php
 *
 *  Compile locally:
 *    g++ -o srmcart srmcart_all_in_one.cpp -std=c++17
 *
 * ============================================================
 *
 *  OOP CONCEPTS DEMONSTRATED:
 *
 *  1. ENCAPSULATION  — User, Product, Cart, Order
 *                      (private members + public getters/setters)
 *
 *  2. INHERITANCE    — Customer    inherits User
 *                      Electronics inherits Product
 *                      Clothing    inherits Product
 *                      UPIPayment  inherits Payment
 *                      CardPayment inherits Payment
 *
 *  3. ABSTRACTION    — Payment is an abstract class
 *                      pay() is a pure virtual method (= 0)
 *
 *  4. POLYMORPHISM   — login()       : User vs Customer
 *                      displayInfo() : Electronics vs Clothing
 *                      pay()         : UPIPayment vs CardPayment
 *
 * ============================================================
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ============================================================
//  CLASS 1: User  (Base Class)
//  OOP: ENCAPSULATION — private attributes, public getters
// ============================================================
class User {
private:
    string name;    // Private — cannot be accessed directly
    string email;   // Private — cannot be accessed directly

public:
    // Constructor
    User(string name, string email) {
        this->name  = name;
        this->email = email;
    }

    // Getters (Encapsulation — controlled access)
    string getName()  const { return name;  }
    string getEmail() const { return email; }

    // Setters (Encapsulation — controlled modification)
    void setName(string n)  { name  = n; }
    void setEmail(string e) { email = e; }

    // Virtual login() — overridden in Customer (Polymorphism)
    virtual void login() {
        cout << "[User] " << name
             << " logged in with email: " << email << endl;
    }

    virtual ~User() {}
};


// ============================================================
//  CLASS 2: Product  (Abstract Base Class)
//  OOP: ENCAPSULATION + ABSTRACTION
//  displayInfo() is pure virtual — must be implemented by subclasses
// ============================================================
class Product {
private:
    int    id;
    string name;
    double price;

public:
    Product(int id, string name, double price) {
        this->id    = id;
        this->name  = name;
        this->price = price;
    }

    // Getters
    int    getId()    const { return id;    }
    string getName()  const { return name;  }
    double getPrice() const { return price; }

    // ABSTRACTION — pure virtual method: subclasses MUST implement this
    virtual void displayInfo() const = 0;

    virtual ~Product() {}
};


// ============================================================
//  CLASS 3: Electronics  (Child of Product)
//  OOP: INHERITANCE + POLYMORPHISM
//  Extra attribute: warrantyMonths
// ============================================================
class Electronics : public Product {   // INHERITANCE
private:
    int warrantyMonths;

public:
    Electronics(int id, string name, double price, int warrantyMonths)
        : Product(id, name, price) {
        this->warrantyMonths = warrantyMonths;
    }

    int getWarranty() const { return warrantyMonths; }

    // POLYMORPHISM — overrides Product::displayInfo()
    void displayInfo() const override {
        cout << "[Electronics] ID: " << getId()
             << " | Name: "         << getName()
             << " | Price: Rs."     << getPrice()
             << " | Warranty: "     << warrantyMonths << " months" << endl;
    }
};


// ============================================================
//  CLASS 4: Clothing  (Child of Product)
//  OOP: INHERITANCE + POLYMORPHISM
//  Extra attribute: size
// ============================================================
class Clothing : public Product {   // INHERITANCE
private:
    string size;

public:
    Clothing(int id, string name, double price, string size)
        : Product(id, name, price) {
        this->size = size;
    }

    string getSize() const { return size; }

    // POLYMORPHISM — overrides Product::displayInfo()
    void displayInfo() const override {
        cout << "[Clothing]    ID: " << getId()
             << " | Name: "         << getName()
             << " | Price: Rs."     << getPrice()
             << " | Size: "         << size << endl;
    }
};


// ============================================================
//  CLASS 5: Cart
//  OOP: ENCAPSULATION
//  Private list of products, public methods to manage them
// ============================================================
class Cart {
private:
    vector<Product*> items;   // Private product list

public:
    // Add a product
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
        cout << "[Cart] Product ID " << productId << " not found." << endl;
    }

    // Calculate total price
    double calculateTotal() const {
        double total = 0.0;
        for (const auto& p : items) total += p->getPrice();
        return total;
    }

    // Display cart contents
    void displayCart() const {
        if (items.empty()) {
            cout << "[Cart] Cart is empty." << endl;
            return;
        }
        cout << "\n===== CART CONTENTS =====" << endl;
        for (const auto& p : items) {
            p->displayInfo();   // Polymorphic call
        }
        cout << "Total: Rs." << calculateTotal() << endl;
        cout << "=========================" << endl;
    }

    const vector<Product*>& getItems() const { return items; }
    void clear() { items.clear(); }
    int size() const { return items.size(); }
};


// ============================================================
//  CLASS 6: Order
//  OOP: ENCAPSULATION
//  Stores order details after cart is confirmed
// ============================================================
class Order {
private:
    int              orderId;
    vector<Product*> products;
    double           totalAmount;
    string           status;

public:
    Order(int orderId, const Cart& cart) {
        this->orderId     = orderId;
        this->products    = cart.getItems();
        this->totalAmount = cart.calculateTotal();
        this->status      = "Pending";
    }

    int    getOrderId()     const { return orderId;     }
    double getTotalAmount() const { return totalAmount; }
    string getStatus()      const { return status;      }

    void placeOrder() {
        if (products.empty()) {
            cout << "[Order] Cart is empty — cannot place order!" << endl;
            return;
        }
        status = "Confirmed";
        cout << "\n===== ORDER PLACED =====" << endl;
        cout << "Order ID : ORD-" << orderId << endl;
        cout << "Items    : " << products.size() << endl;
        cout << "Total    : Rs." << totalAmount << endl;
        cout << "Status   : " << status << endl;
        cout << "========================" << endl;
    }

    void displayOrder() const {
        cout << "\n----- Order Summary -----" << endl;
        cout << "Order ID : ORD-" << orderId << endl;
        for (const auto& p : products) p->displayInfo();
        cout << "Total    : Rs." << totalAmount << endl;
        cout << "Status   : " << status << endl;
        cout << "-------------------------" << endl;
    }
};


// ============================================================
//  CLASS 7: Payment  (Abstract Class)
//  OOP: ABSTRACTION
//  pay() is pure virtual — cannot instantiate Payment directly
// ============================================================
class Payment {
protected:
    double amount;

public:
    Payment(double amount) {
        this->amount = amount;
    }

    // ABSTRACTION — pure virtual: forces subclasses to implement pay()
    virtual void pay() = 0;

    void printReceipt() {
        cout << "[Payment] Receipt: Rs." << amount
             << " charged successfully." << endl;
    }

    virtual ~Payment() {}
};


// ============================================================
//  CLASS 8: UPIPayment  (Child of Payment)
//  OOP: INHERITANCE + POLYMORPHISM
// ============================================================
class UPIPayment : public Payment {   // INHERITANCE
private:
    string upiId;

public:
    UPIPayment(double amount, string upiId) : Payment(amount) {
        this->upiId = upiId;
    }

    // POLYMORPHISM — implements abstract pay() with UPI logic
    void pay() override {
        cout << "\n[UPIPayment] Processing UPI Payment..." << endl;
        cout << "  UPI ID : " << upiId << endl;
        cout << "  Amount : Rs." << amount << endl;
        cout << "  Status : SUCCESS — Payment via UPI complete!" << endl;
        printReceipt();
    }
};


// ============================================================
//  CLASS 9: CardPayment  (Child of Payment)
//  OOP: INHERITANCE + POLYMORPHISM
// ============================================================
class CardPayment : public Payment {   // INHERITANCE
private:
    string cardNumber;
    string cardHolder;

public:
    CardPayment(double amount, string cardNumber, string cardHolder)
        : Payment(amount) {
        this->cardNumber = cardNumber;
        this->cardHolder = cardHolder;
    }

    // POLYMORPHISM — implements abstract pay() with Card logic
    void pay() override {
        cout << "\n[CardPayment] Processing Card Payment..." << endl;
        cout << "  Card Holder : " << cardHolder << endl;
        cout << "  Card No.    : **** **** **** " << cardNumber << endl;
        cout << "  Amount      : Rs." << amount << endl;
        cout << "  Status      : SUCCESS — Payment via Card complete!" << endl;
        printReceipt();
    }
};


// ============================================================
//  CLASS 10: Customer  (Child of User)
//  OOP: INHERITANCE + POLYMORPHISM
// ============================================================
class Customer : public User {   // INHERITANCE
public:
    Customer(string name, string email) : User(name, email) {}

    // POLYMORPHISM — overrides User::login()
    void login() override {
        cout << "[Customer] Welcome, " << getName()
             << "! Logged in as Customer." << endl;
    }

    void addToCart(Cart& cart, Product* product) {
        cout << "[Customer] " << getName()
             << " adding '" << product->getName() << "' to cart." << endl;
        cart.addProduct(product);
    }

    void placeOrder(Cart& cart) {
        cout << "[Customer] " << getName()
             << " is placing an order." << endl;
    }
};


// ============================================================
//  HELPER: Separator line for readability
// ============================================================
void separator(const string& title) {
    cout << "\n===========================================" << endl;
    cout << "  " << title << endl;
    cout << "===========================================" << endl;
}


// ============================================================
//  MAIN — Demonstrates all OOP concepts step by step
// ============================================================
int main() {

    cout << "============================================" << endl;
    cout << "    SRM CART — C++ OOP Demo (All-in-One)   " << endl;
    cout << "    SRM Institute of Science & Technology  " << endl;
    cout << "============================================" << endl;

    // ----------------------------------------------------------
    // STEP 1: ENCAPSULATION + INHERITANCE
    //         User and Customer
    // ----------------------------------------------------------
    separator("STEP 1: ENCAPSULATION + INHERITANCE");

    // Base class object — plain User
    User user2("Prof. Sharma", "sharma@srmist.edu.in");
    user2.login();     // Calls User::login()

    // Child class object — Customer inherits User
    Customer customer("Ravi Kumar", "ravi@srmist.edu.in");
    customer.login();  // Calls Customer::login() — POLYMORPHISM

    // Encapsulation: access private data via getters only
    cout << "Name  : " << customer.getName()  << endl;
    cout << "Email : " << customer.getEmail() << endl;


    // ----------------------------------------------------------
    // STEP 2: INHERITANCE + POLYMORPHISM
    //         Electronics and Clothing both inherit Product
    // ----------------------------------------------------------
    separator("STEP 2: INHERITANCE + POLYMORPHISM (Products)");

    Electronics laptop (101, "Dell Laptop",      55000.0, 24);
    Electronics phone  (102, "Samsung Phone",    18000.0, 12);
    Electronics webcam (103, "HD Webcam",         2500.0,  6);
    Clothing    tshirt (201, "SRM T-Shirt",        499.0, "L");
    Clothing    jeans  (202, "Blue Jeans",        1299.0, "M");
    Clothing    hoodie (203, "Cotton Hoodie",     1799.0, "XL");

    // Store in base-class pointer vector — Polymorphism in action
    vector<Product*> catalogue = {
        &laptop, &phone, &webcam, &tshirt, &jeans, &hoodie
    };

    cout << "\n--- Product Catalogue ---" << endl;
    for (Product* p : catalogue) {
        p->displayInfo();   // POLYMORPHISM: correct version called at runtime
    }


    // ----------------------------------------------------------
    // STEP 3: ENCAPSULATION — Cart Class
    // ----------------------------------------------------------
    separator("STEP 3: ENCAPSULATION (Cart)");

    Cart cart;
    customer.addToCart(cart, &laptop);
    customer.addToCart(cart, &tshirt);
    customer.addToCart(cart, &phone);

    cart.displayCart();

    cout << "\n[Removing Samsung Phone from cart...]" << endl;
    cart.removeProduct(102);
    cart.displayCart();


    // ----------------------------------------------------------
    // STEP 4: ORDER — Encapsulation
    // ----------------------------------------------------------
    separator("STEP 4: ENCAPSULATION (Order)");

    customer.placeOrder(cart);
    Order order(1001, cart);
    order.placeOrder();
    order.displayOrder();


    // ----------------------------------------------------------
    // STEP 5: ABSTRACTION + POLYMORPHISM — Payment
    // ----------------------------------------------------------
    separator("STEP 5: ABSTRACTION + POLYMORPHISM (Payment)");

    double total = order.getTotalAmount();

    // Payment* can hold any subclass object — POLYMORPHISM
    Payment* upiPay  = new UPIPayment (total, "ravi@okhdfcbank");
    Payment* cardPay = new CardPayment(total, "7842", "Ravi Kumar");

    cout << "\n--- Option 1: Pay via UPI ---" << endl;
    upiPay->pay();    // Calls UPIPayment::pay()

    cout << "\n--- Option 2: Pay via Card ---" << endl;
    cardPay->pay();   // Calls CardPayment::pay()

    // Cleanup
    delete upiPay;
    delete cardPay;


    // ----------------------------------------------------------
    // SUMMARY
    // ----------------------------------------------------------
    separator("OOP CONCEPTS SUMMARY");
    cout << "  ENCAPSULATION : User, Product, Cart, Order" << endl;
    cout << "  INHERITANCE   : Customer<-User" << endl;
    cout << "                  Electronics<-Product, Clothing<-Product" << endl;
    cout << "                  UPIPayment<-Payment, CardPayment<-Payment" << endl;
    cout << "  ABSTRACTION   : Payment class (pure virtual pay())" << endl;
    cout << "  POLYMORPHISM  : login(), displayInfo(), pay()" << endl;

    cout << "\n[SRM Cart] Thank you! Demo complete.\n" << endl;
    return 0;
}
