// UI.cpp
/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS */
   Rev. 2 - 22/07/24 Original by JAWS */
//================================ 
/* This module implements the Product class, which encapsulates data related to a product.
   The class provides methods to access, modify, and manage product information,
   demonstrating the principles of abstraction and high cohesion by encapsulating
   related functionality within the Product class. */
//================================ 
#include <iostream>
#include "controlModule.h"
using namespace std;

//================================ 
class UIModule {
public:

    void run () {
        int choice;
        do {
             //----------------------
            displayMainMenu();
            // Description: display function to display Main Menu
            // Parameters: None (no parameters)
            //----------------------

            cout << "Enter Selection: ";
            cin >> choice;
            //----------------------
            
            switch (choice) {
                case 1:
                    //----------------------
                    displayAddMenu();
                    // Description: display function to display Add Menu
                    // Parameters: None (no parameters)
                    break;
                    //----------------------
                case 2:
                    //----------------------
                    displayUpdatesMenu();
                    // Description: display function to display Updates Menu
                    // Parameters: None (no parameters)
                    break;
                    //----------------------
                case 3:
                    //----------------------
                    displayDisplayMenu();
                    // Description: display function to display Display Menu
                    // Parameters: None (no parameters)
                    break;
                    //----------------------
                case 0:
                    //----------------------
                    cout << "Thank you for using the JAWS Issue Tracker program." << endl;
                    break;
                    //----------------------
                default:
                    //----------------------
                    cout << "Invalid selection. Please enter a valid option." << endl;
                    break;
                    //----------------------
            }
        } while (choice != 0);
    }

//================================ 
private:
    void displayMainMenu () {
        cout << "Main Menu:" << endl;
        cout << "1) Add" << endl;
        cout << "2) Updates" << endl;
        cout << "3) Display" << endl;
        cout << "0) Quit" << endl;
    }

    void displayAddMenu () {
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
                    //----------------------
                    addProductControl();
                    // Description: executes 'Add Product' operation.
                    // Parameters: None (no parameters)
                    break;
                    //----------------------
                case 2:
                    //----------------------
                    addReleaseControl();
                    // Description: executes 'Add Release' operation.
                    // Parameters: None (no parameters)
                    break;
                    //----------------------
                case 3:
                    //----------------------
                    addChangeRequestControl();
                    // Description: executes 'Add Product' operation.
                    // Parameters: None (no parameters)
                    break;
                    //----------------------
                case 0:
                    //----------------------
                    cout << "Returning to Main Menu...\n" << endl;
                    displayMainMenu();
                    // Description: return to the main menu.
                    // Parameters: None (no parameters)
                    break;
                    //----------------------
                default:
                    //----------------------
                    cout << "Invalid selection. Please enter a valid option." << endl;
                    break;
                    //----------------------
            }
        } while (choice != 0);
    }

    //================================ 
    void displayUpdatesMenu () {
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
                    updateUserControl();
                    // Description: executes 'Update User' operation.
                    // Parameters: None (no parameters)
                    break;
                case 2:
                    updateChangeItemControl();
                    // Description: executes 'Update Change Item' operation.
                    // Parameters: None (no parameters)
                    break;
                case 0:
                    cout << "Returning to Main Menu...\n" << endl;
                    displayMainMenu();
                    // Description: return to the main menu.
                    // Parameters: None (no parameters)
                    break;
                default:
                    cout << "Invalid selection. Please enter a valid option." << endl;
                    break;
            }
            
        } while (choice != 0);
    }

    //================================ 
    void displayDisplayMenu () {
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
                    //----------------------
                    displayRemReportControl();
                    // Description: executes 'Update User' operation.
                    // Parameters: None (no parameters)
                    break;
                    //----------------------
                case 2:
                    //----------------------
                    displayNotifyReportControl();
                    // Description: executes 'Update User' operation.
                    // Parameters: None (no parameters)
                    break;
                    //----------------------
                case 3:
                    //----------------------
                    getStatusControl();
                    // Description: executes 'Update User' operation.
                    // Parameters: None (no parameters)
                    break;
                    //----------------------
                case 0:
                    //----------------------
                    cout << "Returning to Main Menu...\n" << endl;
                    displayMainMenu();
                    // Description: return to the main menu.
                    // Parameters: None (no parameters)
                    break;
                    //----------------------
                default:
                    //----------------------
                     cout << "Invalid selection. Please enter a valid option." << endl;
                    break;
                    //----------------------
            }
        } while (choice != 0);
    }
    //================================ 
};
