#include "User.h"
#include <iostream>
#include <fstream>
#include <iomanip> // for std::setw
#include <cstdlib> // for std::exit

using namespace std;

// Default constructor
User::User() {
    initUser(); // Initialize object upon startup
}

// Parameterized constructor
User::User(const char* userID, const char* name, const char* phone, const char* email) {
    initUser(); // Initialize object upon startup
    setUserID(userID);
    setName(name);
    setPhone(phone);
    setEmail(email);
}

// Getter methods
const char* User::getUserID() const {
    return userID;
}

const char* User::getName() const {
    return name;
}

const char* User::getPhone() const {
    return phone;
}

const char* User::getEmail() const {
    return email;
}

// Setter methods
void User::setUserID(const char* userID) {
    strncpy(this->userID, userID, sizeof(this->userID) - 1);
    this->userID[sizeof(this->userID) - 1] = '\0'; // Ensure null-termination
}

void User::setName(const char* name) {
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0'; // Ensure null-termination
}

void User::setPhone(const char* phone) {
    strncpy(this->phone, phone, sizeof(this->phone) - 1);
    this->phone[sizeof(this->phone) - 1] = '\0'; // Ensure null-termination
}

void User::setEmail(const char* email) {
    strncpy(this->email, email, sizeof(this->email) - 1);
    this->email[sizeof(this->email) - 1] = '\0'; // Ensure null-termination
}

// Utility methods
void User::displayUserInfo(const char* fileName) const {
    ifstream inFile(fileName, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw exception(); // Throwing exception if file cannot be opened
    }

    // Read user info from file
    while (inFile.read(reinterpret_cast<char*>(const_cast<User*>(this)), sizeof(User))) {
        cout << "User ID: " << userID << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl << endl;
    }

    inFile.close();
}

bool User::changeUserInfo(const char* fileName) {
    fstream file(fileName, ios::in | ios::out | ios::binary);
    if (!file) {
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    bool found = false;
    User temp;

    // Search for the user by userID and update information
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(User))) {
        if (strcmp(temp.userID, userID) == 0) {
            // Update information
            strncpy(temp.name, name, sizeof(temp.name) - 1);
            strncpy(temp.phone, phone, sizeof(temp.phone) - 1);
            strncpy(temp.email, email, sizeof(temp.email) - 1);

            // Write back to file
            file.seekp(-static_cast<int>(sizeof(User)), ios::cur);
            file.write(reinterpret_cast<const char*>(&temp), sizeof(User));
            found = true;
            break;
        }
    }

    file.close();
    return found;
}

User& User::checkUser(const char* fileName, const char* userID) {
    ifstream inFile(fileName, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw exception(); // Throwing exception if file cannot be opened
    }

    static User user; // Static to ensure it persists after function ends
    bool found = false;

    // Search for the user by userID
    while (inFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        if (strcmp(user.userID, userID) == 0) {
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) {
        cerr << "Error: User with ID " << userID << " not found." << endl;
        throw exception(); // Throwing exception if user not found
    }

    return user;
}

bool User::addUser(const char* fileName) {
    ofstream outFile(fileName, ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    // Write user information to file
    outFile.write(reinterpret_cast<const char*>(this), sizeof(User));
    outFile.close();
    return true;
}

void User::initUser() {
    // Initialize object upon startup
    memset(userID, 0, sizeof(userID));
    memset(name, 0, sizeof(name));
    memset(phone, 0, sizeof(phone));
    memset(email, 0, sizeof(email));
}

void User::closeUser() {
    // Delete the Object and frees any memory allocated on the heap.
    // This class does not use heap memory, so nothing to do here.
}

User User::displayUsersFromFile(const char* fileName) const {
    ifstream inFile(fileName, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        return User(); // Return a default user in case of error
    }

    const int numRecordsPerPage = 5; // Number of records to display per page
    int startRecord = 0; // Starting record index

    bool displayNextPage = true;
    User selectedUser; // To store the selected user

    while (displayNextPage) {
        // Display header
        cout << "Change Request - Must Add or Select a User:" << endl;
        cout << "Request Status (Page " << (startRecord / numRecordsPerPage + 1) << ")" << endl;
        cout << setw(2) << "#" << "  ";
        cout << setw(10) << "User ID" << "  ";
        cout << setw(15) << "User Name" << "  ";
        cout << setw(15) << "Phone Number" << "  ";
        cout << setw(20) << "Email" << endl;
        cout << setw(2) << "--" << "  ";
        cout << setw(10) << "----------" << "  ";
        cout << setw(15) << "---------------" << "  ";
        cout << setw(15) << "---------------" << "  ";
        cout << setw(20) << "--------------------" << endl;

        // Display records
        bool endOfFile = false;
        int displayedCount = 0;
        inFile.clear();
        inFile.seekg(startRecord * sizeof(User), ios::beg);

        for (int i = 0; i < numRecordsPerPage; ++i) {
            User user;
            if (!inFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
                endOfFile = true; // End of file
                break;
            }
            cout << setw(2) << startRecord + i + 1 << "  ";
            cout << setw(10) << user.getUserID() << "  ";
            cout << setw(15) << user.getName() << "  ";
            cout << setw(15) << user.getPhone() << "  ";
            cout << setw(20) << user.getEmail() << endl;
            ++displayedCount;
        }

        // Prompt user for input
        if (!endOfFile) {
            cout << endl;
            cout << "Press <enter> to display the next " << numRecordsPerPage << " rows, or \"q\" to go back." << endl;
            cout << "If you would like to select a person type the number #." << endl;
            cout << "If a User ID is known type \"s\" to enter it." << endl;

            string selection;
            cout << "Enter Selection: ";
            getline(cin, selection);

            // Handle user input
            if (selection.empty()) {
                // Default action: Display next page
                startRecord += numRecordsPerPage;
            } else if (selection == "q") {
                // Quit action
                displayNextPage = false; // Exit loop
            } else if (selection == "s") {
                // Enter User ID action
                cout << "Enter User ID: ";
                string userID;
                getline(cin, userID);
                inFile.clear();
                inFile.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                User user;
                while (inFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
                    if (strcmp(user.getUserID(), userID.c_str()) == 0) {
                        cout << "User found: " << user.getName() << endl;
                        selectedUser = user;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "User ID not found." << endl;
                } else {
                    displayNextPage = false; // Exit loop if user is found
                }
            } else if (isdigit(selection[0])) {
                // Select by number action
                int selectedNumber = stoi(selection);
                inFile.clear();
                inFile.seekg((selectedNumber - 1) * sizeof(User), ios::beg);
                User user;
                if (inFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
                    cout << "User selected: " << user.getName() << endl;
                    selectedUser = user;
                    cout << endl;
                    displayNextPage = false; // Exit loop if user is selected
                } else {
                    cout << "Invalid selection." << endl;
                }
            } else {
                cout << "Invalid selection." << endl;
            }
        } else {
            // End of file reached
            cout << "End of file reached. Press q to go back" << endl;
            cout << "If you would like to select a person type the number #." << endl;
            cout << "If a User ID is known type \"s\" to enter it." << endl;

            string selection;
            cout << "Enter Selection: ";
            getline(cin, selection);

            if (selection == "q") {
                displayNextPage = false; // Exit loop
            } else if (selection == "s") {
                // Enter User ID action
                cout << "Enter User ID: ";
                string userID;
                getline(cin, userID);
                inFile.clear();
                inFile.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                User user;
                while (inFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
                    if (strcmp(user.getUserID(), userID.c_str()) == 0) {
                        cout << "User found: " << user.getName() << endl;
                        selectedUser = user;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "User ID not found." << endl;
                } else {
                    displayNextPage = false; // Exit loop if user is found
                }
            } else if (isdigit(selection[0])) {
                // Select by number action
                int selectedNumber = stoi(selection);
                inFile.clear();
                inFile.seekg((selectedNumber - 1) * sizeof(User), ios::beg);
                User user;
                if (inFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
                    cout << "User selected: " << user.getName() << endl;
                    selectedUser = user;
                    displayNextPage = false; // Exit loop if user is selected
                } else {
                    cout << "Invalid selection." << endl;
                }
            } else {
                cout << "Invalid selection." << endl;
            }
        }
    }

    inFile.close();
    return selectedUser; // Return the selected user
}















   