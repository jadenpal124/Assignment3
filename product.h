//Revision History: 
//Rev. 1 - 04/07/24 Original by JAWS
//==================================================
//This module is the implementation of the Product class. 
//User class contains all the data about user and functions to access them.
//==================================================
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <cstring> // For string manipulation functions

using namespace std;
//==================================================
class Product {
public: 
    // Constructors
    Product(); // Default constructor initializing productID and name to empty strings.

    Product(const char* productID, const char* name); // Parameterized constructor
    // Description: Parameterized constructor initializing productID and name with provided values.
    // Parameters:
    //   - productID: Pointer to a character array containing the product ID (input)
    //   - name: Pointer to a character array containing the product name (input)

    // Getter methods
    //----------------------
    const char* getProductID() const;
    // Description: Retrieves the product ID.
    // Parameters: None
    // Exceptions: None.

    //----------------------
    const char* getName() const;
    // Description: Retrieves the product name.
    // Parameters: None
    // Exceptions: None.

    // Setter methods
    //----------------------
    void setProductID(const char* productID);
    // Description: Sets the product ID.
    // Parameters:
    //   - productID: Pointer to a character array containing the product ID (input)
    // Exceptions: None.

    //----------------------
    void setName(const char* name);
    // Description: Sets the product name.
    // Parameters:
    //   - name: Pointer to a character array containing the product name (input)
    // Exceptions: None.

    // Utility methods
    //----------------------
    bool checkUser(const char* fileName, const char* productIDToFind); 
    // Description: Checks if a product with the given ID exists in a file.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - productIDToFind: Pointer to a character array containing the product ID to search for (input)
    // Exceptions: None.

    //----------------------
    bool addProduct(const char* fileName);
    // Description: Adds a product to a file.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    // Exceptions: None.

    //----------------------
    bool checkaddProduct(const char* fileName, int productID); 
    // Description: Method to check if added product with the given ID in the given file has been successfully added.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - productID: Integer ID of the change item to find (input)
    // Exceptions: None.

    //----------------------
    bool checkProduct(const char* fileName, int productID); 
    // Description: Method to check if product with the given ID in the given file
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - productID: Integer ID of the change item to find (input)
    // Exceptions: None.

    //----------------------
    void initProduct(const char* productID, const char* name);
    // Description: Initializes the product with the provided values.
    // Parameters:
    //   - productID: Pointer to a character array containing the product ID (input)
    //   - name: Pointer to a character array containing the product name (input)
    // Exceptions: None.

    void closeProduct();
    // Description: save the product and free the memory.
    // Parameters: None (no parameters)
    // Exceptions: None.

private:
    char productID[8]; // Member variable for storing product ID (max length: 8 characters)
    char name[30]; // Member variable for storing product name (max length: 30 characters)
};
//==================================================

#endif // PRODUCT_H
