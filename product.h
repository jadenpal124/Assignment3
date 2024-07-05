/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS */
//================================ 
/* This module implements the Product class, which encapsulates data related to a product.
   The class provides methods to access, modify, and manage product information,
   demonstrating the principles of abstraction and high cohesion by encapsulating
   related functionality within the Product class. */
//================================ 
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <cstring> // For string manipulation functions
using namespace std;

//================================
class Product {

public:
    
    // Constructors
    //----------------------
    Product (); // Default constructor

    //----------------------
    Product (const char* productID, const char* name); // Parameterized constructor
    // Parameterized constructor initializing productID and name with provided values.
    // Parameters:
    //   - productID: Pointer to a character array containing the product ID (input)
    //   - name: Pointer to a character array containing the product name (input)

    // Getter methods
    //----------------------

    const char* getProductID () const;
    // Retrieves the product ID.
    // Parameters: None (no parameters)

    //----------------------
    const char* getName () const;
    // Retrieves the product name.
    // Parameters: None (no parameters)

    // Setter methods
    //----------------------

    void setProductID (const char* productID);
    // Sets the product ID.
    // Parameters:
    //   - productID: Pointer to a character array containing the product ID (input)

    //----------------------
    void setName (const char* name);
    // Sets the product name.
    // Parameters:
    //   - name: Pointer to a character array containing the product name (input)


    // Utility methods
    //----------------------

    User& checkUserExists (const char* fileName, const char* productIDToFind); 
    // Description: Checks if a user with the given ID exists in a file.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - productIDToFind: Pointer to a character array containing the user ID to search for (input)
    // Returns:
    //   - Reference to the User object if the user with the given ID exists in the file.
    // Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.

    //----------------------
    bool addProduct (const char* fileName); 
    // Description: Creates a product and adds it to the file.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input/output)
    // Returns:
    //   - true if the product is successfully added to the file, false otherwise.
    // Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.

private:
    char productID[8]; // Member variable for storing product ID (max length: 8 characters)
    char name[30]; // Member variable for storing product name (max length: 30 characters)
};
//================================

#endif // PRODUCT_H
