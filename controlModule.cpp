#include "controlModule.h"

// Program Startup
void initialize() { 

    userTmp.initUser(userFile);
    prodTmp.initProduct(productFile);
    relTmp.initRelease(releaseFile);
    chRTmp.initChReq(changeRequestFile);
    chItemTmp.initChangeItem(changeItemFile);
}

// Closing Program
void close() { 
    userTmp.closeUser();
    prodTmp.closeProduct();
    relTmp.closeRelease();
    chRTmp.closeChReq();
    chItemTmp.closeChangeItem();
}



// Implementation of addProductControl
void addProductControl() {
    const int NAME_MAX_LENGTH = 30;
    const int ID_MAX_LENGTH = 8;

    cout << "Enter the Product Name (1-29 Character Length): ";
    char prodName[NAME_MAX_LENGTH];
    cin.ignore();
    cin.getline(prodName, NAME_MAX_LENGTH);

    cout << "Enter the Product ID (1-7 Character Length): ";
    char prodID[ID_MAX_LENGTH];
    cin.getline(prodID, ID_MAX_LENGTH);

    cout << "Do you want to add product: " << prodName << " (select Y/N)? ";
    char input;
    cin >> input;
    if (input == 'Y' || input == 'y') {
        Product product(prodID, prodName);
        if (product.addProduct()) {
            cout << "Successfully Added. Returning to Add Menu" << endl;
        } else {
            cout << "Failed to add product. Returning to Add Menu" << endl;
        }
    } else {
        cout << "Product addition cancelled. Returning to Add Menu" << endl;
    }
}

// Implementation of addReleaseControl
void addReleaseControl() {
    Product temp; 
    const char* fileName = "releases.dat"; // Set the file name for the releases
    char relID[8];
    char choiceP, choiceR;

    // Display product from file and check if it's valid
    temp = temp.displayProductFromFile(); // Assuming this method loads the product from a file

    if (temp.getName() == nullptr) {
        cout << "Product not found. Exiting..." << endl;
        return;
    }

    cout << "Are you sure you want to add a Release to " << temp.getName() << " (select y/n): ";
    cin >> choiceP;
    cout << endl;

    // Validate choice
    if (choiceP != 'y' && choiceP != 'Y') {
        cout << "Operation cancelled. Returning to the menu." << endl;
        return;
    }

    cout << "Enter Release ID (1-8 character Length): "; 
    cin.ignore();
    cin.getline(relID, 8);

    // Validate Release ID length
    if (strlen(relID) == 0) {
        cout << "Release ID cannot be empty. Returning to the menu." << endl;
        return;
    }

    cout << "Do you want to add release " << relID << " (select y/n)? ";
    cin >> choiceR;
    cout << endl;

    if (choiceR != 'y' && choiceR != 'Y') {
        cout << "Operation cancelled. Returning to the menu." << endl;
        return;
    }

    // Create a Release object and set its details
    Release newRelease;
    newRelease.setReleaseID(relID);
    newRelease.setProduct(temp);

    // Optionally, set release date or other fields if needed
    char releaseDate[11];
    cout << "Enter Release Date (YYYY-MM-DD): ";
    cin.ignore();
    cin.getline(releaseDate, 11);
    newRelease.setReleaseDate(releaseDate);

    // Add the release to the file
    if (newRelease.addRelease()) {
        cout << "Release successfully added." << endl;
    } else {
        cout << "Failed to add release. Please check the file and try again." << endl;
    }
}

// Implementation of addChangeRequestControl
void addChangeRequestControl() {
    // Local variables for function 
    const char* userFile;
    const char* productFile;
    const char* changeItemFile;
    User tempUser;
    changeItem tempChangeItem;
    Release tempRelease;
    Product tempProd;
    char date[11];
    char description[30];
    char choice;

    // Select a User 
    tempUser = tempUser.displayUsersFromFile();
    cout << "Do you want to select User " << tempUser.getName() << " (Select Y/N) ";
    cin >> choice;
    cout << endl;
    if (choice != 'Y' || choice != 'y') { 
        tempUser.displayUsersFromFile();
    }

    // Choose a product for change request
    tempProd = tempProd.displayProductFromFile();

    cout << "Do you want to select product " << tempProd.getName() << " (Select Y/N)? ";
    cin >> choice;
    if (!choice == 'Y' || !choice == 'y') { 
        tempUser.displayUsersFromFile();
    }
    cout << endl;

    // Add a date of change Request
    cout << "Enter the date, format (YYYY/MM//DD) : ";
    cin.ignore();
    cin.getline(date, 11);
    cout << endl;
    cout << "Do you want to add the date " << date << " (Select Y/N)? ";
    cin >> choice;
    cout << endl;

    // Check change items for given product or add changeItem. 
    tempChangeItem = tempChangeItem.displayAndReturnChangeItem(tempProd);
    cout << "Do you want to add the changeItem " << tempChangeItem.getChangeItemID() << " (Select Y/N)? ";
    cin >> choice;
    if (!choice == 'Y' || !choice == 'y') { 
        tempUser.displayUsersFromFile();
    }
    cout << endl;

    // Confirm inputs then add create change request object with corresponding variables
    if (choice == 'Y' || choice == 'y') {
        // Assuming you have a ChangeRequest class and appropriate methods
        changeRequest changeRequest;
        changeRequest.setUser(tempUser);
        changeRequest.setAssociatedRelease(tempChangeItem.getAnticipatedRelease());
        changeRequest.setDateRequested(date);

        // Add Change Reqeust to file.
        if (changeRequest.addChangeRequest()) {
            cout << "Change request added successfully." << endl;
        } else {
            cout << "Failed to add change request." << endl;
        }
    } else {
        cout << "Change request not added." << endl;
    }
}

// Implementation of updateUserControl
void updateUserControl() {
    const int ID_MAX_LENGTH = 8;
    cout << "Enter the User ID to update: ";
    char userID[ID_MAX_LENGTH];
    cin.ignore();
    cin.getline(userID, ID_MAX_LENGTH);

    User user = User().checkUser(userID);

    cout << "Enter new Name (leave empty to keep current): ";
    char name[30];
    cin.getline(name, 30);
    if (strlen(name) > 0) user.setName(name);

    cout << "Enter new Phone (leave empty to keep current): ";
    char phone[15];
    cin.getline(phone, 15);
    if (strlen(phone) > 0) user.setPhone(phone);

    cout << "Enter new Email (leave empty to keep current): ";
    char email[30];
    cin.getline(email, 30);
    if (strlen(email) > 0) user.setEmail(email);

    if (user.changeUserInfo()) {
        cout << "Successfully Updated. Returning to Update Menu" << endl;
    } else {
        cout << "Failed to update user. Returning to Update Menu" << endl;
    }
}

// Implementation of updateChangeItemControl
void updateChangeItemControl() {
    const char* fileName;
    Product tempProduct;
    changeItem tempChangeItem;

    tempProduct = tempProduct.displayProductFromFile(); // Need to make product class open and initialize files once.
    tempChangeItem = tempChangeItem.displayAndReturnChangeItem(tempProduct);
    tempChangeItem.updateChangeItem(tempChangeItem);
}

// Implementation of displayRemReportControl
void displayRemReportControl() {
    const char* fileName;
    changeItem tempChangeItem;
    Product tempProduct;
    tempProduct = tempProduct.displayProductFromFile();
    tempChangeItem.displayRemainingReports(tempProduct);
}


// Implementation of displayNotifyReportControl
void displayNotifyReportControl() {
    // Prompt for product ID
    char productID[8];
    cout << "Enter Product ID: ";
    cin >> productID;

    // Create a Product object and check if it exists
    Product product;
    product.checkProductExists("products.bin");
    
    // If product doesn't exist, notify the user and exit
    if (strcmp(product.getProductID(), productID) != 0) {
        cerr << "Product not found." << endl;
        return;
    }

    // Prompt for release ID
    char releaseID[9];
    cout << "Enter Release ID: ";
    cin >> releaseID;

    // Create a Release object and check if it exists for the given product
    Release release;
    release.initRelease("releases.bin"); // Initialize release file
    if (!release.checkRelease(releaseID)) {
        cerr << "Release not found." << endl;
        release.closeRelease();
        return;
    }
    release.closeRelease(); // Close the file after checking

    // Open the file containing change requests
    ifstream inFile("changeRequests.bin", ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file for reading." << endl;
        return;
    }

    changeRequest req;

    // Display report header
    cout << "Users to be Notified Report for Product ID: " << productID << ", Release ID: " << releaseID << endl;
    cout << "Change ID | Requester Name | Requester Email" << endl;
    cout << "---------------------------------------------" << endl;

    // Read and process each change request record
    while (inFile.read(reinterpret_cast<char*>(&req), sizeof(changeRequest))) {
        // Check if the change item status is 'Done' and if it matches the selected product and release
        if (req.getChangeItem().getStatus() == changeItem::Status::Done &&
            strcmp(req.getAssociatedRelease().getProduct().getProductID(), productID) == 0 &&
            strcmp(req.getAssociatedRelease().getReleaseID(), releaseID) == 0) {
            // Assuming getChangeItem() provides a method getChangeID() to get the Change ID
            cout << req.getChangeItem().getChangeItemID() << " | "
                 << req.getUser().getName() << " | "
                 << req.getUser().getEmail() << endl;
        }
    }

    inFile.close(); // Close the file
}

// Implementation of getStatusControl
void getStatusControl() {
    Product productTemp;
    changeItem changeItemTemp;

    // Display product information and return selected product
    productTemp = productTemp.displayProductFromFile();

    // Display change items for the selected product and return selected change item
    changeItemTemp = changeItemTemp.displayAndReturnChangeItem(productTemp);

    // Output the details of the selected change item
    cout << "Change Item ID: " << changeItemTemp.getChangeItemID() << endl;
    cout << "Description: " << changeItemTemp.getDescription() << endl;
    cout << "Status: " << changeItemTemp.getStatus() << endl;
    cout << "Associated Product ID: " << changeItemTemp.getAssociatedProduct().getProductID() << endl;
    cout << "Associated Product Name: " << changeItemTemp.getAssociatedProduct().getName() << endl;
    cout << "Anticipated Release ID: " << changeItemTemp.getAnticipatedRelease().getReleaseID() << endl;
    cout << "Anticipated Release Date: " << changeItemTemp.getAnticipatedRelease().getReleaseDate() << endl;
}
