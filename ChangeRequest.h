// Revision History:
// Rev. 1 - 04/07/24 Original by Soroush
//==================================================
// This module implements the changeRequest class, which encapsulates data related to change requests
// and provides methods to access and manipulate them. The class integrates data about users, products,
// change items, and associated releases, fostering high cohesion by managing cohesive operations within
// the context of change requests.
//==================================================

#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include <iostream>
#include <cstring>
#include "User.h"
#include "Product.h"
#include "changeItem.h"
#include "Release.h"

using namespace std;

//==================================================
class changeRequest {
public:
    // Constructors
    changeRequest (); // Default constructor initializing changeRequest and name to empty strings.

    changeRequest (const changeItem& changeItem, const User& user, const Release* associatedRelease);
    // Description: Parameterized constructor initializing productID and name with provided values.
    // Parameters:
    //   - productID: Pointer to a character array containing the product ID (input)
    //   - name: Pointer to a character array containing the product name (input)

    // Getter methods
    //----------------------
    const Product& getProduct () const;
    // Description: Returns the associated Product object of the change request.

    //----------------------
    const User& getUser () const;
    // Description: Returns the associated User object of the change request.

    //----------------------
    const changeItem& getChangeItem () const;
    // Description: Returns the associated changeItem object of the change request.

    //----------------------
    const Release& getAssociatedRelease () const;
    // Description: Returns the associated Release object of the change request.

    // Setter methods
    //----------------------
    void setProduct (const Product& product);
    // Description: Sets the product of the changeRequest object to the provided value.
    // Parameters:
    //   - product: Reference to a constant Product object representing the associated change request. (input)

    //----------------------
    void setUser (const User& user);
    // Description: Sets the product of the changeRequest object to the provided value.
    // Parameters:
    //   - user: Reference to a constant Product object representing the associated change request. (input)

    //----------------------
    void setChangeItem (const changeItem& changeItem);
    // Description: Sets the change item of the changeRequest object to the provided value.
    // Parameters:
    //   - changeItem: Reference to a constant changeItem object representing the associated change request. (input)

    //----------------------
    void setAssociatedRelease (const Release& associatedRelease);
    // Description: Sets the associatedRelease of the changeRequest object to the provided value.
    // Parameters:
    //   - associatedRelease: Reference to a constant Product object representing the associated change request. (input)

    // Utility Methods
    //----------------------
    bool addChangeRequest(const char* fileName);
    // Description: Creates and adds the changeRequest object to the file identified by fileName.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    // Returns: true if the change request was successfully added, false otherwise.
    // Exceptions:
    //   May throw an exception if the file specified by fileName does not exist or cannot be accessed.

    // Session management methods
    //----------------------
    void initChReq ();
    // Description: Initializes the change request by calling the default constructor
    //              and allocated any memeory on heap.

    //----------------------
    void closeChReq ();
    // Description: Delete the Object and frees any memory allocated on the heap.

private:
    User user; // User object to reference User class
    Product product; // Product object to reference Product class
    changeItem ChangeItem; // changeItem object to reference changeItem class
    Release associatedRelease; // Release object to reference Release class
    char dateRequested[11]; // Assuming release date format YYYY-MM-DD
};

#endif // CHANGEREQUEST_H
//==================================================
