#include "Product.h"
#include <iostream>
#include <fstream>
#include <iomanip> // for std::setw
#include <cstdlib> // for std::exit

// Default constructor
Product::Product () {
  initProduct ();
}

// Parameterized constructor
Product::Product (const char* productID, const char* name) {
    initProduct ();
    setProductID (productID);
    setName (name);
}

// Getter methods
const char* Product::getProductID () const {
    return productID;
}

const char* Product::getName () const {
    return name;
}

// Setter methods
void Product::setProductID (const char* productID) {
    strncpy(this->productID, productID, sizeof (this->productID) - 1);
    this->productID[sizeof(this->productID) - 1] = '\0';
}

void Product::setName (const char* name) {
    strncpy(this->name, name, sizeof (this->name) - 1);
    this->productID[sizeof(this->name) - 1] = '\0';
}

bool Product::addProduct(const char* fileName) {
    ofstream outFile(fileName, ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    // Write product information to file
    outFile.write(reinterpret_cast<const char*>(this), sizeof(Product));
    outFile.close();
    return true;
}

// Utility methods
Product& Product::checkProduct(const char* fileName, const char* productIDToFind) {
    ifstream inFile(fileName, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw exception(); // Throwing exception if file cannot be opened
    }

    static Product product; // Static to ensure it persists after function ends
    bool found = false;

    // Search for the product by productID
    while (inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (strcmp(product.productID, productID) == 0) {
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) {
        cerr << "Error: Product with ID " << productID << " not found." << endl;
        throw exception(); // Throwing exception if product not found
    }

    return product;
}

void Product::initProduct () {
    memset(productID, 0, sizeof(productID));
    memset(name, 0, sizeof(name));
}

void Product::closeProduct () {
    // Delete the Object and frees any memory allocated on the heap.
    // This class does not use heap memory, so nothing to do here.
}
