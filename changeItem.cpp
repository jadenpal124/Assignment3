// Revision History:
// Rev. 1 - 04/15/24 Original by JAWS
//==================================================
// This module implements the changeItem class, which encapsulates data related to individual change items.
// The class provides methods to access, modify, and persist change item data, managing a file internally.
//==================================================

#include "changeItem.h"
#include "changeRequest.h"
//==================================================
std::fstream changeItem::file; // Declare the file member variable
//==================================================

// Default constructor
changeItem::changeItem()
    : anticipatedRelease(), associatedProduct() {
    // Initialize description to empty
    memset(description, 0, sizeof(description));
    int generateID = generateUniqueChangeItemID();
    this->changeItemID = generateID;
}

//----------------------
changeItem::changeItem(int changeItemID, const char* description, const Product product, const Release releasePtr)
    : changeItemID(changeItemID), status(NewRequest), anticipatedRelease(releasePtr), associatedProduct(product) {
    // Description: Parameterized constructor initializing changeItemID, description, associated product, and release with provided values.
    // Parameters:
    //     - changeItemID: Integer ID of the change item (input)
    //     - description: Pointer to a character array containing the description (input)
    //     - product: Pointer to the associated Product object (input)
    //     - releasePtr: Pointer to the anticipated Release object (input)
    strncpy(this->description, description, sizeof(this->description) - 1);
    this->description[sizeof(this->description) - 1] = '\0';
}

//----------------------
int changeItem::getChangeItemID() const {
    // Description: Getter for retrieving change item ID
    return changeItemID;
}

//----------------------
const char* changeItem::getDescription () const {
    // Description: Getter for retrieving change item description
    return description;
}

//----------------------
const Release changeItem::getAnticipatedRelease () const {
    // Description: Getter for retrieving anticipated release ID
    return anticipatedRelease;
}

//----------------------
changeItem::Status changeItem::getStatus () const {
    // Description: Getter for retrieving status of change item
    return status;
}

const char* changeItem::getStatusAsString() const {
    switch (status) {
        case Cancelled:
            return "Cancelled";
        case NewRequest:
            return "NewRequest";
        case ReviewRequest:
            return "ReviewRequest";
        case InProgress:
            return "InProgress";
        case Done:
            return "Done";
        default:
            return "Unknown Status";
    }
}

//----------------------
const Product changeItem::getAssociatedProduct () const {
    // Description: Getter for retrieving associated product ID
    return associatedProduct;
}

//----------------------
void changeItem::setChangeItemID (int changeItemID) {
    // Description: Setter for setting change item ID
    // Parameters:
    //     - changeItemID: Integer ID of the change item (input)
    this->changeItemID = changeItemID;
}

//----------------------
void changeItem::setDescription (const char* description) {
    // Description: Setter for setting change item description
    // Parameters:
    //     - description: Pointer to a character array containing the description (input)
    strncpy(this->description, description, sizeof(this->description) - 1);
    this->description[sizeof(this->description) - 1] = '\0';
}

//----------------------
void changeItem::setStatus (const string &newStatus) {
    // Description: Setter for setting status
    // Parameters:
    //     - status: Enum value representing the status of the change item (input)
    this->status = stringToStatus(newStatus);
}

//----------------------
void changeItem::setAnticipatedRelease (const Release releasePtr) {
    // Description: Setter for setting anticipated release
    // Parameters:
    //     - releasePtr: Pointer to the anticipated Release object (input)
    this->anticipatedRelease = releasePtr;
}

//----------------------
void changeItem::setAssociatedProduct (const Product productPtr) {
    // Description: Setter for setting associated product
    // Parameters:
    //     - productPtr: Pointer to the associated Product object (input)
    associatedProduct = productPtr;
}

//----------------------
void changeItem::initChangeItem(const char* fileName) {
    file.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        file.clear();
        file.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open or create file " << fileName << std::endl;
            throw std::runtime_error("Error: Could not open or create file");
        }
        file.close();
        file.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
    }
    if (!file.is_open()) {
        std::cerr << "Error: Could not reopen file " << fileName << " for reading and writing" << std::endl;
        throw std::runtime_error("Error: Could not open file after creation attempt");
    }
}

//----------------------
void changeItem::closeChangeItem () {
    // Description: Closes the file and frees any allocated resources
    if (file.is_open()) {
        file.close();
    }
}

bool changeItem::checkChangeItemID () {
// Description: Method to check if changeItem exists already
// Returns: true if the change item is in file, false otherwise.
// Exceptions: May throw an exception if the file cannot be accessed.
    if (!file.is_open()) {
        cerr << "Error: File is not open." << endl;
        return false; // File not open, cannot check ID
    }

    // Clear any existing state of the file stream
    file.clear();
    file.seekg(0, ios::beg);

    changeItem temp;
    // Iterate through each record in the file
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(temp))) {
        if (temp.getChangeItemID() == this->changeItemID) {
            return true; // Change Item ID found
        }
    }

    return false; // Change Item ID not found
}


//----------------------
changeItem::Status changeItem::stringToStatus (const string& statusStr) {
    if (statusStr == "Cancelled") return Cancelled;
    if (statusStr == "NewRequest") return NewRequest;
    if (statusStr == "ReviewRequest") return ReviewRequest;
    if (statusStr == "InProgress") return InProgress;
    if (statusStr == "Done") return Done;

    // Default case if the input string doesn't match any known status
    throw std::invalid_argument("Invalid status string");
}


bool changeItem::updateChangeItem(changeItem changeItemToFind) {
    // Description: Updates a change item in the file based on user input.
    // Parameters:
    //     - changeItemToFind: The change item to find and update (input).
    // Returns: true if the change item is successfully updated, false otherwise.
    // Exceptions: May throw an exception if the file cannot be accessed.
    
    if (!file.is_open()) {
        cerr << "Error: File is not open." << endl;
        return false;
    }

    bool found = false;
    int changeItemToFindID = changeItemToFind.getChangeItemID();
    changeItem temp;
    changeRequest req;
    char userChoice;
    char userInput;
    char userInput2[9];
    char userInput3[30];
    string strStatus;
    Release tempReleaseFound;

    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg); // Rewind to the beginning of the file

    while (file.read(reinterpret_cast<char*>(&temp), sizeof(changeItem))) {
        if (temp.getChangeItemID() == changeItemToFindID) {
            found = true;
            cout << "\nCurrent details for Change ID " << changeItemToFindID << ":\n";
            cout << "ProductID: " << temp.getAssociatedProduct().getProductID() << "\n";
            cout << "ChangeID: " << temp.getChangeItemID() << "\n";
            cout << "Anticipated ReleaseID: " << temp.getAnticipatedRelease().getReleaseID() << "\n";
            cout << "Status: " << temp.getStatusAsString() << "\n";  // Use getStatusAsString
            cout << "Description: " << temp.getDescription() << "\n\n";

            while (true) {
                cout << "Enter the number of the field you want to update:\n";
                cout << "1) ReleaseID\n";
                cout << "2) Status\n";
                cout << "3) Description\n";
                cout << "0) Quit\n";
                cout << "Enter Selection: ";
                cin >> userInput;
                cin.ignore(); // Clear input buffer

                switch (userInput) {
                    case '1': {
                        cout << "Enter new Release ID (1-8 Character Length): ";
                        cin.getline(userInput2, 9);
                        cout << "Do you want to update Release ID to " << userInput2 << " (select Y/N)? ";
                        cin >> userChoice;
                        cin.ignore(); // Clear input buffer
                        if (userChoice == 'Y' || userChoice == 'y') {
                            tempReleaseFound.setReleaseID(userInput2);
                            tempReleaseFound.setReleaseDate(temp.getAnticipatedRelease().getReleaseDate());
                            tempReleaseFound.setProduct(temp.getAssociatedProduct());
                            tempReleaseFound.addRelease();
                            temp.setAnticipatedRelease(tempReleaseFound); // Update temp with new release
                            cout << "Release ID Successfully updated.\n";
                        }
                        break;
                    }
                    case '2': {
                        cout << "\nEnter new Status:\n";
                        cout << "1) NewRequest\n";
                        cout << "2) ReviewRequest\n";
                        cout << "3) InProgress\n";
                        cout << "4) Done\n";
                        cout << "5) Cancelled\n";
                        cout << "Enter Selection: ";
                        cin >> userInput;
                        cin.ignore(); // Clear input buffer
                        switch (userInput) {
                            case '1': strStatus = "NewRequest"; break;
                            case '2': strStatus = "ReviewRequest"; break;
                            case '3': strStatus = "InProgress"; break;
                            case '4': strStatus = "Done"; break;
                            case '5': strStatus = "Cancelled"; break;
                            default: strStatus = "Unknown"; break;
                        }
                        cout << "Do you want to update Status to " << strStatus << " (select Y/N)? ";
                        cin >> userChoice;
                        cin.ignore(); // Clear input buffer
                        if (userChoice == 'Y' || userChoice == 'y') {
                            temp.setStatus(strStatus);
                            cout << "Status Successfully updated.\n";
                        }
                        break;
                    }
                    case '3': {
                        cout << "Enter new Description (1-30 Character Length): ";
                        cin.getline(userInput3, 30);
                        cout << "Do you want to update the description to " << userInput3 << " (select Y/N)? ";
                        cin >> userChoice;
                        cin.ignore(); // Clear input buffer
                        if (userChoice == 'Y' || userChoice == 'y') {
                            temp.setDescription(userInput3);
                            cout << "Description Successfully updated.\n";
                        }
                        break;
                    }
                    case '0':
                        req.updateChangeItem(temp);
                        // Write the updated change item back to the file
                        file.seekp(-static_cast<long>(sizeof(changeItem)), ios::cur);
                        file.write(reinterpret_cast<const char*>(&temp), sizeof(changeItem));
                        file.flush(); // Ensure data is written to the file
                        return found;
                }
            }
        }
    }
}

//----------------------
bool changeItem::addChangeItem() {
    fstream file("changeItems.dat", ios::in | ios::out | ios::binary | ios::app);

    file.clear();

    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing." << endl;
        return false;
    }

    // Serialize the changeItem object
    file.write(reinterpret_cast<const char*>(this), sizeof(changeItem));

    if (!file.good()) {
        cerr << "Error: Failed to write change item to file." << endl;
        file.close();
        return false;
    }

    return true;
}

//----------------------
void changeItem::displayRemainingReports(const Product productToFind) const {
    // Description:
    //   Displays change items that still need to be implemented or are in progress.
    // Parameters:
    //     - productToFind: Reference to the Product object to match against (input)
    // Exceptions: May throw an exception if the file cannot be accessed.

    if (!file.is_open()) {
        throw runtime_error("File not open");
    }

    // Define constants
    const int ITEMS_PER_PAGE = 5; // Number of items per page
    const int STATUS_WIDTH = 20;  // Width of the Status column
    const int DESCRIPTION_WIDTH = 30; // Width of the Description column

    int startRecord = 0;          // Starting record index for the current page
    char userChoice;              // User choice to navigate pages
    int totalCount = 0;          // Total number of records that match the criteria
    int currentCount = 0;        // Number of records on the current page

    // First pass: Count the total number of matching records
    file.clear();
    file.seekg(0);
    changeItem item;
    while (file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
        if (item.getStatus() != changeItem::Status::Done && 
            strcmp(item.getAssociatedProduct().getProductID(), productToFind.getProductID()) == 0) {
            ++totalCount;
        }
    }

    // Check if there are no matching records
    if (totalCount == 0) {
        cout << "No matching records found." << endl;
        return;
    }

    // Display pages
    do {
        // Rewind to the beginning and seek to the starting record for the current page
        file.clear();
        file.seekg(0);
        currentCount = 0;

        // Print page header
        cout << "Remaining Items to be Implemented Report (Page " << (startRecord / ITEMS_PER_PAGE + 1) << ")" << endl;
        cout << setw(4) << "#"
             << setw(12) << "ProductID"
             << setw(12) << "ChangeID"
             << setw(12) << "ReleaseID"
             << setw(STATUS_WIDTH) << "Status"
             << setw(DESCRIPTION_WIDTH) << "Description" << endl;
        cout << setw(4) << "--"
             << setw(12) << "----------"
             << setw(12) << "----------"
             << setw(12) << "----------"
             << setw(STATUS_WIDTH) << "------------"
             << setw(DESCRIPTION_WIDTH) << "------------------------" << endl;

        // Seek to the start record for the current page
        file.seekg(startRecord * sizeof(changeItem), ios::beg);

        // Read and print records for the current page
        while (file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
            if (item.getStatus() != changeItem::Status::Done && 
                strcmp(item.getAssociatedProduct().getProductID(), productToFind.getProductID()) == 0) {
                // Print item details
                cout << setw(4) << (currentCount % ITEMS_PER_PAGE + 1)
                     << setw(12) << item.getAssociatedProduct().getProductID()
                     << setw(12) << item.getChangeItemID()
                     << setw(12) << item.getAnticipatedRelease().getReleaseID()
                     << setw(STATUS_WIDTH) << item.getStatusAsString()
                     << setw(DESCRIPTION_WIDTH) << item.getDescription() << endl;
                ++currentCount;
                if (currentCount % ITEMS_PER_PAGE == 0) {
                    break; // Stop reading for the current page
                }
            }
        }


        // Check if more pages are available
        if (startRecord + ITEMS_PER_PAGE >= totalCount) {
            cout << "End of records." << endl;
            break;
        }

        // Prompt user to go to the next page
        cout << "Press Enter to go to the next page, or 'q' to quit: ";
        cin.get(userChoice);
        cin.ignore(); // Clear input buffer

        if (userChoice == 'q' || userChoice == 'Q') {
            break; // Exit if user chooses to quit
        }

        // Move to the next page
        startRecord += ITEMS_PER_PAGE;
    } while (true);
}

//----------------------
changeItem changeItem::displayAndReturnChangeItem(const Product productToFind, const Release rel) {
    // Description: Displays change items stored in the currently managed file in batches of 5, allowing scrolling.
    //              User can press Enter to view the next 5 items or 'q' to stop.
    //              Allows the user to select and returns that change item.
    // Exceptions:
    //   May throw an exception if the file cannot be accessed.

    // Check if file is open
    if (!file.is_open()) {
        cerr << "Error: File is not open." << endl;
        return changeItem(); // Return a default changeItem in case of error
    }

    const int numRecordsPerPage = 5; // Number of records to display per page
    int startRecord = 0; // Starting record index

    bool displayNextPage = true;
    changeItem selectedItem; // To store the selected changeItem

    while (displayNextPage) {
        // Display header
        cout << " - Must Add or Select a Change Item:" << endl;
        cout << "Change Items Report (Page " << (startRecord / numRecordsPerPage + 1) << ")" << endl;
        cout << setw(2) << "#" << "  ";
        cout << setw(12) << "ProductID" << "  ";
        cout << setw(12) << "ChangeID" << "  ";
        cout << setw(12) << "ReleaseID" << "  ";
        cout << setw(10) << "Status" << "  ";
        cout << "Description" << endl;
        cout << setw(2) << "--" << "  ";
        cout << setw(12) << "----------" << "  ";
        cout << setw(12) << "----------" << "  ";
        cout << setw(12) << "----------" << "  ";
        cout << setw(10) << "--------" << "  ";
        cout << "-----------" << endl;

        // Display records
        bool endOfFile = false;
        int displayedCount = 0;
        file.clear();
        file.seekg(startRecord * sizeof(changeItem), ios::beg);

        for (int i = 0; i < numRecordsPerPage; ++i) {
            changeItem item;
            if (!file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
                endOfFile = true; // End of file
                break;
            }

            if (strcmp(item.getAssociatedProduct().getProductID(), productToFind.getProductID()) == 0) {
            cout << setw(2) << startRecord + i + 1 << "  ";
            cout << setw(12) << item.getAssociatedProduct().getProductID() << "  ";
            cout << setw(12) << item.getChangeItemID() << "  ";
            cout << setw(12) << item.getAnticipatedRelease().getReleaseID() << "  ";
            cout << setw(10) << item.getStatusAsString() << "  ";
            cout << item.getDescription() << endl;
            ++displayedCount;
            }
            
        }

        // Prompt user for input
        if (!endOfFile || displayedCount > 0) {
            cout << endl;
            cout << "Press <enter> to display the next " << numRecordsPerPage << " rows, or \"q\" to go back." << endl;
            cout << "If you would like to select an item type the number #." << endl;
            cout << "If a Change Item ID is known type \"s\" to enter it." << endl;
            cout << "To add a new change item type \"a\"." << endl;

            string selection;
            cout << "Enter Selection: ";
            getline(cin, selection);

            // Handle user input
            if (selection.empty()) {
                // Default action: Display next page
                startRecord += numRecordsPerPage;
            } else if (selection == "q") {
                displayNextPage = false; // Exit loop
                break;
            } else if (selection == "a") {
                // Add new change item
                changeItem newItem;
                bool validIDEntered = false;

                while (validIDEntered) {
                    if (newItem.checkChangeItemID()) {
                        validIDEntered = true;
                    } else {
                        int newId = generateUniqueChangeItemID();
                        newItem.setChangeItemID(newId);
                    }
                }


                newItem.setStatus("NewRequest");
                newItem.setAssociatedProduct(productToFind);

                Release anticipatedRelease;
                anticipatedRelease.setReleaseID(rel.getReleaseID()); // Or gather input from the user
                newItem.setAnticipatedRelease(anticipatedRelease);

                cout << "Enter Description: ";
                string description;
                getline(cin, description);
                newItem.setDescription(description.c_str());

                file.clear();
                file.seekp(0, ios::end); // Move to the end of the file
                if (file.write(reinterpret_cast<const char*>(&newItem), sizeof(changeItem))) {
                    cout << "Change item added successfully." << endl;
                    selectedItem = newItem;
                    return selectedItem;
                } else {
                    cout << "Failed to add change item." << endl;
                }
            } else if (selection == "s") {
                // Enter Change Item ID action
                cout << "Enter Change Item ID: ";
                int changeItemID;
                cin >> changeItemID;
                cin.ignore(); // Ignore the newline character left in the input buffer

                file.clear();
                file.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                changeItem item;
                while (file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
                    if (item.getChangeItemID() == changeItemID) {
                        cout << "Change Item found: " << endl;
                        cout << "ID: " << item.getChangeItemID() << " | Description: " << item.getDescription() << endl;
                        selectedItem = item;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Change Item ID not found." << endl;
                } else {
                    displayNextPage = false; // Exit loop if item is found
                }
            } else if (isdigit(selection[0])) {
                // Select by number action
                int selectedNumber = stoi(selection);
                file.clear();
                file.seekg((selectedNumber - 1) * sizeof(changeItem), ios::beg);
                changeItem item;
                if (file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
                    cout << "Change Item selected: " << item.getDescription() << endl;
                    selectedItem = item;
                    displayNextPage = false; // Exit loop if item is selected
                } else {
                    cout << "Invalid selection." << endl;
                }
            } else {
                cout << "Invalid selection." << endl;
            }
        } else {
            // End of file reached
            cout << "End of file reached. Press q to go back" << endl;
            cout << "If you would like to select an item type the number #." << endl;
            cout << "If a Change Item ID is known type \"s\" to enter it." << endl;
            cout << "To add a new change item type \"a\"." << endl;

            string selection;
            cout << "Enter Selection: ";
            getline(cin, selection);

            if (selection == "q") {
                displayNextPage = false; // Exit loop
                break;
            } else if (selection == "s") {
                // Enter Change Item ID action
                cout << "Enter Change Item ID: ";
                int changeItemID;
                cin >> changeItemID;
                cin.ignore(); // Ignore the newline character left in the input buffer

                file.clear();
                file.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                changeItem item;
                while (file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
                    if (item.getChangeItemID() == changeItemID) {
                        cout << "Change Item found: " << item.getDescription() << endl;
                        selectedItem = item;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Change Item ID not found." << endl;
                } else {
                    displayNextPage = false; // Exit loop if item is found
                }
            } else if (selection == "a") {
                // Add new change item
                changeItem newItem;
                bool validIDEntered = false;

                while (validIDEntered) {
                    if (newItem.checkChangeItemID()) {
                        validIDEntered = true;
                    } else {
                        int newId = generateUniqueChangeItemID();
                        newItem.setChangeItemID(newId);
                    }
                }
                newItem.setStatus("NewRequest");
                newItem.setAssociatedProduct(productToFind);

                Release anticipatedRelease;
                anticipatedRelease.setReleaseID(rel.getReleaseID()); // Or gather input from the user
                anticipatedRelease.setReleaseDate(rel.getReleaseDate()); // Or gather input from the user
                anticipatedRelease.setProduct(rel.getProduct()); // Or gather input from the user
                newItem.setAnticipatedRelease(anticipatedRelease);

                cout << "Enter Description: ";
                string description;
                getline(cin, description);
                newItem.setDescription(description.c_str());

                file.clear();
                file.seekp(0, ios::end); // Move to the end of the file
                if (file.write(reinterpret_cast<const char*>(&newItem), sizeof(changeItem))) {
                    cout << "Change item added successfully." << endl;
                    selectedItem = newItem;
                    return selectedItem;
                } else {
                    cout << "Failed to add change item." << endl;
                }
            } else if (isdigit(selection[0])) {
                // Select by number action
                int selectedNumber = stoi(selection);
                file.clear();
                file.seekg((selectedNumber - 1) * sizeof(changeItem), ios::beg);
                changeItem item;
                if (file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
                    cout << "Change Item selected: " << item.getChangeItemID() << endl;
                    cout << "check Change item Status: " << item.getStatusAsString() << endl;
                    selectedItem = item;
                    displayNextPage = false; // Exit loop if item is selected
                } else {
                    cout << "Invalid selection.\n\n";
                }
            } else {
                cout << "Invalid selection.\n\n" << endl;
            }
        }
    }

    return selectedItem; // Return the selected change item
}

changeItem changeItem::displayAndReturnChangeItemStatus (const Product productToFind) {
    // Description: Displays change items stored in the currently managed file in batches of 5, allowing scrolling.
    //              User can press Enter to view the next 5 items or 'q' to stop.
    //              Allows the user to select and returns that change item.
    // Exceptions:
    //   May throw an exception if the file cannot be accessed.

    // Check if file is open
    if (!file.is_open()) {
        cerr << "Error: File is not open." << endl;
        return changeItem(); // Return a default changeItem in case of error
    }

    const int numRecordsPerPage = 5; // Number of records to display per page
    int startRecord = 0; // Starting record index

    bool displayNextPage = true;
    changeItem selectedItem; // To store the selected changeItem

    while (displayNextPage) {
        // Display header
        cout << "Change Items Report (Page " << (startRecord / numRecordsPerPage + 1) << ")" << endl;
        cout << setw(2) << "#" << "  ";
        cout << setw(12) << "ProductID" << "  ";
        cout << setw(12) << "ChangeID" << "  ";
        cout << setw(12) << "ReleaseID" << "  ";
        cout << setw(10) << "Status" << "  ";
        cout << "Description" << endl;
        cout << setw(2) << "--" << "  ";
        cout << setw(12) << "----------" << "  ";
        cout << setw(12) << "----------" << "  ";
        cout << setw(12) << "----------" << "  ";
        cout << setw(10) << "--------" << "  ";
        cout << "-----------" << endl;

        // Display records
        bool endOfFile = false;
        int displayedCount = 0;
        file.clear();
        file.seekg(startRecord * sizeof(changeItem), ios::beg);

        for (int i = 0; i < numRecordsPerPage; ++i) {
            changeItem item;
            if (!file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
                endOfFile = true; // End of file
                break;
            }

            if (strcmp(item.getAssociatedProduct().getProductID(), productToFind.getProductID()) == 0) {
                cout << setw(2) << startRecord + i + 1 << "  ";
                cout << setw(12) << item.getAssociatedProduct().getProductID() << "  ";
                cout << setw(12) << item.getChangeItemID() << "  ";
                cout << setw(12) << item.getAnticipatedRelease().getReleaseID() << "  ";
                cout << setw(10) << item.getStatusAsString() << "  ";
                cout << item.getDescription() << endl;
                ++displayedCount;
            }
        }

        // Prompt user for input
        if (!endOfFile || displayedCount > 0) {
            cout << endl;
            cout << "Press <enter> to display the next " << numRecordsPerPage << " rows, or \"q\" to go back." << endl;
            cout << "If you would like to select an item, type the number #." << endl;
            cout << "If a Change Item ID is known, type \"s\" to enter it." << endl;

            string selection;
            cout << "Enter Selection: ";
            getline(cin, selection);

            // Handle user input
            if (selection.empty()) {
                // Default action: Display next page
                startRecord += numRecordsPerPage;
            } else if (selection == "q") {
                displayNextPage = false; // Exit loop
                break;
            } else if (selection == "s") {
                // Enter Change Item ID action
                cout << "Enter Change Item ID: ";
                int changeItemID;
                cin >> changeItemID;
                cin.ignore(); // Ignore the newline character left in the input buffer

                file.clear();
                file.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                changeItem item;
                while (file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
                    if (item.getChangeItemID() == changeItemID) {
                        cout << "Change Item found: " << endl;
                        cout << "ID: " << item.getChangeItemID() << " | Description: " << item.getDescription() << endl;
                        selectedItem = item;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Change Item ID not found." << endl;
                } else {
                    displayNextPage = false; // Exit loop if item is found
                }
            } else if (isdigit(selection[0])) {
                // Select by number action
                int selectedNumber = stoi(selection);
                file.clear();
                file.seekg((selectedNumber - 1) * sizeof(changeItem), ios::beg);
                changeItem item;
                if (file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
                    cout << "Change Item selected: " << item.getDescription() << endl;
                    selectedItem = item;
                    displayNextPage = false; // Exit loop if item is selected
                } else {
                    cout << "Invalid selection." << endl;
                }
            } else {
                cout << "Invalid selection." << endl;
            }
        } else {
            // End of file reached
            cout << "End of file reached. Press q to go back" << endl;
            cout << "If you would like to select an item, type the number #." << endl;
            cout << "If a Change Item ID is known, type \"s\" to enter it." << endl;

            string selection;
            cout << "Enter Selection: ";
            getline(cin, selection);

            if (selection == "q") {
                displayNextPage = false; // Exit loop
                break;
            } else if (selection == "s") {
                // Enter Change Item ID action
                cout << "Enter Change Item ID: ";
                int changeItemID;
                cin >> changeItemID;
                cin.ignore(); // Ignore the newline character left in the input buffer

                file.clear();
                file.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                changeItem item;
                while (file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
                    if (item.getChangeItemID() == changeItemID) {
                        cout << "Change Item found: " << item.getDescription() << endl;
                        selectedItem = item;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Change Item ID not found." << endl;
                } else {
                    displayNextPage = false; // Exit loop if item is found
                }
            } else if (isdigit(selection[0])) {
                // Select by number action
                int selectedNumber = stoi(selection);
                file.clear();
                file.seekg((selectedNumber - 1) * sizeof(changeItem), ios::beg);
                changeItem item;
                if (file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
                    cout << "Change Item selected: " << item.getChangeItemID() << endl;
                    cout << "check Change item Status: " << item.getStatusAsString() << endl;
                    selectedItem = item;
                    displayNextPage = false; // Exit loop if item is selected
                } else {
                    cout << "Invalid selection.\n\n";
                }
            } else {
                cout << "Invalid selection.\n\n" << endl;
            }
        }
    }

    return selectedItem; // Return the selected change item
}


// Function to generate a unique change item ID
int changeItem::generateUniqueChangeItemID() {
    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    // Generate a random number in the range [0, 999999]
    int id = rand() % 1000000; // 1000000 is exclusive

    return id;
}

changeItem& changeItem::operator=(const changeItem& other) {
    if (this != &other) {
        changeItemID = other.changeItemID;
        status = other.status;
        associatedProduct = other.associatedProduct;
        anticipatedRelease = other.anticipatedRelease;
        strncpy(description, other.description, sizeof(description) - 1);
        description[sizeof(description) - 1] = '\0';
    }
    return *this;
}