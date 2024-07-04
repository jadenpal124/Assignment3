#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include <iostream>
#include <cstring>
#include "Release.h" // Include Release class header
#include "Product.h" // Include Product class header

using namespace std;

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
    changeItem(int changeItemID, const char* description, const Product* product, const Release* releasePtr); // Updated constructor

    // Getter methods
    int getChangeItemID() const;
    const char* getDescription() const;
    const Release* getAnticipatedReleaseID() const; // Getter for anticipated release ID
    Status getStatus() const; // Getter for status
    const Product* getAssociatedProduct() const; // Getter for associated Product

    // Setter methods
    void setChangeItemID(int changeItemID);
    void setDescription(const char* description);
    void setStatus(Status status); // Setter for status
    void setAnticipatedRelease(const Release* releasePtr); // Setter for associated Release
    void setAssociatedProduct(const Product* productPtr); // Setter for associated Product

    // Utility methods
    bool checkChangeItemIDExists(const char* fileName, int changeItemIDToFind);
    bool addChangeItem(const char* fileName);
    int searchChangeItemID(const char* fileName, int changeItemIDToFind);

private:
    int changeItemID; // Integer from [0, 999999]
    char description[100]; // Assuming maximum length for description
    Status status; // Status attribute
    const Release* getAnticipatedRelease; // Pointer to associated Release object
    const Product* associatedProduct; // Pointer to associated Product object
};

#endif // CHANGEITEM_H
