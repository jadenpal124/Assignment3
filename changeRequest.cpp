// Revision History:
// Rev. 1 - 04/15/24 Original by Jaden Pal
//==================================================
// This module implements the changeRequest class, which encapsulates data related to change requests
// and provides methods to access and manipulate them. The class integrates data about users, products,
// change items, and associated releases, fostering high cohesion by managing cohesive operations within
// the context of change requests.
//==================================================

#include "changeRequest.h"
#include <string>
#include <iomanip>

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

//----------------------
bool changeRequest::addChangeRequest () {
// Description: Creates and adds the changeRequest object to the file.
// Returns: true if the change request was successfully added, false otherwise.
    // Ensure file is open
    if (!fileStream.is_open()) {
        cerr << "Error: File is not open for writing." << endl;
        return false;
    }

    // Write the entire object to file
    fileStream.clear();
    fileStream.write(reinterpret_cast<const char*>(this), sizeof(changeRequest));
    if (!fileStream) {
        cerr << "Error: Failed to write changeRequest to file." << endl;
        return false;
    }

    fileStream.flush(); // Ensure data is written to disk
    return true;
}

//----------------------
bool changeRequest::updateUser (User userToUpdate) {
    // Description: This will update the change Requests user in the change Request file, to maintain synchronization.
    // Parameters: 
    //   - userToUpdate: copy of new user to update (input). 

    // Ensure the file stream is open
    if (!fileStream.is_open()) {
        std::cerr << "Error: changeRequest.dat file is not open." << std::endl;
        return false;
    }

    // Move the read/write position to the beginning of the file
    fileStream.clear();
    fileStream.seekg(0, std::ios::beg); // Move the read pointer to the start
    fileStream.seekp(0, std::ios::beg); // Move the write pointer to the start

    changeRequest req;
    bool updated = false;

    // Read each record and update if a match is found
    while (fileStream.read(reinterpret_cast<char*>(&req), sizeof(changeRequest))) {
        if (strcmp(req.getUser().getUserID(), userToUpdate.getUserID()) == 0) {
            req.setUser(userToUpdate); // Update the user information
            
            // Move write pointer back to the start of the current record
            fileStream.seekp(-static_cast<long>(sizeof(changeRequest)), std::ios::cur);
            
            // Write the updated record
            fileStream.write(reinterpret_cast<const char*>(&req), sizeof(changeRequest));
            
            // Check if the write operation was successful
            if (!fileStream) {
                std::cerr << "Error: Failed to write updated change request to file." << std::endl;
                return false;
            }

            fileStream.flush();
            updated = true;
            break; // Exit loop after successful update
        }
    }

    // Clear any error flags and return the result
    fileStream.clear();
    return updated;
}

//----------------------
bool changeRequest::updateChangeItem (changeItem changeItemToUpdate) {
    // Description: This will update all changeItems in the changeRequest file that match the given changeItem ID to maintain synchronization.
    // Parameters: 
    //   - changeItemToUpdate: The updated changeItem with new status (input). 

    // Ensure the file stream is open
    if (!fileStream.is_open()) {
        std::cerr << "Error: changeRequest.dat file is not open." << std::endl;
        return false;
    }

    // Move the read/write position to the beginning of the file
    fileStream.clear();
    fileStream.seekg(0, std::ios::beg);
    fileStream.seekp(0, std::ios::beg);

    changeRequest req;
    bool updated = false;

    while (fileStream.read(reinterpret_cast<char*>(&req), sizeof(changeRequest))) {
        // Check if the changeItem within the current changeRequest matches the ID to be updated
        if (req.getChangeItem().getChangeItemID() == changeItemToUpdate.getChangeItemID()) {
            std::cout << "Updating ChangeItem ID: " << req.getChangeItem().getChangeItemID() << std::endl;
            std::cout << "Status : " << req.getChangeItem().getStatusAsString() << std::endl;

            // Update the changeItem within the changeRequest
            req.setChangeItem(changeItemToUpdate);

            cout << "UPDATED: " <<  changeItemToUpdate.getStatusAsString() << endl;

            std::cout << "Status : " << req.getChangeItem().getStatusAsString() << std::endl;

            // Move the file pointer back to the position where the record was read
            fileStream.seekp(-static_cast<long>(sizeof(changeRequest)), std::ios::cur);

            // Write the updated changeRequest back to the file
            fileStream.write(reinterpret_cast<const char*>(&req), sizeof(changeRequest));
            fileStream.flush();

            updated = true;
        }
    }

    if (!updated) {
        std::cerr << "Error: ChangeItem ID " << changeItemToUpdate.getChangeItemID() << " not found in any changeRequest record." << std::endl;
    }

    fileStream.clear();
    return updated;
}

void changeRequest::displayUsersToBeNotified(Product prod) {
    // Description: Displays a list of users who should be notified of requests that are implemented.
    // Parameters: 
    //  - prod: The Product object used to filter and display relevant users.

    // Check if file is open
    if (!fileStream.is_open()) {
        cerr << "Error: File is not open for reading." << endl;
        return;
    }

    const int numRecordsPerPage = 5; // Number of records to display per page
    int startRecord = 0; // Starting record index
    bool displayNextPage = true;

    // Loop to display items 
    while (true) {
        // Display header
        cout << "Users To Be Notified Report (Page " << (startRecord / numRecordsPerPage + 1) << ")" << endl;
        cout << setw(4) << right << "#" << "  ";
        cout << setw(25) << right << "User Name" << "  ";
        cout << setw(30) << right << "Email" << "  ";
        cout << setw(10) << right << "ChangeID" << "  ";
        cout << setw(22) << right << "Anticipated ReleaseID" << endl;
        cout << setw(4) << right << "--" << "  ";
        cout << setw(25) << right << "-------------------------"
             << "  ";
        cout << setw(30) << right << "------------------------------"
             << "  ";
        cout << setw(10) << right << "----------"
             << "  ";
        cout << setw(22) << right << "------------------------" << endl;

        // Read the file and display relevant information
        fileStream.clear();
        fileStream.seekg(startRecord * sizeof(changeRequest), ios::beg);

        bool endOfFile = false;
        int displayedCount = 0;
        changeRequest req;

        int i = startRecord; // Initialize i with the starting record index

        // loop to read items from file
        while (fileStream.read(reinterpret_cast<char*>(&req), sizeof(changeRequest))) {
            if (req.getChangeItem().getStatus() == changeItem::Status::Done &&
                strcmp(req.getChangeItem().getAssociatedProduct().getProductID(), prod.getProductID()) == 0) {
                // Display information in specified format
                cout << setw(4) << right << ++i << "  ";
                cout << setw(25) << right << req.getUser().getName() << "  ";
                cout << setw(30) << right << req.getUser().getEmail() << "  ";
                cout << setw(10) << right << req.getChangeItem().getChangeItemID() << "  ";
                cout << setw(22) << right << req.getChangeItem().getAnticipatedRelease().getReleaseID() << endl;
                ++displayedCount;

                if (displayedCount >= numRecordsPerPage) {
                    break; // Stop if the maximum number of records per page is reached
                }
            }
        }

        if (displayedCount < numRecordsPerPage) {
            cout << "End of File." << endl;
            break; // Exit if no records are found
        }

        // Prompt user for input
        cout << "Press <enter> to display the next " << numRecordsPerPage << " rows, or \"q\" to go back." << endl;
        cout << "To return to menu type \"0\": ";

        string selection;
        getline(cin, selection);

        if (selection.empty()) {
            // Default action: Display next page
            startRecord += numRecordsPerPage;
        } else if (selection == "q") {
            break;
        } else if (selection == "0") {
            break;
        } else {
            cout << "Invalid selection." << endl;
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
