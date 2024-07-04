/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS */
//================================ 
/* This module is the implementation of the Product class. 
   User class contains all the data about user and functions to access them. */
//================================ 
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <cstring> // For string manipulation functions
using namespace std;
//================================
class Product {

public:
    
    Product(); // Default constructor
    // Default constructor initializing productID and name to empty strings.
    Product(const char* productID, const char* name); // Parameterized constructor
    // Parameterized constructor initializing productID and name with provided values.
    // Parameters:
    //   - productID: Pointer to a character array containing the product ID (input)
    //   - name: Pointer to a character array containing the product name (input)

    
    //----------------------
    // Getter methods

    const char* getProductID() const;
    // Retrieves the product ID.
    // Parameters: None (no parameters)

    //----------------------
    const char* getName() const;
    // Retrieves the product name.
    // Parameters: None (no parameters)

    //----------------------
    // Setter methods

    void setProductID(const char* productID);
    // Sets the product ID.
    // Parameters:
    //   - productID: Pointer to a character array containing the product ID (input)

    //----------------------
    void setName(const char* name);
    // Sets the product name.
    // Parameters:
    //   - name: Pointer to a character array containing the product name (input)

    //----------------------
    // Utility methods

    bool checkUserExists(const char* fileName, const char* productIDToFind); // Check if product exists in file
    // Checks if a product with the given ID exists in a file.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - productIDToFind: Pointer to a character array containing the product ID to search for (input)
    // Returns:
    //   - true if the product with the given ID exists in the file, false otherwise

    //----------------------
    bool addProduct(const char* fileName); // Add product to file
    // Adds a product to a file.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    // Returns:
    //   - true if the product successfully added to the file, false otherwise

//----------------------
private:
    char productID[8];
    // Member variable for storing product ID (max length: 8 characters)
    char name[30];
    // Member variable for storing product name (max length: 30 characters)
};
//================================

#endif // PRODUCT_H
