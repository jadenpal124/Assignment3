/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS */
//================================ 
/* This module is the implementation of the changeRequest class. 
   changeRequest class contains all the data about change request and functions to access them. */
//================================ 
#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include <iostream>
#include <cstring>
#include "User.h"
#include "Product.h"
#include "changeItem.h"
#include "Release.h"
using namespace std;

//================================ 
class changeRequest {
//----------------------
public:
    // Constructors
    changeRequest();
    // Default constructor initializing changeRequest and name to empty strings.
    changeRequest(const changeItem& changeItem, const User& user, const Release* associatedRelease);
    // Parameterized constructor initializing productID and name with provided values.
    // Parameters:
    //   - productID: Pointer to a character array containing the product ID (input)
    //   - name: Pointer to a character array containing the product name (input)

    //----------------------
    // Getter methods

    const Product& getProduct() const;
    // Parameters: None (no parameters)
    // Returns:
    //   Reference to a constant Product object representing the associated product.
    // Description:
    //   Returns the associated Product object of the change request.

    const User& getUser() const;
    // Parameters: None (no parameters)
    // Returns:
    //   Reference to a constant User object representing the associated user.
    // Description:
    //   Returns the associated User object of the change request.

    const changeItem& getChangeItem() const;
    // Parameters: None (no parameters)
    // Returns:
    //   Reference to a constant changeItem object representing the associated change item.
    // Description:
    //   Returns the associated changeItem object of the change request.

    const Release& getAssociatedRelease() const;
    // Parameters: None (no parameters)
    // Returns:
    //   Reference to a constant Release object representing the associated change request.
    // Description:
    //   Returns the associated Release object of the change request.

    //----------------------
    // Setter methods

    void setProduct(const Product& product);
    // Parameters:
    //   - product: Reference to a constant Product object representing the associated change request. (input)
    // Description:
    //   Sets the product of the changeRequest object to the provided value.

    void setUser(const User& user);
    // Parameters:
    //   - user: Reference to a constant Product object representing the associated change request. (input)
    // Description:
    //   Sets the product of the changeRequest object to the provided value.

    void setChangeItem(const changeItem& changeItem);
    // Parameters:
    //   - changeItem: Reference to a constant changeItem object representing the associated change request. (input)
    // Description:
    //   Sets the change item of the changeRequest object to the provided value.

    void setAssociatedRelease(const Release& associatedRelease);
    // Parameters:
    //   - associatedRelease: Reference to a constant Product object representing the associated change request. (input)
    // Description:
    //   Sets the associatedRelease of the changeRequest object to the provided value.

    //----------------------
    // Utility methods
    bool addChangeRequest(const char* fileName);
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    // Returns:
    //   true if the change request was successfully added to the file, false otherwise.
    // Description:
    //   Adds the changeRequest object to the file identified by fileName.

//----------------------
private:
    User user; // User object to reference User class
    Product product; // Product object to reference Product class
    changeItem ChangeItem; // changeItem object to reference changeItem class
    Release associatedRelease; // Release object to reference Release class
    char dateRequested[11]; // Assuming release date format YYYY-MM-DD
};
//================================

#endif // CHANGEREQUEST_H
