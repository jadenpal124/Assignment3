
// Revision History:
// Rev. 1 - 04/07/24 Original by JAWS
// Rev. 2 - 16/07/24 Original by Soroush
//==================================================
// This module implements the changeItem class, which encapsulates data related to individual change items.
// The class provides methods to access, modify, and persist change item data, ensuring high cohesion
// by managing cohesive operations within the context of change items.
//==================================================
#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include <iostream>
#include <cstring>
#include "Release.h"    // Include Release class header
#include "Product.h"    // Include Product class header

using namespace std;

//==================================================
class changeItem {
public:
    // Enum for status
    enum Status {
        Cancelled,
        NewRequest,
        ReviewRequest,
        InProgress,
        Done
    };

    // Constructors
    changeItem();    // Default constructor

    changeItem(int changeItemID, const char* description, const Product* product, const Release* releasePtr); 
    // Description: Parameterized constructor initializing changeItemID, description, associated product, and release with provided values.
    // Parameters:
    //     - changeItemID: Integer ID of the change item (input)
    //     - description: Pointer to a character array containing the description (input)
    //     - product: Pointer to the associated Product object (input)
    //     - releasePtr: Pointer to the anticipated Release object (input)


    changeItem(const changeItem& other); 
    // Copy constructor creates a copy of the given Release object.
    // Parameters:
    //   - other: Reference to another Release object to copy from (input)


    changeItem& operator=(const changeItem& other);

    // Getter methods
    //----------------------
    int getChangeItemID () const;    
    // Description: Getter for retrieving change item ID

    //----------------------
    const string* getDescription () const;     
    // Description: Getter for retrieving change item description

    //----------------------
    const Release getAnticipatedRelease() const;
    // Description: Getter for retrieving anticipated release

    //----------------------
    const char* getAnticipatedReleaseID () const;    
    // Description: Getter for retrieving anticipated release ID

    //----------------------
    Status getStatus () const;    
    // Description: Getter for retrieving status of change item

    const Product getAssociatedProduct () const;

    //----------------------
    const char* getAssociatedProductID () const;    
    // Description: Getter for retrieving associated product

    // Setter methods
    //----------------------
    void setChangeItemID (int changeItemID);    
    // Description: Setter for setting change item ID
    // Parameters:
    //     - changeItemID: Integer ID of the change item (input)

    //----------------------
    void setDescription (const string descriptionNew);     
    // Description: Setter for setting change item description
    // Parameters:
    //     - description: Pointer to a character array containing the description (input)

    //----------------------
    void setStatus (Status status);    
    // Description: Setter for setting status
    // Parameters:
    //     - status: Enum value representing the status of the change item (input)

    //----------------------
    void setAnticipatedRelease (const Release* releasePtr);    
    // Description: Setter for setting anticipated release
    // Parameters:
    //     - releasePtr: Pointer to the anticipated Release object (input)

    //----------------------
    void setAssociatedProduct (const Product* productPtr);    
    // Description: Setter for setting associated product
    // Parameters:
    //     - productPtr: Pointer to the associated Product object (input)


    // Utility methods
    //----------------------
    changeItem& checkChangeItem (const char* fileName, int changeItemIDToFind);    
    // Description: Method to check if change item ID exists in the given file and return a reference to the found change item.
    // Parameters:
    //     - fileName: Pointer to a character array containing the file name (input)
    //     - changeItemIDToFind: Integer ID of the change item to find (input)
    // Returns: Reference to the changeItem object if found.
    // Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.

    //----------------------
    bool updateChangeItem (const char* fileName, int changeItemIDToFind);    
    // Description: Method to update the change item with the given ID in the given file
    // Parameters:
    //     - fileName: Pointer to a character array containing the file name (input)
    //     - changeItemIDToFind: Integer ID of the change item to find (input)
    // Returns: true if the change item is successfully updated, false otherwise.
    // Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.
   
    //----------------------
    bool addChangeItem (const char* fileName);    
    // Description: Method to add a change item to the given file
    // Parameters:
    //     - fileName: Pointer to a character array containing the file name (input)
    // Returns: true if the change item is successfully added to the file, false otherwise.
    // Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.

    //----------------------
    int searchChangeItemID (const char* fileName, int changeItemIDToFind);    
    // Description: Method to search for a change item ID in the given file
    // Parameters:
    //     - fileName: Pointer to a character array containing the file name (input)
    //     - changeItemIDToFind: Integer ID of the change item to find (input)
    // Returns: Position of the change item ID in the file, or -1 if not found.
    // Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.

    //----------------------
    void displayRemainingReports (const char* fileName) const;    
    // Description: Displays change items that still need to be implemented or are in progress.
    // Parameters:
    //     - fileName: Pointer to a character array containing the file name (input)
    // Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.


    //----------------------
    changeItem displayAndReturnChangeItem(const char* fileName, const char* productIDToFind) ;
    
    void initChangeItem (const char* fileName);
    // Description: Initializes the obj with default constructor

    //----------------------
    void closeChangeItem ();
    // Description: Delete the Object and frees any memory allocated on the heap.

private:
    int changeItemID;    // Member variable for storing change item ID (integer from [0, 999999])
    string description;    // Member variable for storing change item description (maximum length: 30 characters)
    Status status;    // Member variable for storing status attribute
    Release anticipatedRelease;    // Pointer to associated Release object
    Product associatedProduct;    // Pointer to associated Product object
    fstream file;  // File stream for read and write operations
    string fileName; // File name for operations
};

//==================================================
#endif // CHANGEITEM_H
