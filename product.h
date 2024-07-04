#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <cstring> // For string manipulation functions
using namespace std;

class Product {

public:
    // Constructors
    Product(); // Default constructor
    Product(const char* productID, const char* name); // Parameterized constructor

    // Getter methods
    const char* getProductID() const;
    const char* getName() const;

    // Setter methods
    void setProductID(const char* productID);
    void setName(const char* name);

    // Utility methods
    bool checkUserExists(const char* fileName, const char* productIDToFind); // Check if product exists in file
    bool addProduct(const char* fileName); // Add product to file

private:
    char productID[8];
    char name[30];
};

#endif // PRODUCT_H
