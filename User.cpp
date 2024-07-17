// user.cpp

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

void User::displayUsersFromFile(const char* fileName) const {
    ifstream inFile(fileName, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        return;
    }

    inFile.seekg(0, ios::end); // Move file pointer to end to get file size
    streampos fileSize = inFile.tellg();
    inFile.seekg(0, ios::beg); // Move file pointer back to beginning

    const int recordSize = sizeof(User);
    User user;
    int userCount = 0;
    char choice = ' ';

    while (inFile.read(reinterpret_cast<char*>(&user), recordSize)) {
        // Check if user is valid (assuming userID is not empty as a validity check)
        if (strlen(user.userID) == 0) {
            continue;
        }

        cout << "User ID: " << user.userID << endl;
        cout << "Name: " << user.name << endl;
        cout << "Phone: " << user.phone << endl;
        cout << "Email: " << user.email << endl << endl;

        ++userCount;

        // Check if we have reached end of file
        if (inFile.tellg() >= fileSize) {
            cout << "End of file reached." << endl;
            break;
        }

        if (userCount % 5 == 0) {
            cout << "Press Enter to view next user or 'q' to stop: " << endl;
            cin.get(choice);
            if (choice == 'q') {
                break; // Exit loop if user chooses to stop
            }
        }
    }

    inFile.close();
}

   