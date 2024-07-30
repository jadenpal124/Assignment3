// Revision History:
// Rev. 1 - 04/15/24 Original by Jaden Pal
//==================================================
// This module implements the changeRequest class, which encapsulates data related to change requests
// and provides methods to access and manipulate them. The class integrates data about users, products,
// change items, and associated releases, fostering high cohesion by managing cohesive operations within
// the context of change requests.
//==================================================

#include "changeRequest.h"

//==================================================
std::fstream changeRequest::fileStream;
//==================================================

// Default constructor
//----------------------
changeRequest::changeRequest () {
// Initialize all member variables to default or empty values
    user = User();               // Assuming User has a default constructor that sets values to default
    ChangeItem = changeItem();  // Assuming changeItem has a default constructor
    associatedRelease = Release(); // Assuming Release has a default constructor
    dateRequested[0] = '\0';    // Null-terminate the dateRequested string
}

// Parameterized constructor
//----------------------
changeRequest::changeRequest (const changeItem changeItem, const User user, const Release release, const char* date) 
// Description: Parameterized constructor initializing changeItem, user, associatedRelease, and dateRequested with provided values.
// Parameters:
//   - changeItem: Reference to the changeItem object (input)
//   - user: Reference to the User object (input)
//   - associatedRelease: Reference to the Release object (input)
//   - date: Pointer to a character array containing the date requested (input)
    : ChangeItem(changeItem), user(user), associatedRelease(release) {
    // Copy the date string, ensuring it fits within dateRequested
    strncpy(dateRequested, date, sizeof(dateRequested) - 1); // Copy up to size - 1 characters
    dateRequested[sizeof(dateRequested) - 1] = '\0';        // Ensure null-termination
}

//----------------------
const User& changeRequest::getUser () const {
// Description: Returns the associated User object of the change request.
    return user;
}

//----------------------
const changeItem& changeRequest::getChangeItem () const {
// Description: Returns the associated changeItem object of the change request.
    return ChangeItem;
}

//----------------------
const Release& changeRequest::getAssociatedRelease () const {
// Description: Returns the associated Release object of the change request.
    return associatedRelease;
}

//----------------------
const char* changeRequest::getDateRequested () const {
// Description: Returns the date requested associated with the change request.
    return dateRequested;
}

//----------------------
void changeRequest::setUser (const User& user) {
// Description: Sets the user of the changeRequest object to the provided value.
// Parameters:
//   - user: Reference to the User object representing the associated change request (input)
    this->user = user;
}

//----------------------
void changeRequest::setChangeItem (const changeItem& changeItem) {
// Description: Sets the change item of the changeRequest object to the provided value.
// Parameters:
//   - changeItem: Reference to the changeItem object representing the associated change request (input)
    this->ChangeItem = changeItem;
}

//----------------------
void changeRequest::setAssociatedRelease (const Release& associatedRelease) {
// Description: Sets the associated release of the changeRequest object to the provided value.
    this->associatedRelease = associatedRelease;
}

//----------------------
void changeRequest::setDateRequested (const char* date) {
// Description: Sets the date requested associated with the change request.
// Copy the date string, ensuring it fits within dateRequested
    strncpy(this->dateRequested, date, sizeof(this->dateRequested) - 1);  // Copy up to size - 1 characters
    this->dateRequested[sizeof(this->dateRequested) - 1] = '\0';        // Ensure null-termination
}

bool changeRequest::addChangeRequest() {
    // Ensure file is open
    if (!fileStream.is_open()) {
        cerr << "Error: File is not open for writing." << endl;
        return false;
    }

    // Ensure that all fields are set before writing
    // Debug output before writing
    cout << "Writing ChangeRequest with ChangeID: " << this->getChangeItem().getChangeItemID() << endl;
    cout << "ProductID: " << this->getChangeItem().getAssociatedProduct().getProductID() << endl;

    // Write the entire object to file
    fileStream.write(reinterpret_cast<const char*>(this), sizeof(changeRequest));
    if (!fileStream) {
        cerr << "Error: Failed to write changeRequest to file." << endl;
        return false;
    }

    fileStream.flush(); // Ensure data is written to disk
    return true;
}

//----------------------
void changeRequest::displayUsersToBeNotified(Product prod) {
    // Description: Displays a list of users who should be notified of requests that are implemented.

    // Check if file is open
    if (!fileStream.is_open()) {
        cerr << "Error: File is not open for reading." << endl;
        return;
    }

    const int numRecordsPerPage = 5; // Number of records to display per page
    int startRecord = 0; // Starting record index
    bool displayNextPage = true;

    while (displayNextPage) {
        // Display header
        cout << "Users To Be Notified Report (Page " << (startRecord / numRecordsPerPage + 1) << ")" << endl;
        cout << "User Name" << endl;
        cout << "ChangeID" << endl;
        cout << "ProductID" << endl;
        cout << "Anticipated ReleaseID" << endl;
        cout << "--------- " << endl;
        cout << "-------- " << endl;
        cout << "--------- " << endl;
        cout << "---------------------" << endl;

        // Read the file and display relevant information
        fileStream.clear();
        fileStream.seekg(startRecord * sizeof(changeRequest), ios::beg);

        bool endOfFile = false;
        int displayedCount = 0;

        changeRequest req;

        while (fileStream.read(reinterpret_cast<char*>(&req), sizeof(changeRequest))) {
            // Debug output
            cout << "Read ChangeRequest with ChangeID: " << req.getChangeItem().getChangeItemID() << endl;
            cout << "Status: " << req.getChangeItem().getStatusAsString() << endl;
            cout << "ProductID: " << req.getChangeItem().getAssociatedProduct().getProductID() << endl;

            if (req.getChangeItem().getStatusAsString() == "Done" &&
                strcmp(req.getChangeItem().getAssociatedProduct().getProductID(), prod.getProductID()) == 0) {
                // Display information in specified format
                cout << setw(20) << left << req.getUser().getName() << endl;
                cout << setw(8) << left << req.getChangeItem().getChangeItemID() << endl;
                cout << setw(8) << left << req.getChangeItem().getAssociatedProduct().getProductID() << endl;
                cout << setw(20) << left << req.getChangeItem().getAnticipatedRelease().getReleaseID() << endl;
                cout << endl;
                ++displayedCount;

                if (displayedCount >= numRecordsPerPage) {
                    break; // Stop if the maximum number of records per page is reached
                }
            }
        }

        if (displayedCount == 0) {
            cout << "No matching users to notify found." << endl;
            break; // Exit if no records are found
        }

        // Prompt user for input
        if (fileStream.eof() && displayedCount < numRecordsPerPage) {
            cout << "End of file reached. Press 'q' to go back" << endl;
            displayNextPage = false;
        } else {
            cout << "Press <enter> to display the next " << numRecordsPerPage << " rows, or \"q\" to go back." << endl;
            cout << "To return to menu type \"0\": ";

            string selection;
            getline(cin, selection);

            if (selection.empty()) {
                // Default action: Display next page
                startRecord += numRecordsPerPage;
            } else if (selection == "q") {
                // Quit action
                displayNextPage = false;
            } else if (selection == "0") {
                // Return to menu action
                displayNextPage = false;
            } else {
                cout << "Invalid selection." << endl;
            }
        }
    }
}


//----------------------
void changeRequest::initChReq (const char* fileName) {
// Description: Initializes the change request by opening the specified file for operations.
// Parameters:
//   - fileName: Pointer to a character array containing the file name (input)
    fileStream.open(fileName, ios::in | ios::out | ios::binary);
    
    if (!fileStream.is_open()) {
        // File could not be opened, attempt to create it
        fileStream.clear(); // Clear any error flags
        fileStream.open(fileName, ios::out | ios::binary | ios::trunc);
        
        if (!fileStream.is_open()) {
            cerr << "Error: Could not open or create file " << fileName << endl;
            throw runtime_error("Error: Could not open or create file");
        }
        fileStream.close(); // Close the file after creation

        // Reopen the file for reading and writing
        fileStream.open(fileName, ios::in | ios::out | ios::binary);
    }

    if (!fileStream.is_open()) {
        cerr << "Error: Could not reopen file " << fileName << " for reading and writing" << endl;
        throw runtime_error("Error: Could not open file after creation attempt");
    }
}

//----------------------
void changeRequest::closeChReq () {
    // Description: Closes the file
    if (fileStream.is_open()) {
        fileStream.close();
    }
}
