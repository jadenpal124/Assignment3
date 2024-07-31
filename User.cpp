/* Revision History: 
   Rev. 1 - 04/15/24 Original by JAWS */
//==================================================
/* This module implements the User class, encapsulating user data and operations.

   Attributes include userID, name, phone, and email, each managed with specific getter 
   and setter methods for accessing and modifying user information. The class also provides 
   utility methods for displaying user info and managing user data in a file.

   Procedures are cohesive as they collectively manage and abstract user-related data 
   and operations, ensuring encapsulation and promoting reusability across modules. */
//==================================================

#include "User.h"

//==================================================
std::fstream User::fileStream;
//==================================================

// Default constructor
//----------------------
User::User () {
// Description: Default constructor initializing a User object with default values.
    memset(userID, 0, sizeof(userID));
    memset(name, 0, sizeof(name));
    memset(phone, 0, sizeof(phone));
    memset(email, 0, sizeof(email));
}

// Parameterized constructor
//----------------------
User::User (const char* userID, const char* name, const char* phone, const char* email) {
// Description: Parameterized constructor initializing userID, name, phone, and email with provided values.
// Parameters:
//   - userID: Pointer to a character array containing the user ID (input)
//   - name: Pointer to a character array containing the user name (input)
//   - phone: Pointer to a character array containing the user phone (input)
//   - email: Pointer to a character array containing the email (input)
    setUserID(userID);
    setName(name);
    setPhone(phone);
    setEmail(email);
}

// Getter methods
//----------------------
const char* User::getUserID () const {
// Description: Getter for retrieving user ID
// Parameters: None
// Returns: Pointer to a constant character array containing the user ID
    return userID;
}

//----------------------
const char* User::getName () const {
// Description: Getter for retrieving user name
// Parameters: None
// Returns: Pointer to a constant character array containing the user name
    return name;
}

//----------------------
const char* User::getPhone () const {
// Description: Getter for retrieving user phone number
// Parameters: None
// Returns: Pointer to a constant character array containing the user phone number
    return phone;
}

//----------------------
const char* User::getEmail () const {
// Description: Getter for retrieving user email address
// Parameters: None
// Returns: Pointer to a constant character array containing the user email address
    return email;
}

//----------------------
const char* User::getDepartment() const {
    return department;
}

// Setter methods
//----------------------
void User::setUserID (const char* userID) {
// Description: Setter for setting user ID
// Parameters:
//   - userID: Pointer to a character array containing the user ID (input)
    strncpy(this->userID, userID, sizeof(this->userID) - 1);
    this->userID[sizeof(this->userID) - 1] = '\0'; // Ensure null-termination
}

//----------------------
void User::setName (const char* name) {
// Description: Setter for setting user name
// Parameters:
//   - name: Pointer to a character array containing the user name (input)
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0'; // Ensure null-termination
}

//----------------------
void User::setPhone (const char* phone) {
// Description: Setter for setting user phone number
// Parameters:
//   - phone: Pointer to a character array containing the user phone (input)
    strncpy(this->phone, phone, sizeof(this->phone) - 1);
    this->phone[sizeof(this->phone) - 1] = '\0'; // Ensure null-termination
}

//----------------------
void User::setEmail (const char* email) {
// Description: Setter for setting user email address
// Parameters:
//   - email: Pointer to a character array containing the email (input)
    strncpy(this->email, email, sizeof(this->email) - 1);
    this->email[sizeof(this->email) - 1] = '\0'; // Ensure null-termination
}

//----------------------
void User::setDepartment(const char* dept) {
    strncpy(this->department, dept, sizeof(department) - 1);
    department[sizeof(department) - 1] = '\0'; // Ensure null-termination
}

// Utility methods
//----------------------
void User::initUser(const char* fileName) {
    // Description: Initializes the User object and opens the specified file for operations
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)

    // Attempt to open file for reading and writing in binary mode
    fileStream.open(fileName, ios::in | ios::out | ios::binary);

    if (!fileStream.is_open()) {
        // File does not exist or could not be opened for reading and writing
        fileStream.clear(); // Clear error state

        // Attempt to create a new file
        fileStream.open(fileName, ios::out | ios::binary | ios::trunc);
        if (!fileStream) {
            throw runtime_error("Error: Could not create file");
        }
        fileStream.close(); // Close the newly created file

        // Reopen file for reading and writing
        fileStream.open(fileName, ios::in | ios::out | ios::binary);
        if (!fileStream) {
            throw runtime_error("Error: Could not open file for reading and writing after creation attempt");
        }
    }
}

//----------------------
void User::closeUser () {
// Description: Closes the file and performs any necessary cleanup.
    // Close file stream
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

//----------------------
void User::displayUserInfo () const {
// Description: Displays user information from the currently managed file.
// Exception:
//   May throw an exception if the file cannot be accessed.
    // Check if file is open
    if (!fileStream.is_open()) {
        cerr << "Error: File is not open." << endl;
        return;
    }

    // Read user info from file
    User temp;
    fileStream.seekg(0, ios::beg);
    while (fileStream.read(reinterpret_cast<char*>(&temp), sizeof(User))) {
        cout << "User ID: " << temp.getUserID() << endl;
        cout << "Name: " << temp.getName() << endl;
        cout << "Phone: " << temp.getPhone() << endl;
        cout << "Email: " << temp.getEmail() << endl;
        cout << "Department: " << temp.getDepartment() << endl << endl;
    }
}

//----------------------
bool User::changeUserInfo () {
// Description: Updates the user's information such as name, phone, email, and department in the currently managed file.
// Returns:
//   true if the user information was successfully updated; false otherwise.
// Exception:
//   May throw an exception if the file cannot be accessed.
    // Check if file is open
    if (!fileStream.is_open()) {
        cerr << "Error: File is not open." << endl;
        return false;
    }

    bool found = false;
    User temp;

    // Move file pointer to the beginning of the file
    fileStream.clear(); // Clear any error flags
    fileStream.seekg(0, ios::beg);

    // Search for the user by userID and update information
    while (fileStream.read(reinterpret_cast<char*>(&temp), sizeof(User))) {
        if (strcmp(temp.getUserID(), userID) == 0) {
            // Update information
            strncpy(temp.name, name, sizeof(temp.name) - 1);
            strncpy(temp.phone, phone, sizeof(temp.phone) - 1);
            strncpy(temp.email, email, sizeof(temp.email) - 1);
            strncpy(temp.department, department, sizeof(temp.department) -1);

            // Write back to file
            fileStream.seekp(-static_cast<int>(sizeof(User)), ios::cur);
            fileStream.write(reinterpret_cast<const char*>(&temp), sizeof(User));
            found = true;
            break;
        }
    }

    return found;
}

 bool User::checkUserIDExists () {
// Description: Checks if a product with the given Product ID exists in a file.
// Parameters:
//   - productIDToFind: Pointer to a character array containing the Product ID to search for (input)
// Returns:
//   - Reference to the Product object if the product with the given Product ID exists in the file.
// Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.
    if (!fileStream.is_open()) {
        cerr << "File stream is not open." << endl;
        return false;
    }

    // Seek to the beginning of the file
    fileStream.seekg(0, ios::beg);
    
    User temp;
    while (fileStream.read(reinterpret_cast<char*>(&temp), sizeof(User))) {
        // Compare the user ID
        if (strcmp(temp.userID, this->userID) == 0) {
            return true;
        }
    }

    return false;
}

//----------------------
bool User::addUser() {
    // Description: Adds the user's details to the currently managed file.
    // Returns:
    //   - true if the user details were successfully added; false otherwise.
    // Exceptions: May throw an exception if the file cannot be accessed.

    fileStream.clear();
    // Check if file is open
    if (!fileStream.is_open()) {
        cerr << "Error: File is not open." << endl;
        return false;
    }

    // Move the write pointer to the end of the file
    fileStream.seekp(0, ios::end);
    if (fileStream.fail()) {
        cerr << "Error: Failed to move write pointer to the end of the file." << endl;
        return false;
    }

    // Write the User object to the file
    fileStream.write(reinterpret_cast<const char*>(this), sizeof(User));
    if (fileStream.fail()) {
        cerr << "Error: Failed to write to file." << endl;
        fileStream.clear();  // Clear the error state
        return false;
    }

    // Clear the file error state
    fileStream.flush();
    fileStream.clear();
    return true;
}


//----------------------
User User::displayUsersFromFile () const {
// Description: Displays users stored in the currently managed file in batches of 5, allowing scrolling.
//              User can press Enter to view the next 5 users or 'q' to stop.
//              Allows the user to select and returns that user.
// Exceptions:
//   May throw an exception if the file cannot be accessed.
// Check if file is open
    if (!fileStream.is_open()) {
        cerr << "Error: File is not open." << endl;
        return User(); // Return a default user in case of error
    }

    const int numRecordsPerPage = 5; // Number of records to display per page
    int startRecord = 0; // Starting record index

    bool displayNextPage = true;
    User selectedUser; // To store the selected user

    while (displayNextPage) {
        // Display header
        cout << " - Must Add or Select a User:" << endl;
        cout << "Request Status (Page " << (startRecord / numRecordsPerPage + 1) << ")" << endl;
        cout << setw(2) << "#" << "  ";
        cout << setw(10) << "User ID" << "  ";
        cout << setw(15) << "User Name" << "  ";
        cout << setw(15) << "Phone Number" << "  ";
        cout << setw(20) << "Email" << "  ";
        cout << setw(20) << "Department" << endl;
        cout << setw(2) << "--" << "  ";
        cout << setw(10) << "----------" << "  ";
        cout << setw(15) << "---------------" << "  ";
        cout << setw(15) << "---------------" << "  ";
        cout << setw(20) << "--------------------" << "  ";
        cout << setw(20) << "--------------------" << endl;

        // Display records
        bool endOfFile = false;
        int displayedCount = 0;
        fileStream.clear();
        fileStream.seekg(startRecord * sizeof(User), ios::beg);

        for (int i = 0; i < numRecordsPerPage; ++i) {
            User user;
            if (!fileStream.read(reinterpret_cast<char*>(&user), sizeof(User))) {
                endOfFile = true; // End of file
                break;
            }
            cout << setw(2) << startRecord + i + 1 << "  ";
            cout << setw(10) << user.getUserID() << "  ";
            cout << setw(15) << user.getName() << "  ";
            cout << setw(15) << user.getPhone() << "  ";
            cout << setw(20) << user.getEmail() << " ";
            cout << setw(20) << user.getDepartment() << endl;
            ++displayedCount;
        }

        // Prompt user for input
        if (!endOfFile) {
            cout << endl;
            cout << "Press <enter> to display the next " << numRecordsPerPage << " rows, or \"q\" to go back." << endl;
            cout << "If you would like to select a person type the number #." << endl;
            cout << "If a User ID is known type \"s\" to enter it." << endl;
            cout << "To add a new user type \"a\"." << endl;

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
            } else if (selection == "a") {
                // Add new user
                User newUser;
                string userID;
                bool validIDEntered = false;

                while (!validIDEntered) {
                    cout << "Enter User ID: ";
                    getline(cin, userID);

                    newUser.setUserID(userID.c_str());

                    if (newUser.checkUserIDExists()) {
                        validIDEntered = true;
                    } else {
                        cout << "User ID already exists. Please enter a different User ID." << endl;
                    }
                }

                cout << "Enter User Name: ";
                string userName;
                getline(cin, userName);
                newUser.setName(userName.c_str());

                cout << "Enter Phone Number: ";
                string phone;
                getline(cin, phone);
                newUser.setPhone(phone.c_str());

                cout << "Enter Email: ";
                string email;
                getline(cin, email);
                newUser.setEmail(email.c_str());

                cout << "Enter Department (leave empty if not internal): ";
                string department;
                getline(cin, department);
                newUser.setDepartment(department.c_str());

                if (newUser.addUser()) {
                    cout << "User added successfully." << endl;
                    selectedUser = newUser;
                    return selectedUser;
                } else {
                    cout << "Failed to add user." << endl;
                }
            } else if (selection == "s") {
                // Enter User ID action
                cout << "Enter User ID: ";
                string userID;
                getline(cin, userID);
                fileStream.clear();
                fileStream.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                User user;
                while (fileStream.read(reinterpret_cast<char*>(&user), sizeof(User))) {
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
                fileStream.clear();
                fileStream.seekg((selectedNumber - 1) * sizeof(User), ios::beg);
                User user;
                if (fileStream.read(reinterpret_cast<char*>(&user), sizeof(User))) {
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
            cout << "To add a new user type \"a\"." << endl;

            string selection;
            cout << "Enter Selection: ";
            getline(cin, selection);

            if (selection == "q") {
                displayNextPage = false; // Exit loop
                break;
            } else if (selection == "s") {
                // Enter User ID action
                cout << "Enter User ID: ";
                string userID;
                getline(cin, userID);
                fileStream.clear();
                fileStream.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                User user;
                while (fileStream.read(reinterpret_cast<char*>(&user), sizeof(User))) {
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
            } else if (selection == "a") {
                // Add new user
                User newUser;
                string userID;
                bool validIDEntered = false;
                while (!validIDEntered) {
                    cout << "Enter User ID: ";
                    getline(cin, userID);
                    
                    newUser.setUserID(userID.c_str());

                    if (newUser.checkUserIDExists()) {
                        validIDEntered = true;
                    } else {
                        cout << "User ID already exists. Please enter a different User ID." << endl;
                    }
                }

                cout << "Enter User Name: ";
                string userName;
                getline(cin, userName);
                newUser.setName(userName.c_str());

                cout << "Enter Phone Number: ";
                string phone;
                getline(cin, phone);
                newUser.setPhone(phone.c_str());

                cout << "Enter Email: ";
                string email;
                getline(cin, email);
                newUser.setEmail(email.c_str());

                cout << "Enter Department (leave empty if not internal): ";
                string department;
                getline(cin, department);
                newUser.setDepartment(department.c_str());

                if (newUser.addUser()) {
                    cout << "User added successfully." << endl;
                    selectedUser = newUser;
                    return selectedUser;
                } else {
                    cout << "Failed to add user." << endl;
                }
            } else if (isdigit(selection[0])) {
                // Select by number action
                int selectedNumber = stoi(selection);
                fileStream.clear();
                fileStream.seekg((selectedNumber - 1) * sizeof(User), ios::beg);
                User user;
                if (fileStream.read(reinterpret_cast<char*>(&user), sizeof(User))) {
                    cout << "User selected: " << user.getName() << endl;
                    selectedUser = user;
                    displayNextPage = false; // Exit loop if user is selected
                } else {
                    cout << "Invalid selection.\n\n";
                }
            } else {
                cout << "Invalid selection.\n\n" << endl;
            }
        }
    }

    return selectedUser; // Return the selected user
}















   