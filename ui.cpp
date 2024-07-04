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
                    handleUpdates(); // Placeholder for Updates functionality
                    break;
                case 3:
                    handleDisplay(); // Placeholder for Display functionality
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
                    cout << "Returning to Main Menu..." << endl;
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

    void handleUpdates() {
        cout << "Executing 'Updates' operation..." << endl;
        // Placeholder for Updates functionality
    }

    void handleDisplay() {
        cout << "Executing 'Display' operation..." << endl;
        // Placeholder for Display functionality
    }
};
