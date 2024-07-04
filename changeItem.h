/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS */
//================================ 
/* This module is the implementation of the changeItem class.
   changeItem class contains all the data about a change item and functions to access and modify them. */
//================================ 
#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include <iostream>
#include <cstring>
#include "Release.h" // Include Release class header
#include "Product.h" // Include Product class header

using namespace std;
//================================ 
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
    changeItem(); 
    // Default constructor

    changeItem(int changeItemID, const char* description, const Product* product, const Release* releasePtr); 
    // Parameterized constructor initializing changeItemID, description, associated product, and release with provided values.
    // Parameters:
    //   - changeItemID: Integer ID of the change item (input)
    //   - description: Pointer to a character array containing the description (input)
    //   - product: Pointer to the associated Product object (input)
    //   - releasePtr: Pointer to the anticipated Release object (input)

    // Getter methods
    //----------------------
    int getChangeItemID() const;   
    // Getter for retrieving change item ID

    //----------------------
    const char* getDescription() const;     
    // Getter for retrieving change item description

    //----------------------
    const Release* getAnticipatedReleaseID() const;    
    // Getter for retrieving anticipated release ID

    //----------------------
    Status getStatus() const;    
    // Getter for retrieving status of change item

    //----------------------
    const Product* getAssociatedProduct() const;    
    // Getter for retrieving associated product

    // Setter methods
    //----------------------
    void setChangeItemID(int changeItemID); 
    // Setter for setting change item ID
    // Parameters:
    //   - changeItemID: Integer ID of the change item (input)

    //----------------------
    void setDescription(const char* description);     
    // Setter for setting change item description
    // Parameters:
    //   - description: Pointer to a character array containing the description (input)

    //----------------------
    void setStatus(Status status);   
    // Setter for setting status
    // Parameters:
    //   - status: Enum value representing the status of the change item (input)

    //----------------------
    void setAnticipatedRelease(const Release* releasePtr);   
    // Setter for setting anticipated release
    // Parameters:
    //   - releasePtr: Pointer to the anticipated Release object (input)

    //----------------------
    void setAssociatedProduct(const Product* productPtr);   
    // Setter for setting associated product
    // Parameters:
    //   - productPtr: Pointer to the associated Product object (input)


    // Utility methods
    //----------------------
    bool checkChangeItemIDExists(const char* fileName, int changeItemIDToFind); 
    // Method to check if change item ID exists in the given file
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - changeItemIDToFind: Integer ID of the change item to find (input)

    //----------------------
    bool addChangeItem(const char* fileName); 
    // Method to add a change item to the given file
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)

    //----------------------
    int searchChangeItemID(const char* fileName, int changeItemIDToFind); 
    // Method to search for a change item ID in the given file
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    //   - changeItemIDToFind: Integer ID of the change item to find (input)

private:
    int changeItemID; // Member variable for storing change item ID (integer from [0, 999999])
    char description[100]; // Member variable for storing change item description (maximum length: 100 characters)
    Status status; // Member variable for storing status attribute
    const Release* getAnticipatedRelease; // Pointer to associated Release object
    const Product* associatedProduct; // Pointer to associated Product object
};

#endif // CHANGEITEM_H
