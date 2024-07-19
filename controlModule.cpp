#include "controlModule.h"

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
        if (product.addProduct("products.dat")) {
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
    temp = temp.displayProductFromFile(fileName); // Assuming this method loads the product from a file

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
    if (newRelease.addRelease(fileName)) {
        cout << "Release successfully added." << endl;
    } else {
        cout << "Failed to add release. Please check the file and try again." << endl;
    }
}

// Implementation of addChangeRequestControl
void addChangeRequestControl() {
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


    tempUser = tempUser.displayUsersFromFile(userFile);
    cout << "Do you want to select User " << tempUser.getName() << " (Select Y/N) ";
    cin >> choice;
    cout << endl;
    if (choice != 'Y' || choice != 'y') { 
        tempUser.displayUsersFromFile(userFile);
    }

    tempProd = tempProd.displayProductFromFile(productFile);

    cout << "Do you want to select product " << tempProd.getName() << " (Select Y/N)? ";
    cin >> choice;
    if (!choice == 'Y' || !choice == 'y') { 
        tempUser.displayUsersFromFile(userFile);
    }
    cout << endl;

    cout << "Enter the date, format (YYYY/MM//DD) : ";
    cin.ignore();
    cin.getline(date, 11);
    cout << endl;

    cout << "Do you want to add the date " << date << " (Select Y/N)? ";
    cin >> choice;
    cout << endl;

    tempChangeItem = tempChangeItem.displayAndReturnChangeItem(changeItemFile, tempProd);
    cout << "Do you want to add the changeItem " << tempChangeItem.getChangeItemID() << " (Select Y/N)? ";
    cin >> choice;

    if (!choice == 'Y' || !choice == 'y') { 
        tempUser.displayUsersFromFile(userFile);
    }
    cout << endl;

    if (choice == 'Y' || choice == 'y') {
        // Assuming you have a ChangeRequest class and appropriate methods
        changeRequest changeRequest;
        changeRequest.setUser(tempUser);
        changeRequest.setAssociatedRelease(tempChangeItem.getAnticipatedRelease());
        changeRequest.setDateRequested(date);

        // Add further logic for saving the change request or processing it
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

    User user = User().checkUser("users.dat", userID);

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

    if (user.changeUserInfo("users.dat")) {
        cout << "Successfully Updated. Returning to Update Menu" << endl;
    } else {
        cout << "Failed to update user. Returning to Update Menu" << endl;
    }
}

// Implementation of updateChangeItemControl
void updateChangeItemControl() {
    Product tempProduct;
    Product* tempProductPtr;
    changeItem tempChangeItem;

    tempProductPtr = &(tempProduct.displayProductFromFile(fileNameProduct));
    tempChangeItem = tempChangeItem.displayAndReturnChangeItem(fileNameChangeItem, tempProductPtr);
    tempChangeItem.updateChangeItem(fileNameChangeItem,tempChangeItem);
}

// Implementation of displayRemReportControl
void displayRemReportControl() {
  //TO BE IMPLEMENTED
}

// Implementation of displayNotifyReportControl
void displayNotifyReportControl() {
 //TO BE IMPLEMENTED
}

// Implementation of getStatusControl
void getStatusControl() {
  //TO BE IMPLEMENTED
}
