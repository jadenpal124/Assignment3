/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS /
//==================================================
/ This module defines functions for handling various operations related to adding products, release's, and change requests,
   user updates, change requests, and reports within the system. */
//==================================================

#include "controlModule.h"

//==================================================
User userTmp;
Product prodTmp;
Release relTmp;
changeRequest chRTmp;
changeItem chItemTmp;

const char* changeItemFile = "changeItems.dat";
const char* productFile = "products.dat";
const char* releaseFile = "releases.dat";
const char* userFile = "users.dat";
const char* changeRequestFile = "changeRequests.dat";
//==================================================

// Program Startup
//----------------------
void initialize () { 
// Description: 
//   Initialize files
    userTmp.initUser(userFile);
    prodTmp.initProduct(productFile);
    relTmp.initRelease(releaseFile);
    chRTmp.initChReq(changeRequestFile);
    chItemTmp.initChangeItem(changeItemFile);
}

// Closing Program
//----------------------
void close () { 
// Description: 
//   Closes All files
    userTmp.closeUser();
    prodTmp.closeProduct();
    relTmp.closeRelease();
    chRTmp.closeChReq();
    chItemTmp.closeChangeItem();
}



// Implementation of addProductControl
//----------------------
void addProductControl() {
    // Description:
    //   Executes 'Add Product' operation.

    const int NAME_MAX_LENGTH = 30;
    const int ID_MAX_LENGTH = 8;

    // Get product name from user
    cout << "Enter the Product Name (1-29 Characters): ";
    char prodName[NAME_MAX_LENGTH];
    cin.ignore();  // Clear any remaining newline character in the buffer
    cin.getline(prodName, NAME_MAX_LENGTH);

    // Get product ID from user
    cout << "Enter the Product ID (1-7 Characters): ";
    char prodID[ID_MAX_LENGTH];
    cin.getline(prodID, ID_MAX_LENGTH);

    // Check if inputs are valid
    if (strlen(prodName) == 0 || strlen(prodID) == 0) {
        cout << "Invalid input. Product name and ID cannot be empty." << endl;
        return;
    }

    if (strlen(prodName) >= NAME_MAX_LENGTH || strlen(prodID) >= ID_MAX_LENGTH) {
        cout << "Input exceeds maximum length. Returning to Add Menu." << endl;
        return;
    }

    // Confirm addition with the user
    cout << "Do you want to add product: " << prodName << " (select Y/N)? ";
    char input;
    cin >> input;
    cin.ignore();  // Clear the input buffer

    if (input == 'Y' || input == 'y') {
        Product product(prodID, prodName);

        // Attempt to add the product
        if (product.addProduct()) {
            cout << "Successfully Added. Returning to Add Menu." << endl;
        } else {
            cout << "Failed to add product. Returning to Add Menu." << endl;
        }
    } else {
        cout << "Product addition cancelled. Returning to Add Menu." << endl;
    }
}

// Implementation of addReleaseControl
//----------------------
void addReleaseControl () {
// Description:
//   Executes 'Add Release' operation.
    Product temp;
    char relID[8];
    char choiceP, choiceR;

    cin.ignore();

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
    char releaseDate[12];
    cout << "Enter Release Date (YYYY-MM-DD): ";
    cin.ignore();
    cin.getline(releaseDate, 12);
    newRelease.setReleaseDate(releaseDate);

    // Add the release to the file
    if (newRelease.addRelease()) {
        cout << "Release successfully added." << endl;
    } else {
        cout << "Failed to add release. Please check the file and try again." << endl;
    }
}

// Implementation of addChangeRequestControl
//----------------------
void addChangeRequestControl() {
    // Description:
    //   Executes 'Add Change Request' operation.

    // Local variables for function.
    User tempUser;
    changeItem tempChangeItem;
    Release tempRelease;
    Product tempProd;
    char date[12]; // 10 characters + 1 for null terminator
    char choice;

    while (true) {
        cin.ignore(); // Clear input buffer before getting new input
        cout << "\nChange Request\n";

        // Select a User
        while (true) {
            tempUser = tempUser.displayUsersFromFile();
            // Check if no valid user was found
            if (strlen(tempUser.getUserID()) == 0) {
                cout << "No valid user found. Please try again or type 'q' to quit.\n";
                cout << "Press <enter> to display more users or type 'q' to quit.\n";
                cin.get(choice); // Read user input
                cin.ignore(); // Clear newline character from input buffer

                if (choice == 'q' || choice == 'Q') {
                    cout << "Returning to main menu.\n";
                    return; // Exit function to return to the main menu
                }
                continue; // Continue to display more users
            }

            // Prompt for user confirmation
            cout << "Do you want to select User " << tempUser.getName() << " (Y/N)? ";
            cin >> choice;
            cin.ignore(); // Clear newline character from input buffer

            if (choice == 'Y' || choice == 'y') {
                break; // Exit loop if user confirms selection
            } else if (choice == 'q' || choice == 'Q') {
                cout << "Returning to main menu.\n";
                return; // Exit function to return to the main menu
            } else {
                cout << "Invalid choice. Please select 'Y' to confirm, 'N' to reject, or 'q' to quit.\n";
            }
        }

        // Choose a product for change request
        while (true) {
            tempProd = tempProd.displayProductFromFile();
            // Check if no valid product was found
            if (strlen(tempProd.getProductID()) == 0) {
                cout << "No valid product found. Please try again or type 'q' to quit.\n";
                cout << "Press <enter> to display more products or type 'q' to quit.\n";
                cin.get(choice); // Read user input
                cin.ignore(); // Clear newline character from input buffer

                if (choice == 'q' || choice == 'Q') {
                    cout << "Returning to main menu.\n";
                    return; // Exit function to return to the main menu
                }
                continue; // Continue to display more products
            }

            // Prompt for product confirmation
            cout << "Do you want to select product " << tempProd.getName() << " (Y/N)? ";
            cin >> choice;
            cin.ignore(); // Clear newline character from input buffer

            if (choice == 'Y' || choice == 'y') {
                break; // Exit loop if user confirms selection
            } else if (choice == 'q' || choice == 'Q') {
                cout << "Returning to main menu.\n";
                return; // Exit function to return to the main menu
            } else {
                cout << "Invalid choice. Please select 'Y' to confirm, 'N' to reject, or 'q' to quit.\n";
            }
        }

        // Choose a release of product for changeRequest
        while (true) {
            tempRelease = tempRelease.findReleaseAndReturn(tempProd);


            // Check if no valid product was found
            if (strlen(tempRelease.getReleaseDate()) == 0) {
                cout << "No valid release found. Please try again or type 'q' to quit.\n";
                cout << "Press <enter> to display more products or type 'q' to quit.\n";
                cin.get(choice); // Read user input
                cin.ignore(); // Clear newline character from input buffer

                if (choice == 'q' || choice == 'Q') {
                    cout << "Returning to main menu.\n";
                    return; // Exit function to return to the main menu
                }
                continue; // Continue to display more products
            }

            // Prompt for product confirmation
            cout << "Do you want to select release " << tempRelease.getReleaseID() << " (Y/N)? ";
            cin >> choice;
            cin.ignore(); // Clear newline character from input buffer

            if (choice == 'Y' || choice == 'y') {
                break; // Exit loop if user confirms selection
            } else if (choice == 'q' || choice == 'Q') {
                cout << "Returning to main menu.\n";
                return; // Exit function to return to the main menu
            } else {
                cout << "Invalid choice. Please select 'Y' to confirm, 'N' to reject, or 'q' to quit.\n";
            }
        }

        // Add a date of change request
        while (true) {
            cout << "Enter the date, format (YYYY/MM/DD): ";
            cin.getline(date, sizeof(date)); // Read date with size limit

            cout << "Do you want to add the date " << date << " (Y/N)? ";
            cin >> choice;
            cin.ignore(); // Clear newline character from input buffer

            if (choice == 'Y' || choice == 'y') {
                break; // Exit loop if user confirms date
            } else if (choice == 'q' || choice == 'Q') {
                cout << "Returning to main menu.\n";
                return; // Exit function to return to the main menu
            } else {
                cout << "Invalid choice. Please select 'Y' to confirm or 'q' to quit.\n";
            }
        }



        // Check change items for the given product or add changeItem
        while (true) {
            tempChangeItem = tempChangeItem.displayAndReturnChangeItem(tempProd, tempRelease);

            // Check if no valid change item was found
            if (tempChangeItem.getChangeItemID() == 0) {
                cout << "No valid change item found. Please try again or type 'q' to quit.\n";
                cout << "Press <enter> to display more change items or type 'q' to quit.\n";
                cin.get(choice); // Read user input
                cin.ignore(); // Clear newline character from input buffer

                if (choice == 'q' || choice == 'Q') {
                    cout << "Returning to main menu.\n";
                    return; // Exit function to return to the main menu
                }
                continue; // Continue to display more change items
            }

            // Prompt for change item confirmation
            cout << "Do you want to add the change item " << tempChangeItem.getChangeItemID() << " (Y/N)? ";
            cin >> choice;
            tempChangeItem.setAnticipatedRelease(tempRelease);

            cin.ignore(); // Clear newline character from input buffer

            if (choice == 'Y' || choice == 'y') {
                break; // Exit loop if user confirms selection
            } else if (choice == 'q' || choice == 'Q') {
                cout << "Returning to main menu.\n";
                return; // Exit function to return to the main menu
            } else {
                cout << "Invalid choice. Please select 'Y' to confirm, 'N' to reject, or 'q' to quit.\n";
            }
        }

        // Confirm inputs and create change request object with corresponding variables
        if (choice == 'Y' || choice == 'y') {
            // Assuming you have a ChangeRequest class and appropriate methods
            changeRequest cr;
            cr.setChangeItem(tempChangeItem);
            cr.setUser(tempUser);
            cr.setAssociatedRelease(tempChangeItem.getAnticipatedRelease());
            cr.setDateRequested(date);

            // Add Change Request to file.
            if (cr.addChangeRequest()) {
                cout << "Change request added successfully." << endl;
                return; // Exit function after successful addition
            } else {
                cout << "Failed to add change request." << endl;
            }
        } else {
            cout << "Change request not added." << endl;
            return; // Exit function if change request is not added
        }
    }
}


// Implementation of updateUserControl
//----------------------
void updateUserControl() {
    // Description:
    //   Executes 'Update User' operation.
    cin.ignore();

    cout << "\nUpdate User";

    User user;
    changeRequest req;
    
    user = user.displayUsersFromFile();

    // Check if the returned user is valid
    if (strlen(user.getUserID()) == 0) { // Assuming empty userID indicates an invalid user
        cout << "\n\nNo valid user selected. Returning to Update Menu" << endl;
        return; // Exit the function if no valid user is selected
    }

    cout << "Enter new Name (leave empty to keep current: ";
    char name[30];
    cin.getline(name, 30);
    if (strlen(name) > 0) user.setName(name);

    cout << "Enter new Phone (leave empty to keep current): ";
    char phone[15];
    cin.getline(phone, 12);
    if (strlen(phone) > 0) user.setPhone(phone);

    cout << "Enter new Email (leave empty to keep current): ";
    char email[24];
    cin.getline(email, 24);
    if (strlen(email) > 0) user.setEmail(email);

    if (user.changeUserInfo() && req.updateUser(user)) {
        cout << "Successfully Updated. Returning to Update Menu" << endl;

    } else {
        cout << "Failed to update user. Returning to Update Menu" << endl;
    }
}

// Implementation of updateChangeItemControl
//----------------------
void updateChangeItemControl() {
    // Description:
    //   Executes 'Update Single Issue' operation.
    
    cout << endl;
    cin.ignore();

    // Display and select the product
    Product tempProduct;
    tempProduct = tempProduct.displayProductFromFile(); // Ensure this initializes the product file
    
    cout << endl;
    
    // Display and select the change item to be updated
    changeItem tempChangeItem;
    tempChangeItem = tempChangeItem.displayAndReturnChangeItemStatus(tempProduct); // Get the change item for update

    if (tempChangeItem.getChangeItemID() == 0) {
        cout << "No valid change item selected. Returning to Update Menu" << endl;
        return;
    }

    // Perform the update
    if (tempChangeItem.updateChangeItem(tempChangeItem)) {
        cout << "Succefully updated Changeitem " << endl;
    } else {
        cout << "Failed to update change item." << endl;
    }
}

// Implementation of displayRemReportControl
//----------------------
void displayRemReportControl () {
// Description:
//   Executes ' Displays list Remaining Items Report' operation.
    const char* fileName;
    changeItem tempChangeItem;
    Product tempProduct;
    cin.ignore();
    tempProduct = tempProduct.displayProductFromFile();

    tempChangeItem.displayRemainingReports(tempProduct);
}


// Implementation of displayNotifyReportControl
//----------------------
void displayNotifyReportControl () {
// Description:
//   Executes ' Displays Users to be Notified Report' operation.
    // Prompt for product ID
    Product tmpProduct;

    cin.ignore();

    tmpProduct = tmpProduct.displayProductFromFile();
    
    // If product doesn't exist, notify the user and exit
    if (strlen(tmpProduct.getProductID()) == 0) {
        cerr << "Product not found." << endl;
        return;
    }

    changeRequest req;

    req.displayUsersToBeNotified(tmpProduct);
}

// Implementation of getStatusControl
//----------------------
void getStatusControl () {
// Description:
//   Executes ' Displays list of Status of Change Items' operation.
    Product productTemp;
    changeItem changeItemTemp;

    cin.ignore();

    // Display product information and return selected product
    productTemp = productTemp.displayProductFromFile();

    // Display change items for the selected product and return selected change item
    changeItemTemp = changeItemTemp.displayAndReturnChangeItemStatus(productTemp);

    // if empty return to main menu
   if (strlen(changeItemTemp.getAssociatedProduct().getProductID()) == 0) { 
        cout << "Returning to Menu " << endl;
        return;
   }

    // Output the details of the selected change item
    cout << "Change Item ID: " << changeItemTemp.getChangeItemID() << endl;
    cout << "Description: " << changeItemTemp.getDescription() << endl;
    cout << "Status: " << changeItemTemp.getStatusAsString() << endl;
    cout << "Associated Product ID: " << changeItemTemp.getAssociatedProduct().getProductID() << endl;
    cout << "Associated Product Name: " << changeItemTemp.getAssociatedProduct().getName() << endl;
    cout << "Anticipated Release ID: " << changeItemTemp.getAnticipatedRelease().getReleaseID() << endl;
    cout << "Anticipated Release Date: " << changeItemTemp.getAnticipatedRelease().getReleaseDate() << endl << endl;
}
