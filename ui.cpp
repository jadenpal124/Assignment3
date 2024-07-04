#include <iostream>
using namespace std;

class UIModule {
public:
    void run() {
        int choice;

        do {
            displayMainMenu();

            cout << "Enter Selection: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayAddMenu();
                    break;
                case 2:
                    displayUpdatesMenu();
                    break;
                case 3:
                    displayDisplayMenu();
                    break;
                case 0:
                    cout << "Thank you for using the JAWS Issue Tracker program." << endl;
                    break;
                default:
                    cout << "Invalid selection. Please enter a valid option." << endl;
                    break;
            }
            
        } while (choice != 0);
    }

private:
    void displayMainMenu() {
        cout << "Main Menu:" << endl;
        cout << "1) Add" << endl;
        cout << "2) Updates" << endl;
        cout << "3) Display" << endl;
        cout << "0) Quit" << endl;
    }

    void displayAddMenu() {
        int choice;

        do {
            cout << "\nAdd Menu:" << endl;
            cout << "1) Add Product" << endl;
            cout << "2) Add Release" << endl;
            cout << "3) Add Change Request" << endl;
            cout << "0) Return to Main Menu" << endl;
            cout << "Enter Selection: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    handleAddProduct();
                    break;
                case 2:
                    handleAddRelease();
                    break;
                case 3:
                    handleAddChangeRequest();
                    break;
                case 0:
                    cout << "Returning to Main Menu...\n" << endl;
                    break;
                default:
                    cout << "Invalid selection. Please enter a valid option." << endl;
                    break;
            }
            
        } while (choice != 0);
    }

    void displayUpdatesMenu() {
        int choice;

        do {
            cout << "\nUpdates Menu:" << endl;
            cout << "1) Update User" << endl;
            cout << "2) Update Single Issue" << endl;
            cout << "0) Return to Main Menu" << endl;
            cout << "Enter Selection: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    handleUpdateUser();
                    break;
                case 2:
                    handleUpdateSingleIssue();
                    break;
                case 0:
                    cout << "Returning to Main Menu...\n" << endl;
                    break;
                default:
                    cout << "Invalid selection. Please enter a valid option." << endl;
                    break;
            }
            
        } while (choice != 0);
    }

    void displayDisplayMenu() {
        int choice;

        do {
            cout << "\nDisplay Menu:" << endl;
            cout << "1) Remaining Items to be Implemented Report" << endl;
            cout << "2) Users to be Notified Report" << endl;
            cout << "3) Status of Change Items" << endl;
            cout << "0) Return to Main Menu" << endl;
            cout << "Enter Selection: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    handleRemainingItemsReport();
                    break;
                case 2:
                    handleUsersToBeNotifiedReport();
                    break;
                case 3:
                    handleStatusOfChangeItems();
                    break;
                case 0:
                    cout << "Returning to Main Menu...\n" << endl;
                    break;
                default:
                    cout << "Invalid selection. Please enter a valid option." << endl;
                    break;
            }
            
        } while (choice != 0);
    }

    void handleAddProduct() {
        cout << "Executing 'Add Product' operation..." << endl;
        // Add your code for 'Add Product' operation here
    }

    void handleAddRelease() {
        cout << "Executing 'Add Release' operation..." << endl;
        // Add your code for 'Add Release' operation here
    }

    void handleAddChangeRequest() {
        cout << "Executing 'Add Change Request' operation..." << endl;
        // Add your code for 'Add Change Request' operation here
    }

    void handleUpdateUser() {
        cout << "Executing 'Update User' operation..." << endl;
        // Add your code for 'Update User' operation here
    }

    void handleUpdateSingleIssue() {
        cout << "Executing 'Update Single Issue' operation..." << endl;
        // Add your code for 'Update Single Issue' operation here
    }

    void handleRemainingItemsReport() {
        cout << "Executing 'Remaining Items to be Implemented Report' operation..." << endl;
        // Add your code for 'Remaining Items Report' operation here
    }

    void handleUsersToBeNotifiedReport() {
        cout << "Executing 'Users to be Notified Report' operation..." << endl;
        // Add your code for 'Users to be Notified Report' operation here
    }

    void handleStatusOfChangeItems() {
        cout << "Executing 'Status of Change Items' operation..." << endl;
        // Add your code for 'Status of Change Items' operation here
    }
};
