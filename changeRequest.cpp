#include "changeRequest.h"

// Default constructor
changeRequest::changeRequest() {
    // Initialize all member variables to default or empty values
    user = User();               // Assuming User has a default constructor that sets values to default
    ChangeItem = changeItem();  // Assuming changeItem has a default constructor
    associatedRelease = Release(); // Assuming Release has a default constructor
    dateRequested[0] = '\0';    // Null-terminate the dateRequested string
}

// Parameterized constructor
changeRequest::changeRequest(const changeItem changeItem, const User user, const Release release, const char* date) 
    : ChangeItem(changeItem), user(user), associatedRelease(release) {
    // Copy the date string, ensuring it fits within dateRequested
    strncpy(dateRequested, date, sizeof(dateRequested) - 1); // Copy up to size - 1 characters
    dateRequested[sizeof(dateRequested) - 1] = '\0';        // Ensure null-termination
}

// Destructor
changeRequest::~changeRequest() {
    closeChReq(); // Close the file upon destruction
}

//----------------------
const User& changeRequest::getUser() const {
    // Description: Returns the associated User object of the change request.
    return user;
}

//----------------------
const changeItem& changeRequest::getChangeItem() const {
    // Description: Returns the associated changeItem object of the change request.
    return ChangeItem;
}

//----------------------
const Release& changeRequest::getAssociatedRelease() const {
    // Description: Returns the associated Release object of the change request.
    return associatedRelease;
}

//----------------------
const char* changeRequest::getDateRequested() const {
    // Description: Returns the date requested associated with the change request.
    return dateRequested;
}

//----------------------
void changeRequest::setUser(const User& user) {
    // Description: Sets the user of the changeRequest object to the provided value.
    this->user = user;
}

//----------------------
void changeRequest::setChangeItem(const changeItem& changeItem) {
    // Description: Sets the change item of the changeRequest object to the provided value.
    this->ChangeItem = changeItem;
}

//----------------------
void changeRequest::setAssociatedRelease(const Release& associatedRelease) {
    // Description: Sets the associated release of the changeRequest object to the provided value.
    this->associatedRelease = associatedRelease;
}

//----------------------
void changeRequest::setDateRequested(const char* date) {
    // Description: Sets the date requested associated with the change request.
    // Copy the date string, ensuring it fits within dateRequested
    strncpy(this->dateRequested, date, sizeof(this->dateRequested) - 1);  // Copy up to size - 1 characters
    this->dateRequested[sizeof(this->dateRequested) - 1] = '\0';        // Ensure null-termination
}

//----------------------
bool changeRequest::addChangeRequest() {
    // Description: Creates and adds the changeRequest object to the file.
    // Ensure file is open
    if (!fileStream.is_open()) {
        cerr << "Error: File is not open for writing." << endl;
        return false;
    }

    // Write the entire object to file
    fileStream.write(reinterpret_cast<const char*>(this), sizeof(changeRequest));
    return true;
}

//----------------------
bool changeRequest::readFromFile() {
    // Description: Reads the changeRequest object from the file identified by fileName.
    // Returns: true if the change request was successfully read from the file, false otherwise.
    // Exceptions:
    //   May throw an exception if the file specified by fileName does not exist or cannot be accessed.
    if (!fileStream.is_open()) {
        cerr << "Error: File is not open for reading." << endl;
        return false;
    }

    fileStream.read(reinterpret_cast<char*>(this), sizeof(changeRequest));
    return fileStream.good();
}

//----------------------
void changeRequest::displayUsersToBeNotified() {
    // Description: Displays a list of users who should be notified of requests that are implemented.
    // Open the file in read mode
    ifstream inFile("defaultChangeRequest.bin", ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file for reading." << endl;
        return;
    }

    changeRequest req; // Temporary changeRequest object

    // Read the file and display relevant information
    while (inFile.read(reinterpret_cast<char*>(&req), sizeof(changeRequest))) {
        if (req.getChangeItem().getStatus() == changeItem::Status::Done) {
            cout << "Requester Name: " << req.getUser().getName() << endl;
            cout << "Requester Email: " << req.getUser().getEmail() << endl;
            cout << "---------------------------" << endl;
        }
    }

    inFile.close(); // Close the file
}

//----------------------
void changeRequest::initChReq(const char* fileName) {
    // Description: Initializes the change request by opening the specified file for operations.
    fileStream.open(fileName, ios::binary | ios::in | ios::out | ios::app); // Open for reading and writing
    if (!fileStream.is_open()) {
        cerr << "Error: Failed to open file " << fileName << endl;
    }
}

//----------------------
void changeRequest::closeChReq() {
    // Description: Closes the file and frees any allocated resources.
    if (fileStream.is_open()) {
        fileStream.close();
    }
}
