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
#include <fstream>
#include "User.h"
#include "Product.h"
#include "ChangeItem.h"
#include "Release.h"

using namespace std;

//==================================================
class changeRequest {
public:
    // Constructors
    changeRequest(); 
    // Default constructor initializing all member variables to default or empty values.

    changeRequest(const changeItem changeItem, const User user, const Release associatedRelease, const char* date);
    // Description: Parameterized constructor initializing changeItem, user, associatedRelease, and dateRequested with provided values.
    // Parameters:
    //   - changeItem: Reference to the changeItem object (input)
    //   - user: Reference to the User object (input)
    //   - associatedRelease: Reference to the Release object (input)
    //   - date: Pointer to a character array containing the date requested (input)

    // Getter methods
    //----------------------
    const User& getUser() const;
    // Description: Returns the associated User object of the change request.

    //----------------------
    const changeItem& getChangeItem() const;
    // Description: Returns the associated changeItem object of the change request.

    //----------------------
    const Release& getAssociatedRelease() const;
    // Description: Returns the associated Release object of the change request.

    //----------------------
    const char* getDateRequested() const;
    // Description: Returns the date requested associated with the change request.

    // Setter methods
    //----------------------
    void setUser(const User& user);
    // Description: Sets the user of the changeRequest object to the provided value.
    // Parameters:
    //   - user: Reference to the User object representing the associated change request (input)

    //----------------------
    void setChangeItem(const changeItem& changeItem);
    // Description: Sets the change item of the changeRequest object to the provided value.
    // Parameters:
    //   - changeItem: Reference to the changeItem object representing the associated change request (input)

    //----------------------
    void setAssociatedRelease(const Release& associatedRelease);
    // Description: Sets the associated release of the changeRequest object to the provided value.
    // Parameters:
    //   - associatedRelease: Reference to the Release object representing the associated change request (input)

    //----------------------
    void setDateRequested(const char* date);
    // Description: Sets the date requested associated with the change request.
    // Parameters:
    //   - date: Pointer to a character array containing the date requested (input)

    // Utility Methods
    //----------------------
    bool addChangeRequest();
    // Description: Creates and adds the changeRequest object to the file.
    // Returns: true if the change request was successfully added, false otherwise.

    //----------------------
    bool readFromFile();
    // Description: Reads the changeRequest object from the file identified by fileName.
    // Returns: true if the change request was successfully read from the file, false otherwise.
    // Exceptions:
    //   May throw an exception if the file specified by fileName does not exist or cannot be accessed.

    //----------------------
    void displayUsersToBeNotified(); 
    // Description: Displays a list of users who should be notified of requests that are implemented.

    // Session management methods
    //----------------------
    void initChReq(const char* fileName);
    // Description: Initializes the change request by opening the specified file for operations.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)

    //----------------------
    void closeChReq();
    // Description: Closes the file and frees any allocated resources.

private:
    User user; // User object to hold User class instance
    changeItem ChangeItem; // changeItem object to hold changeItem class instance
    Release associatedRelease; // Release object to hold Release class instance
    char dateRequested[11]; // Assuming date format YYYY-MM-DD
    static fstream fileStream; // File for reading and writing
};

#endif // CHANGEREQUEST_H
//==================================================
