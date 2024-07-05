//Revision History: 
//Rev. 1 - 04/07/24 Original by JAWS
//==================================================
//This module is the implementation of the changeItem class.
//changeItem class contains all the data about a change item and functions to access and modify them.
//==================================================
#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include <iostream>
#include <cstring>
#include "Release.h" // Include Release class header
#include "Product.h" // Include Product class header

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
    changeItem(); // Default constructor

    changeItem(int changeItemID, const char* description, const Product* product, const Release* releasePtr); 
    // Description: Parameterized constructor initializing changeItemID, description, associated product, and release with provided values.
    // Parameters:
    //   - changeItemID: Integer ID of the change item (input)
    //   - description: Pointer to a character array containing the description (input)
    //   - product: Pointer to the associated Product object (input)
    //   - releasePtr: Pointer to the anticipated Release object (input)

    // Getter methods
    //----------------------
    int getChangeItemID() const;   
    // Description: Getter for retrieving change item ID
    // Parameters: None.
    // Exceptions: None.

    //----------------------
    const char* getDescription() const;     
    // Description: Getter for retrieving change item description
    // Parameters: None.
    // Exceptions: None.

    //----------------------
    const Release* getAnticipatedReleaseID() const;    
    // Description: Getter for retrieving anticipated release ID
    // Parameters: None.
    // Exceptions: None.

    //----------------------
    Status getStatus() const;    
    // Description: Getter for retrieving status of change item
    // Parameters: None.
    // Exceptions: None.

    //----------------------
    const Product* getAssociatedProduct() const;    
    // Description: Getter for retrieving associated product
    // Parameters: None.
    // Exceptions: None.

    // Setter methods
    //----------------------
    void setChangeItemID(int changeItemID); 
    // Description: Setter for setting change item ID
    // Parameters:
    //   - changeItemID: Integer ID of the change item (input)
    // Exceptions: None.

    //----------------------
    void setDescription(const char* description);     
    // Description: Setter for setting change item description
    // Parameters:
    //   - description: Pointer to a character array containing the description (input)
    // Exceptions: None.

    //----------------------
    void setStatus(Status status);   
    // Description: Setter for setting status
    // Parameters:
    //   - status: Enum value representing the status of the change item (input)
    // Exceptions: None.

    //----------------------
    void setAnticipatedRelease(const Release* releasePtr);   
    // Description: Setter for setting anticipated release
    // Parameters:
    //   - releasePtr: Pointer to the anticipated Release object (input)
    // Exceptions: None.

    //----------------------
    void setAssociatedProduct(const Product* productPtr);   
    // Description: Setter for setting associated product
    // Parameters:
    //   - productPtr: Pointer to the associated Product object (input)
    // Exceptions: None.


    // Utility methods
    //----------------------
    bool checkChangeItem(const char* fileName, int changeItemIDToFind); 
    // Description: Method to check if change item ID exists in the given file
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - changeItemIDToFind: Integer ID of the change item to find (input)
    // Exceptions: None.

    //----------------------
    bool updateChangeItem(const char* fileName, int changeItemIDToFind);
    // Description: Method to update the change item with the given ID in the given file
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - changeItemIDToFind: Integer ID of the change item to find (input)
    // Exceptions: None.
   

    //----------------------
    bool addChangeItem(const char* fileName); 
    // Description: Method to add a change item to the given file
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    // Exceptions: None.

    //----------------------
    int searchChangeItemID(const char* fileName, int changeItemIDToFind); 
    // Description: Method to search for a change item ID in the given file
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - changeItemIDToFind: Integer ID of the change item to find (input)
    // Exceptions: None.

    void initChItem(int changeItemID, const char* description, const Product* product, const Release* releasePtr);
    // Description: Initializes the change item with the provided values.
    // Parameters:
    //   - changeItemID: Integer ID of the change item (input)
    //   - description: Pointer to a character array containing the description (input)
    //   - product: Pointer to the associated Product object (input)
    //   - releasePtr: Pointer to the anticipated Release object (input)
    // Exceptions: None.

    void closeChItem();
    // Description: save the change item and free the memory.
    // Parameters: None (no parameters)
    // Exceptions: None.

private:
    int changeItemID; // Member variable for storing change item ID (integer from [0, 999999])
    char description[100]; // Member variable for storing change item description (maximum length: 100 characters)
    Status status; // Member variable for storing status attribute
    const Release* getAnticipatedRelease; // Pointer to associated Release object
    const Product* associatedProduct; // Pointer to associated Product object
};
//==================================================

#endif // CHANGEITEM_H
