// changeItem.cpp
// Revision History:
// Rev. 1 - 22/07/24 Original by JAWS
//==================================================
// This module implements the changeItem class, which encapsulates data related to individual change items.
// The class provides methods to access, modify, and persist change item data, managing a file internally.
//==================================================

#include "changeItem.h"

//==================================================

// Default constructor
changeItem::changeItem()
    : changeItemID(0), status(NewRequest), anticipatedRelease(), associatedProduct(), fileName(nullptr) {
    // Initialize description to empty
    memset(description, 0, sizeof(description));
}

//----------------------
changeItem::changeItem(int changeItemID, const char* description, const Product& product, const Release& releasePtr)
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
void changeItem::initChangeItem (const char* fileName) {
    // Description: Initializes the changeItem object and opens the specified file for operations
    // Parameters:
    //     - fileName: Pointer to a character array containing the file name (input)
    this->fileName = fileName;
    file.open(fileName, ios::in | ios::out | ios::binary);
    if (!file) {
        throw runtime_error("Failed to open file");
    }
}

//----------------------
void changeItem::closeChangeItem () {
    // Description: Closes the file and frees any allocated resources
    if (file.is_open()) {
        file.close();
    }
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


//----------------------
bool changeItem::updateChangeItem (changeItem changeItemToFind) {
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
    char userChoice;
    char userInput;
    char userInput2[9];
    char userInput3[30];
    string strStatus;
    Release tempReleaseFound;

    // Search for the change item by ID
    file.clear(); // Clear any error flags
    file.seekg(0, ios::beg); // Rewind to the beginning of the file

    while (file.read(reinterpret_cast<char*>(&temp), sizeof(changeItem))) {
        if (temp.getChangeItemID() == changeItemToFindID) {
            cout << "Current details for Change ID " << changeItemToFindID << ":\n";
            cout << "ProductID: " << temp.getAssociatedProduct().getProductID() << "\n";
            cout << "ChangeID: " << changeItemToFindID << "\n";
            cout << "Anticipated ReleaseID: " << temp.getAnticipatedRelease().getReleaseID() << "\n";
            cout << "Status: " << temp.getStatus() << "\n";
            cout << "Description: " << temp.getDescription() << "\n\n";

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
                    cin >> userInput2;
                    cin.ignore(); // Clear input buffer
                    if (userChoice == 'Y' || userChoice == 'y') {
                        tempReleaseFound.setReleaseID(userInput2);
                        tempReleaseFound.setReleaseDate(temp.getAnticipatedRelease().getReleaseDate());
                        tempReleaseFound.setProduct(temp.getAssociatedProduct());
                    }
                    break;
                }
                case '2': {
                    cout << "Enter new Status:\n";
                    cout << "1) NewRequest\n";
                    cout << "2) ReviewRequest\n";
                    cout << "3) InProgress\n";
                    cout << "4) Done\n";
                    cout << "5) Cancelled\n";
                    cout << "Enter Selection: ";
                    cin >> userInput;
                    cin.ignore(); // Clear input buffer
                    cin >> strStatus;
                    cout << "Do you want to update Status to " << temp.getStatus() << " (select Y/N)? ";
                    cin >> userInput2;
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
                    cin >> userInput2;
                    cin.ignore(); // Clear input buffer
                    if (userChoice == 'Y' || userChoice == 'y') {
                        temp.setDescription(userInput3);
                        cout << "Description Successfully updated.\n";
                    }
                    break;
                }
                case '0':
                    file.close();
                    return found;
            }

            // Write updated change item back to file
            file.seekp(-static_cast<int>(sizeof(changeItem)), ios::cur);
            file.write(reinterpret_cast<const char*>(&temp), sizeof(changeItem));
            found = true;
            break;
        }
    }

    return found;
}

//----------------------
bool changeItem::addChangeItem () {
    // Description: Method to add a change item to the file
    // Returns: true if the change item is successfully added, false otherwise.
    // Exceptions: May throw an exception if the file cannot be accessed.
    if (!file.is_open()) {
        throw runtime_error("File not open");
    }

    file.seekp(0, ios::end);
    file.write(reinterpret_cast<const char*>(this), sizeof(changeItem));
    return file.good();
}

//----------------------
void changeItem::displayRemainingReports (const Product& productToFind) const {
    // Description: Displays change items that still need to be implemented or are in progress.
    // Parameters:
    //     - productToFind: Pointer to the Product object to match against (input)
    // Exceptions: May throw an exception if the file cannot be accessed.
    if (!file.is_open()) {
        throw runtime_error("File not open");
    }

    // Define constants
    const int ITEMS_PER_PAGE = 5; // Number of items per page
    const int PAGE_WIDTH = 80;    // Width of the page (adjust as necessary)

    file.seekg(0);
    changeItem item;
    int count = 0;
    int page = 1;

    while (file.read(reinterpret_cast<char*>(&item), sizeof(changeItem))) {
        if (item.getStatus() != Done && (item.getAssociatedProduct().getProductID() == productToFind.getProductID())) {
            if (count % ITEMS_PER_PAGE == 0) {
                if (count > 0) {
                    // Print page separator
                    cout << string(PAGE_WIDTH, '-') << endl;
                }
                // Print header
                cout << "Remaining Items to be Implemented Report (Page " << (count / ITEMS_PER_PAGE + 1) << ")" << endl;
                cout << "#";
                cout << std::setw(12) << std::left << "ProductID";
                cout << std::setw(12) << std::left << "ChangeID";
                cout << std::setw(12) << std::left << "ReleaseID";
                cout << std::setw(10) << std::left << "Status";
                cout << "Description" << endl;
                cout << "--";
                cout << std::setw(12) << std::left << std::setfill('-') << "";
                cout << std::setw(12) << std::left << std::setfill('-') << "";
                cout << std::setw(12) << std::left << std::setfill('-') << "";
                cout << std::setw(10) << std::left << std::setfill('-') << "";
                cout << std::setfill('-') << "" << endl;
            }

            // Print item details
            cout << std::setw(2) << std::left << (count % ITEMS_PER_PAGE + 1);
            cout << std::setw(12) << std::left << item.getAssociatedProduct().getProductID();
            cout << std::setw(12) << std::left << item.getChangeItemID();
            cout << std::setw(12) << std::left << item.getAnticipatedRelease().getReleaseID();
            cout << std::setw(10) << std::left << item.getStatus();
            cout << item.getDescription() << endl;
            ++count;
        }
    }

    if (count % ITEMS_PER_PAGE > 0) {
        // Print page separator after last page
        cout << string(PAGE_WIDTH, '-') << endl;
    }
}

//----------------------
changeItem changeItem::displayAndReturnChangeItem (const Product& productToFind) const {
    // Description: Displays a list of change items with given product 
    //              and returns a change item based on the provided product.
    // Parameters:
    //     - productToFind: Pointer to the Product object to match against (input)
    // Returns: A changeItem object that matches the criteria.
    if (!file.is_open()) {
        throw runtime_error("File not open");
    }

    const int ITEMS_PER_PAGE = 5; // Number of items per page
    int count = 0;
    int page = 1;
    changeItem selectedItem;
    bool itemFound = false;

        // Define constants
    const int ITEMS_PER_PAGE = 5; // Number of items per page
    const int PAGE_WIDTH = 80;    // Width of the page (adjust as necessary)

    while (true) {
        file.seekg(0);
        count = 0;

        while (file.read(reinterpret_cast<char*>(&selectedItem), sizeof(changeItem))) {
            if (selectedItem.getAssociatedProduct().getProductID() == productToFind.getProductID()) {
                if (count % ITEMS_PER_PAGE == 0) {
                    if (count > 0) {
                        // Print page separator
                        cout << string(PAGE_WIDTH, '-') << endl;
                    }
                    // Print header
                    cout << "Change Items Report (Page " << (count / ITEMS_PER_PAGE + 1) << ")" << endl;
                    cout << "#";
                    cout << std::setw(12) << std::left << "ProductID";
                    cout << std::setw(12) << std::left << "ChangeID";
                    cout << std::setw(12) << std::left << "ReleaseID";
                    cout << std::setw(10) << std::left << "Status";
                    cout << "Description" << endl;
                    cout << "--";
                    cout << std::setw(12) << std::left << std::setfill('-') << "";
                    cout << std::setw(12) << std::left << std::setfill('-') << "";
                    cout << std::setw(12) << std::left << std::setfill('-') << "";
                    cout << std::setw(10) << std::left << std::setfill('-') << "";
                    cout << std::setfill('-') << "" << endl;
                }

                // Print item details
                cout << std::setw(2) << std::left << (count % ITEMS_PER_PAGE + 1);
                cout << std::setw(12) << std::left << selectedItem.getAssociatedProduct().getProductID();
                cout << std::setw(12) << std::left << selectedItem.getChangeItemID();
                cout << std::setw(12) << std::left << selectedItem.getAnticipatedRelease().getReleaseID();
                cout << std::setw(10) << std::left << selectedItem.getStatus();
                cout << selectedItem.getDescription() << endl;

                ++count;
                itemFound = true;
            }
        }

        if (itemFound) {
            // Prompt user to select an item or exit
            cout << "Enter the number of the change item to select (0 to exit): ";
            int itemNumber;
            cin >> itemNumber;

            if (itemNumber > 0 && itemNumber <= count) {
                file.seekg((itemNumber - 1) * sizeof(changeItem));
                file.read(reinterpret_cast<char*>(&selectedItem), sizeof(changeItem));
                return selectedItem;
            }
        } else {
            cout << "No matching change items found." << endl;
            return changeItem();
        }
    }
}
