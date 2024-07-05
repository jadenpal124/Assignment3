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
    // Constructors
    //----------------------
    Release (); // Default constructor

    //----------------------
    Release (const char* releaseID, const Product& product, const char* releaseDate); // Parameterized constructor
    // Parameterized constructor initializing releaseID, product, and releaseDate with provided values.
    // Parameters:
    //   - releaseID: Pointer to a character array containing the release ID (input)
    //   - product: Reference to a Product object representing the associated product (input)
    //   - releaseDate: Pointer to a character array containing the release date (input)

    // Getter methods
    //----------------------
    const char* getReleaseID () const;
    // Retrieves the release ID.
    // Parameters: None (no parameters)

    //----------------------
    const Product& getProduct () const;
    // Retrieves the associated product.
    // Parameters: None (no parameters)

    //----------------------
    const char* getReleaseDate () const;
    // Retrieves the release date.
    // Parameters: None (no parameters)

    // Setter methods
    //----------------------
    void setReleaseID (const char* releaseID);
    // Sets the release ID.
    // Parameters:
    //   - releaseID: Pointer to a character array containing the release ID (input)

    //----------------------
    void setProduct (const Product& product);
    // Sets the associated product.
    // Parameters:
    //   - product: Reference to a Product object representing the associated product (input)

    //----------------------
    void setReleaseDate (const char* releaseDate);
    // Sets the release date.
    // Parameters:
    //   - releaseDate: Pointer to a character array containing the release date (input)

    // Utility methods
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
    bool checkRelease (const char* fileName, const char* releaseIDToFind);
    // Description:
    //   Checks if a release with the specified release ID exists in the file identified by fileName.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input).
    //   - releaseIDToFind: Pointer to a character array containing the release ID to search for (input).
    // Returns:
    //   true if the release with the given ID exists in the file, false otherwise.
    // Exceptions:
    //   May throw an exception if the file specified by fileName does not exist or cannot be accessed.

    // Session management methods
    //----------------------
    void initRelease ();
    // Description: Initializes the obj with default constructor

    //----------------------
    void closeRelase ();
    // Description: Delete the Object and frees any memory allocated on the heap.

private:
    char releaseID[8]; // Member variable for storing release ID (max length: 8 characters)
    Product product; // Product object representing the associated product
    char releaseDate[11]; // Member variable for storing release date (format: YYYY-MM-DD)
};

#endif // RELEASE_H
//==================================================
