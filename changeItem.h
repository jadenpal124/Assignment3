// Revision History:
// Rev. 1 - 04/07/24 Original by JAWS
// Rev. 2 - 16/07/24 Updated by Soroush
//==================================================
// This module implements the changeItem class, which encapsulates data related to individual change items.
// The class provides methods to access, modify, and persist change item data, managing a file internally.
//==================================================
#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include <iostream>
#include <cstring>
#include <fstream>
#include "Release.h"    // Include Release class header
#include "Product.h"    // Include Product class header
#include <stdexcept>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;

//==================================================
class changeItem {
public:
    // Enum for status
    enum Status {
        Cancelled,        // Status when the change item is cancelled
        NewRequest,       // Status when a new change request is created
        ReviewRequest,    // Status when the change request is under review
        InProgress,       // Status when the change request is in progress
        Done              // Status when the change request is completed
    };

    // Constructors
    //----------------------
    changeItem ();    
    // Description: Default constructor

     //----------------------
    changeItem (int changeItemID, const char* description, const Product product, const Release releasePtr); 
    // Description: Parameterized constructor initializing changeItemID, description, associated product, and release with provided values.
    // Parameters:
    //     - changeItemID: Integer ID of the change item (input)
    //     - description: Pointer to a character array containing the description (input)
    //     - product: Pointer to the associated Product object (input)
    //     - releasePtr: Pointer to the anticipated Release object (input)

    // Getter methods
    //----------------------
    int getChangeItemID () const;    
    // Description: Getter for retrieving change item ID

    //----------------------
    const char* getDescription () const;     
    // Description: Getter for retrieving change item description

    //----------------------
    const Release getAnticipatedRelease () const;    
    // Description: Getter for retrieving anticipated release ID

    //----------------------
    Status getStatus () const;    
    // Description: Getter for retrieving status of change item

    const char* getStatusAsString() const;

    //----------------------
    const Product getAssociatedProduct () const;    
    // Description: Getter for retrieving associated product ID

    // Setter methods
    //----------------------
    void setChangeItemID (int changeItemID);    
    // Description: Setter for setting change item ID
    // Parameters:
    //     - changeItemID: Integer ID of the change item (input)

    //----------------------
    void setDescription (const char* description);     
    // Description: Setter for setting change item description
    // Parameters:
    //     - description: Pointer to a character array containing the description (input)

    //----------------------
    void setStatus (const string &newStatus);    
    // Description: Setter for setting status
    // Parameters:
    //     - newStatus: string value representing the status of the change item (input)

    //----------------------
    void setAnticipatedRelease (const Release releasePtr);    
    // Description: Setter for setting anticipated release
    // Parameters:
    //     - releasePtr: Pointer to the anticipated Release object (input)

    //----------------------
    void setAssociatedProduct (const Product productPtr);    
    // Description: Setter for setting associated product
    // Parameters:
    //     - productPtr: Pointer to the associated Product object (input)

    // Utility methods
    //----------------------
    void initChangeItem (const char* fileName);    
    // Description: Initializes the changeItem object and opens the specified file for operations
    // Parameters:
    //     - fileName: Pointer to a character array containing the file name (input)

    //----------------------
    void closeChangeItem ();    
    // Description: Closes the file and frees any allocated resources

    //----------------------
    bool updateChangeItem (changeItem changeItemToFind);    
    // Description: Method to update the change item with the given ID in the file
    // Parameters:
    //     - changeItemToFind: changeItem object with updated data (input)
    // Returns: true if the change item is successfully updated, false otherwise.
    // Exceptions: May throw an exception if the file cannot be accessed.

    //----------------------
    bool addChangeItem ();    
    // Description: Method to add a change item to the file
    // Returns: true if the change item is successfully added, false otherwise.
    // Exceptions: May throw an exception if the file cannot be accessed.

    //----------------------
    bool checkChangeItemID ();    
    // Description: Method to check if changeItem exists already
    // Returns: true if the change item is in file, false otherwise.
    // Exceptions: May throw an exception if the file cannot be accessed.

    //----------------------
    void displayRemainingReports (const Product productToFind) const;    
    // Description: Displays change items that still need to be implemented or are in progress.
    // Parameters:
    //     - productToFind: Pointer to the Product object to match against (input)
    // Exceptions: May throw an exception if the file cannot be accessed.

    //----------------------
    changeItem displayAndReturnChangeItem (const Product productToFind, const Release rel);    
    // Description: Displays and returns a change item based on the provided product.
    // Parameters:
    //     - productToFind: Pointer to the Product object to match against (input)
    // Returns: A changeItem object that matches the criteria.

    changeItem displayAndReturnChangeItemStatus (const Product productToFind);
    // Description: Displays change items stored in the currently managed file in batches of 5, allowing scrolling.
    //              User can press Enter to view the next 5 items or 'q' to stop.
    //              Allows the user to select and returns that change item.
    // Exceptions:
    //   May throw an exception if the file cannot be accessed.

    //----------------------
    changeItem::Status stringToStatus (const string &statusStr);
    // Description: Converts the status enum to a corresponding string representation.
    // Returns: A string representing the current status of the change item.

    //==================================================
private:
    int changeItemID;    // Member variable for storing change item ID (integer from [0, 999999])
    char description[30];    // Member variable for storing change item description (maximum length: 30 characters)
    Status status;    // Member variable for storing status attribute
    Release anticipatedRelease;    // Pointer to associated Release object
    Product associatedProduct;    // Pointer to associated Product object
    static std::fstream file;    // File stream for read and write operations

    int generateUniqueChangeItemID (); 
    // Description: Generates a unique change item ID using random number generation.
    // Returns: A randomly generated ID in the range [0, 999999].
    
};

//==================================================
#endif // CHANGEITEM_H
