/*
 * ============================================================
 *  FILE: app.js
 *  SRM Cart — Frontend JavaScript
 *
 *  This file mirrors the C++ OOP class structure exactly.
 *  JavaScript classes are used to simulate the same backend
 *  logic so the browser application works correctly.
 *
 *  OOP CONCEPTS SHOWN:
 *    1. ENCAPSULATION  — private-style fields, getter methods
 *    2. INHERITANCE    — Customer extends User,
 *                        Electronics/Clothing extend Product
 *    3. ABSTRACTION    — Payment base class with pay() "abstract"
 *    4. POLYMORPHISM   — pay() behaves differently per subclass
 * ============================================================
 */

// ===========================================================
// 1. BASE CLASS: User  (ENCAPSULATION)
// ===========================================================
class User {
    // Private-style attributes (prefixed with _)
    constructor(name, email) {
        this._name  = name;   // ENCAPSULATION — controlled via getters
        this._email = email;
    }

    // Getters — Encapsulation: controlled read access
    getName()  { return this._name;  }
    getEmail() { return this._email; }

    login() {
        return `[User] ${this._name} logged in with ${this._email}`;
    }
}

// ===========================================================
// 2. CHILD CLASS: Customer  (INHERITANCE + POLYMORPHISM)
// ===========================================================
class Customer extends User {   // <-- INHERITANCE
    constructor(name, email) {
        super(name, email);   // Call parent constructor
        this._cart = new Cart();
    }

    // POLYMORPHISM — overrides User.login()
    login() {
        return `[Customer] Welcome, ${this.getName()}! You are logged in as a Customer.`;
    }

    getCart() { return this._cart; }

    addToCart(product) {
        return this._cart.addProduct(product);
    }

    placeOrder() {
        return this._cart.placeOrder();
    }
}

// ===========================================================
// 3. BASE CLASS: Product  (ENCAPSULATION + ABSTRACTION)
// ===========================================================
class Product {
    constructor(id, name, price) {
        this._id    = id;
        this._name  = name;
        this._price = price;
    }

    getId()    { return this._id;    }
    getName()  { return this._name;  }
    getPrice() { return this._price; }

    // ABSTRACTION — to be overridden by subclasses
    displayInfo() {
        return `Product: ${this._name} | Rs.${this._price}`;
    }

    getType() { return "Product"; }
}

// ===========================================================
// 4. CHILD CLASS: Electronics  (INHERITANCE + POLYMORPHISM)
// ===========================================================
class Electronics extends Product {   // <-- INHERITANCE
    constructor(id, name, price, warrantyMonths) {
        super(id, name, price);
        this._warrantyMonths = warrantyMonths;
    }

    getWarranty() { return this._warrantyMonths; }
    getType()     { return "Electronics"; }

    // POLYMORPHISM — overrides Product.displayInfo()
    displayInfo() {
        return `[Electronics] ${this._name} | Rs.${this._price} | Warranty: ${this._warrantyMonths} months`;
    }
}

// ===========================================================
// 5. CHILD CLASS: Clothing  (INHERITANCE + POLYMORPHISM)
// ===========================================================
class Clothing extends Product {   // <-- INHERITANCE
    constructor(id, name, price, size) {
        super(id, name, price);
        this._size = size;
    }

    getSize()  { return this._size; }
    getType()  { return "Clothing"; }

    // POLYMORPHISM — overrides Product.displayInfo()
    displayInfo() {
        return `[Clothing] ${this._name} | Rs.${this._price} | Size: ${this._size}`;
    }
}

// ===========================================================
// 6. CART CLASS  (ENCAPSULATION)
// ===========================================================
class Cart {
    constructor() {
        this._items = [];   // Private-style product list
    }

    addProduct(product) {
        this._items.push(product);
        return `Added: ${product.getName()} (Rs.${product.getPrice()})`;
    }

    removeProduct(productId) {
        const before = this._items.length;
        this._items = this._items.filter(p => p.getId() !== productId);
        if (this._items.length < before) {
            return `Removed product ID ${productId}`;
        }
        return `Product ID ${productId} not found in cart.`;
    }

    calculateTotal() {
        return this._items.reduce((sum, p) => sum + p.getPrice(), 0);
    }

    getItems() { return this._items; }

    clear() { this._items = []; }

    size() { return this._items.length; }
}

// ===========================================================
// 7. ORDER CLASS  (ENCAPSULATION)
// ===========================================================
class Order {
    constructor(orderId, cart) {
        this._orderId     = orderId;
        this._products    = [...cart.getItems()];  // Snapshot
        this._totalAmount = cart.calculateTotal();
        this._status      = "Pending";
    }

    getOrderId()      { return this._orderId;     }
    getTotalAmount()  { return this._totalAmount;  }
    getStatus()       { return this._status;       }
    getProducts()     { return this._products;     }

    placeOrder() {
        if (this._products.length === 0) {
            this._status = "Failed";
            return "Cart is empty — cannot place order.";
        }
        this._status = "Confirmed";
        return `Order ORD-${this._orderId} confirmed! Total: Rs.${this._totalAmount}`;
    }
}

// ===========================================================
// 8. ABSTRACT CLASS: Payment  (ABSTRACTION)
// ===========================================================
class Payment {
    constructor(amount) {
        if (new.target === Payment) {
            throw new Error("Payment is an abstract class and cannot be instantiated directly.");
        }
        this._amount = amount;
    }

    // "Abstract" method — must be overridden
    pay() {
        throw new Error("pay() must be implemented by subclasses.");
    }

    printReceipt() {
        return `Receipt: Rs.${this._amount} charged successfully.`;
    }
}

// ===========================================================
// 9. CHILD CLASS: UPIPayment  (INHERITANCE + POLYMORPHISM)
// ===========================================================
class UPIPayment extends Payment {   // <-- INHERITANCE
    constructor(amount, upiId) {
        super(amount);
        this._upiId = upiId;
    }

    // POLYMORPHISM — concrete implementation of abstract pay()
    pay() {
        return {
            method:  "UPI",
            upiId:   this._upiId,
            amount:  this._amount,
            status:  "SUCCESS",
            message: `Payment of Rs.${this._amount} via UPI (${this._upiId}) completed!`
        };
    }
}

// ===========================================================
// 10. CHILD CLASS: CardPayment  (INHERITANCE + POLYMORPHISM)
// ===========================================================
class CardPayment extends Payment {   // <-- INHERITANCE
    constructor(amount, last4, cardHolder) {
        super(amount);
        this._last4      = last4;
        this._cardHolder = cardHolder;
    }

    // POLYMORPHISM — concrete implementation of abstract pay()
    pay() {
        return {
            method:     "Card",
            cardHolder: this._cardHolder,
            last4:      this._last4,
            amount:     this._amount,
            status:     "SUCCESS",
            message:    `Payment of Rs.${this._amount} via Card (**** ${this._last4}) completed!`
        };
    }
}

// ===========================================================
//  PRODUCT CATALOGUE (Pre-loaded data)
// ===========================================================
const PRODUCTS = [
    new Electronics(101, "Dell Laptop",      55000, 24),
    new Electronics(102, "Samsung Phone",    18000, 12),
    new Electronics(103, "HD Webcam",         2500,  6),
    new Clothing   (201, "SRM T-Shirt",        499, "L"),
    new Clothing   (202, "Blue Jeans",        1299, "M"),
    new Clothing   (203, "Cotton Hoodie",     1799, "XL"),
    new Electronics(104, "Wireless Earbuds",  3499,  6),
    new Clothing   (204, "Track Pants",        899, "L"),
];

// ===========================================================
//  Global Application State
// ===========================================================
const currentUser = new Customer("Ravi Kumar", "ravi@srmist.edu.in");
let   orderCounter = 1001;
let   currentPage  = window.location.pathname.split("/").pop() || "index.html";

// Persist cart across pages using sessionStorage
function saveCart() {
    const items = currentUser.getCart().getItems().map(p => ({
        id:    p.getId(),
        type:  p.getType(),
        name:  p.getName(),
        price: p.getPrice(),
        extra: p.getType() === "Electronics" ? p.getWarranty() : p.getSize()
    }));
    sessionStorage.setItem("srmcart_items", JSON.stringify(items));
}

function loadCart() {
    const raw = sessionStorage.getItem("srmcart_items");
    if (!raw) return;
    const items = JSON.parse(raw);
    currentUser.getCart().clear();
    items.forEach(item => {
        let product;
        if (item.type === "Electronics") {
            product = new Electronics(item.id, item.name, item.price, item.extra);
        } else {
            product = new Clothing(item.id, item.name, item.price, item.extra);
        }
        currentUser.getCart().addProduct(product);
    });
}

// ---- Load persisted cart on page load ----
loadCart();
updateCartBadge();

// ===========================================================
//  PRODUCT LIST PAGE FUNCTIONS
// ===========================================================
function renderProducts() {
    const tbody = document.getElementById("product-tbody");
    if (!tbody) return;
    tbody.innerHTML = "";

    PRODUCTS.forEach(p => {
        const tr = document.createElement("tr");

        let extraCol = "";
        if (p instanceof Electronics) {
            extraCol = `${p.getWarranty()} months warranty`;
        } else if (p instanceof Clothing) {
            extraCol = `Size: ${p.getSize()}`;
        }

        tr.innerHTML = `
            <td>${p.getId()}</td>
            <td>${p.getName()}</td>
            <td>${p.getType()}</td>
            <td>Rs.${p.getPrice().toLocaleString()}</td>
            <td>${extraCol}</td>
            <td><button onclick="addToCartById(${p.getId()})">Add to Cart</button></td>
        `;
        tbody.appendChild(tr);
    });
}

function addToCartById(productId) {
    const product = PRODUCTS.find(p => p.getId() === productId);
    if (!product) return;
    currentUser.addToCart(product);
    saveCart();
    updateCartBadge();
    showMessage(`"${product.getName()}" added to cart!`);
}

// ===========================================================
//  CART PAGE FUNCTIONS
// ===========================================================
function renderCart() {
    const tbody   = document.getElementById("cart-tbody");
    const total   = document.getElementById("cart-total");
    const emptyMsg = document.getElementById("empty-msg");
    if (!tbody) return;

    const items = currentUser.getCart().getItems();
    tbody.innerHTML = "";

    if (items.length === 0) {
        if (emptyMsg) emptyMsg.style.display = "block";
        if (total)    total.textContent = "Total: Rs.0";
        return;
    }
    if (emptyMsg) emptyMsg.style.display = "none";

    items.forEach((p, idx) => {
        const tr = document.createElement("tr");
        tr.innerHTML = `
            <td>${p.getName()}</td>
            <td>${p.getType()}</td>
            <td>Rs.${p.getPrice().toLocaleString()}</td>
            <td><button onclick="removeFromCart(${p.getId()})">Remove</button></td>
        `;
        tbody.appendChild(tr);
    });

    const t = currentUser.getCart().calculateTotal();
    if (total) total.textContent = `Total: Rs.${t.toLocaleString()}`;
}

function removeFromCart(productId) {
    currentUser.getCart().removeProduct(productId);
    saveCart();
    updateCartBadge();
    renderCart();
}

// ===========================================================
//  CHECKOUT PAGE FUNCTIONS
// ===========================================================
function renderCheckoutSummary() {
    const summaryDiv = document.getElementById("order-summary");
    if (!summaryDiv) return;

    const items = currentUser.getCart().getItems();
    const total = currentUser.getCart().calculateTotal();

    if (items.length === 0) {
        summaryDiv.innerHTML = "<p>Your cart is empty. <a href='index.html'>Browse products</a></p>";
        return;
    }

    let html = "<table><thead><tr><th>Product</th><th>Type</th><th>Price</th></tr></thead><tbody>";
    items.forEach(p => {
        html += `<tr><td>${p.getName()}</td><td>${p.getType()}</td><td>Rs.${p.getPrice().toLocaleString()}</td></tr>`;
    });
    html += `</tbody></table><p class="checkout-total">Total Amount: Rs.${total.toLocaleString()}</p>`;
    summaryDiv.innerHTML = html;
}

function processPayment() {
    const method      = document.getElementById("payment-method").value;
    const resultDiv   = document.getElementById("payment-result");
    const items       = currentUser.getCart().getItems();
    const total       = currentUser.getCart().calculateTotal();

    if (items.length === 0) {
        resultDiv.innerHTML = "<p style='color:red'>Cart is empty!</p>";
        return;
    }

    // Create Order object
    const order = new Order(orderCounter++, currentUser.getCart());
    const orderMsg = order.placeOrder();

    // POLYMORPHISM — different pay() behaviour based on method chosen
    let payment, result;
    if (method === "upi") {
        const upiId = document.getElementById("upi-id").value || "user@upi";
        payment = new UPIPayment(total, upiId);
    } else {
        const last4  = document.getElementById("card-last4").value  || "0000";
        const holder = document.getElementById("card-holder").value || "Customer";
        payment = new CardPayment(total, last4, holder);
    }

    result = payment.pay();   // POLYMORPHIC CALL

    resultDiv.innerHTML = `
        <div class="success-box">
            <h3>Order Placed Successfully!</h3>
            <p><strong>Order ID:</strong> ORD-${order.getOrderId()}</p>
            <p><strong>Items:</strong> ${order.getProducts().length}</p>
            <p><strong>Amount Paid:</strong> Rs.${total.toLocaleString()}</p>
            <p><strong>Payment:</strong> ${result.method}</p>
            <p><strong>Status:</strong> ${result.status}</p>
            <p>${result.message}</p>
            <a href="index.html">Continue Shopping</a>
        </div>
    `;

    // Clear cart after successful payment
    currentUser.getCart().clear();
    saveCart();
    updateCartBadge();
}

function togglePaymentFields() {
    const method = document.getElementById("payment-method").value;
    const upiDiv  = document.getElementById("upi-fields");
    const cardDiv = document.getElementById("card-fields");
    if (upiDiv)  upiDiv.style.display  = method === "upi"  ? "block" : "none";
    if (cardDiv) cardDiv.style.display = method === "card" ? "block" : "none";
}

// ===========================================================
//  UTILITY
// ===========================================================
function updateCartBadge() {
    const badge = document.getElementById("cart-badge");
    if (badge) badge.textContent = `Cart (${currentUser.getCart().size()})`;
}

function showMessage(msg) {
    const msgDiv = document.getElementById("msg");
    if (!msgDiv) return;
    msgDiv.textContent = msg;
    msgDiv.style.display = "block";
    setTimeout(() => { msgDiv.style.display = "none"; }, 2500);
}

// ===========================================================
//  PAGE INIT
// ===========================================================
window.addEventListener("DOMContentLoaded", () => {
    updateCartBadge();

    if (document.getElementById("product-tbody")) {
        renderProducts();
    }
    if (document.getElementById("cart-tbody")) {
        renderCart();
    }
    if (document.getElementById("order-summary")) {
        renderCheckoutSummary();
        togglePaymentFields();
    }
});
