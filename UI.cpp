#include <iostream>
#include "ControlModule.h"
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
                     // displayAddMenu();
                    break;
                case 2:
                     // displayUpdatesMenu();
                    break;
                case 3:
                     // displayDisplayMenu();
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
                     // addProductControl();
                    break;
                case 2:
                     // addReleaseControl();
                    break;
                case 3:
                     // addChangeRequestControl();
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
                     // updateUserControl();
                    break;
                case 2:
                     // updateChangeItemControl();
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
                     // displayRemReportControl();
                    break;
                case 2:
                     // displayNotifyReportControl();
                    break;
                case 3:
                    getStatusControl();
                    break;
                case 0:
                     // cout << "Returning to Main Menu...\n" << endl;
                    break;
                default:
                     // cout << "Invalid selection. Please enter a valid option." << endl;
                    break;
            }
            
        } while (choice != 0);
    }
};
