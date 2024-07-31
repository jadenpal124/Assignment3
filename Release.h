/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS */
//================================ 
/* This module implements the Release class, which encapsulates data related to a release.
   The class provides methods to access, modify, and manage release information,
   including functionalities to add, check, and find releases in a file. The class
   uses a single file stream for efficient file operations. */
//================================ 
#ifndef RELEASE_H
#define RELEASE_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Product.h"

using namespace std;

//================================

class Release {
public:
    // Constructors
    //----------------------
    Release (); 
    // Default constructor initializes the release object with default values.

    //----------------------
    Release (const char* releaseID, const Product& product, const char* releaseDate); 
    // Parameterized constructor initializes the release object with provided values.
    // Parameters:
    //   - releaseID: Pointer to a character array containing the release ID (input)
    //   - product: Reference to a Product object representing the associated product (input)
    //   - releaseDate: Pointer to a character array containing the release date (input)

    //----------------------
    Release (const Release& other); 
    // Copy constructor creates a copy of the given Release object.
    // Parameters:
    //   - other: Reference to another Release object to copy from (input)

    Release& operator= (const Release& other);

    // Getter methods
    //----------------------
    const char* getReleaseID () const; 
    // Retrieves the release ID.

    //----------------------
    const Product getProduct () const;
    // Retrieves the associated Product object.

    //----------------------
    const char* getReleaseDate () const; 
    // Retrieves the release date.

    // Setter methods
    //----------------------
    void setReleaseID (const char* releaseID); 
    // Sets the release ID.
    // Parameters:
    //   - releaseID: Pointer to a character array containing the release ID (input)

    //----------------------
    void setProduct (const Product& product); 
    // Sets the associated Product object.
    // Parameters:
    //   - product: Reference to a Product object representing the associated product (input)

    //----------------------
    void setReleaseDate (const char* releaseDate); 
    // Sets the release date.
    // Parameters:
    //   - releaseDate: Pointer to a character array containing the release date (input)

    // File management methods
    //----------------------
    bool addRelease (); 
    // Adds the release object to the file.
    // Returns:
    //   - true if the release is successfully added to the file, false otherwise.
    // Exceptions: May throw an exception if the file is not open or in a good state.

    //----------------------
    bool checkRelease (const char* releaseIDToFind); 
    // Checks if a release with the given release ID exists in the file.
    // Parameters:
    //   - releaseIDToFind: Pointer to a character array containing the release ID to search for (input)
    // Returns:
    //   - true if the release with the given release ID exists in the file, false otherwise.
    // Exceptions: May throw an exception if the file is not open or in a good state.

    //----------------------
    Release findReleaseAndReturn (const Product prod); 
    // Finds and returns the release with the given release ID and product ID.
    // Parameters:
    //   - releaseIDToFind: Pointer to a character array containing the release ID to search for (input)
    //   - productIDtoFind: Pointer to a character array containing the product ID to search for (input)
    // Returns:
    //   - Release object if the release with the given IDs is found.
    // Exceptions: May throw an exception if the file is not open or in a good state.

    //----------------------
    void initRelease (const char* fileName); 
    // Initializes the release object and opens the file for both input and output operations.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name to open (input)
    // Exceptions: May throw an exception if the file cannot be opened.

    //----------------------
    void closeRelease (); 
    // Closes the file and releases resources.

private:
    char releaseID[8];     // Member variable for storing release ID (max length: 8 characters)
    Product product;        // Member variable for storing the associated Product object
    char releaseDate[12];   // Member variable for storing release date (max length: 12 characters)
    static fstream file;     // File stream for input and output operations
    string fileName;        // Store file name for accessing later
};
//================================

#endif // RELEASE_H
