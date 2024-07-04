/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS */
//==================================================
/* This module is the implementation of the Release class. 
   User class contains all the data about user and functions to access them. */
//==================================================
/* INCLUDE STATEMENTS */
#ifndef RELEASE_H
#define RELEASE_H

#include <iostream>
#include <cstring> // For string manipulation functions
#include "Product.h" // Include Product class header

using namespace std;

//==================================================



class Release {

public:
    //----------------------
    const char* getReleaseID() const;
    // Parameters: None (no parameters)
    // Returns:
    //   Pointer to a constant character array containing the release ID.
    // Description:
    //   Returns the release ID of the Release object.

    //----------------------
    const Product& getProduct() const;
    // Parameters: None (no parameters)
    // Returns:
    //   Reference to a constant Product object representing the associated product.
    // Description:
    //   Returns the associated Product object of the Release.

    //----------------------
    const char* getReleaseDate() const;
    // Parameters: None (no parameters)
    // Returns:
    //   Pointer to a constant character array containing the release date.
    // Description:
    //   Returns the release date of the Release object.

    //----------------------
    void setReleaseID(const char* releaseID);
    // Parameters:
    //   - releaseID: Pointer to a character array containing the release ID (input)
    // Description:
    //   Sets the release ID of the Release object to the provided value.

    //----------------------
    void setProduct(const Product& product);
    // Parameters:
    //   - product: Reference to a Product object representing the associated product (input)
    // Description:
    //   Sets the associated Product object of the Release.

    //----------------------
    void setReleaseDate(const char* releaseDate);
    // Parameters:
    //   - releaseDate: Pointer to a character array containing the release date (input)
    // Description:
    //   Sets the release date of the Release object to the provided value.

    //----------------------
    bool checkReleaseExists(const char* fileName, const char* releaseIDToFind);
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - releaseIDToFind: Pointer to a character array containing the release ID to search for (input)
    // Returns:
    //   true if the release with the given ID exists in the file, false otherwise.
    // Description:
    //   Checks if a release with the specified release ID exists in the file identified by fileName.

    //----------------------
    bool addRelease(const char* fileName);
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    // Returns:
    //   true if the release details were successfully added to the file, false otherwise.
    // Description:
    //   Adds the details of the Release object to the file identified by fileName.

    //----------------------
    const char* searchRelease(const char* fileName, const char* releaseIDToFind);
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - releaseIDToFind: Pointer to a character array containing the release ID to search for (input)
    // Returns:
    //   Pointer to a character array containing the details of the release if found, nullptr otherwise.
    // Description:
    //   Searches for a release with the specified release ID in the file identified by fileName and returns its details.

private:
    char releaseID[8];
    Product product; // Product object to reference Product class
    char releaseDate[11]; // Assuming release date format YYYY-MM-DD
};

#endif // RELEASE_H
