/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS */
//==================================================
/* This module implements the Release class, which manages data related to software releases.

   The Release class encapsulates attributes such as releaseID, product, and releaseDate, each
   managed with specific getter and setter methods for accessing and modifying release information.
   Additionally, utility methods are provided for checking release existence, adding new releases,
   and searching for releases within specified files.

   The procedures exhibit functional cohesion by collectively managing operations related to release
   data, ensuring encapsulation and promoting reusability across modules. */
//==================================================

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
    const char* getReleaseID () const;
    // Parameters: None (no parameters)
    // Returns:
    //   Pointer to a constant character array containing the release ID.
    // Description:
    //   Returns the release ID of the Release object.

    //----------------------
    const Product& getProduct () const;
    // Parameters: None (no parameters)
    // Returns:
    //   Reference to a constant Product object representing the associated product.
    // Description:
    //   Returns the associated Product object of the Release.

    //----------------------
    const char* getReleaseDate () const;
    // Parameters: None (no parameters)
    // Returns:
    //   Pointer to a constant character array containing the release date.
    // Description:
    //   Returns the release date of the Release object.

    //----------------------
    void setReleaseID (const char* releaseID);
    // Parameters:
    //   - releaseID: Pointer to a character array containing the release ID (input)
    // Description:
    //   Sets the release ID of the Release object to the provided value.

    //----------------------
    void setProduct (const Product& product);
    // Parameters:
    //   - product: Reference to a Product object representing the associated product (input)
    // Description:
    //   Sets the associated Product object of the Release.

    //----------------------
    void setReleaseDate (const char* releaseDate);
    // Parameters:
    //   - releaseDate: Pointer to a character array containing the release date (input)
    // Description:
    //   Sets the release date of the Release object to the provided value.
   
    //----------------------
    bool addRelease (const char* fileName);
    // Description:
    //   Adds the details of the Release object to the file identified by fileName.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    // Returns:
    //   true if the release details were successfully added to the file, false otherwise.
    // Exceptions:
    //   May throw an exception if the file specified by fileName does not exist or cannot be accessed.

    //----------------------
    bool checkRelease(const char* fileName, const char* releaseIDToFind);
    // Description:
    //   Checks if a release with the specified release ID exists in the file identified by fileName.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input).
    //   - releaseIDToFind: Pointer to a character array containing the release ID to search for (input).
    // Returns:
    //   true if the release with the given ID exists in the file, false otherwise.
    // Exceptions:
    //   May throw an exception if the file specified by fileName does not exist or cannot be accessed.

private:
    char releaseID[8];
    Product product; // Product object to reference Product class
    char releaseDate[11]; // Assuming release date format YYYY-MM-DD
};

#endif // RELEASE_H