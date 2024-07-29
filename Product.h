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
#include <fstream>
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

    //----------------------
    Product(const Product& other); // Copy constructor

    //----------------------
    Product& operator=(const Product& other); // Assignment operator

    // Getter methods
    //----------------------
    const char* getProductID () const;
    // Retrieves the product ID.

    //----------------------
    const char* getName () const;
    // Retrieves the product name.

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
    Product& checkProductExists (const char* productIDToFind); 
    // Description: Checks if a product with the given Product ID exists in a file.
    // Parameters:
    //   - productIDToFind: Pointer to a character array containing the Product ID to search for (input)
    // Returns:
    //   - Reference to the Product object if the product with the given Product ID exists in the file.
    // Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.
    
    //----------------------
    bool addProduct (); 
    // Description: Creates a product and adds it to the file.
    // Returns:
    //   - true if the product is successfully added to the file, false otherwise.
    // Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.

    //----------------------
    Product displayProductFromFile () const;
    // Description: Displays and returns a product from the file.
    // Parameters: None (no parameters).
    // Returns: A Product object that matches the criteria.
    // Exceptions: May throw an exception if the file cannot be accessed.

    // Session management methods
    //----------------------
    void initProduct (const char* fileName);
    // Description: Initializes the obj with default constructor and opens the specified file for operations
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)

    //----------------------
    void closeProduct ();
    // Description: Deletes the Object and frees any memory allocated on the heap.

private:
    char productID[8]; // Member variable for storing product ID (max length: 8 characters)
    char name[30]; // Member variable for storing product name (max length: 30 characters)
    static fstream file; // File stream for read and write operations
};
//================================

#endif // PRODUCT_H
