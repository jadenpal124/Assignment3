#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring> // for strcmp
#include <limits> // for std::cin.ignore()
#include "User.h"
#include "User.cpp"

using namespace std;

// Utility function to clear contents of a file
void clearFile(const char* fileName) {
    ofstream ofs(fileName, ofstream::out | ofstream::trunc);
    ofs.close();
}

// Function prototypes for unit tests
void testUserClass();

int main() {
    cout << "Running unit tests for User class...\n";

    // Call your unit tests here
    testUserClass();

    cout << "All tests completed!\n";

    return 0;
}

// Unit tests for User class
void testUserClass() {
    const char* fileName = "UT_users_list";
    int passedTests = 0;
    int totalTests = 6; // Total number of tests

    cout << "Starting testUserOperations...\n";

    // Clear contents of the file before starting tests
    clearFile(fileName);

    // Test 1: Create a user and verify getters
    cout << "Test 1: Creating user and verifying getters... ";
    User user1("U000001", "Alice", "1234567890", "alice@example.com");
    assert(strcmp(user1.getUserID(), "U000001") == 0);
    assert(strcmp(user1.getName(), "Alice") == 0);
    assert(strcmp(user1.getPhone(), "1234567890") == 0);
    assert(strcmp(user1.getEmail(), "alice@example.com") == 0);
    cout << "✔️" << endl;
    passedTests++;

    // Test 2: Modify user information using setters
    cout << "Test 2: Modifying user information... ";
    user1.setName("Alice Smith");
    user1.setPhone("9876543210");
    user1.setEmail("alice.smith@example.com");
    assert(strcmp(user1.getName(), "Alice Smith") == 0);
    assert(strcmp(user1.getPhone(), "9876543210") == 0);
    assert(strcmp(user1.getEmail(), "alice.smith@example.com") == 0);
    cout << "✔️" << endl;
    passedTests++;

    // Test 3: Add user to file and check if added correctly
    cout << "Test 3: Adding user to file... ";
    bool added = user1.addUser(fileName);
    assert(added);
    cout << "✔️" << endl;
    passedTests++;

    // Test 4: Retrieve user from file and verify data
    cout << "Test 4: Retrieving user from file and verifying data... ";
    try {
        User retrievedUser = User().checkUser(fileName, "U000001");
        assert(strcmp(retrievedUser.getUserID(), "U000001") == 0);
        assert(strcmp(retrievedUser.getName(), "Alice Smith") == 0);
        assert(strcmp(retrievedUser.getPhone(), "9876543210") == 0);
        assert(strcmp(retrievedUser.getEmail(), "alice.smith@example.com") == 0);
        cout << "✔️" << endl;
        passedTests++;
    } catch (const exception& e) {
        cerr << "Exception occurred: " << e.what() << endl;
        cout << "❌" << endl;
    }

    // Test 5: Display users from file and verify output
    cout << "Test 5: Displaying users from file and verifying output... " << endl << endl;
    try {
        User user1;
        user1.displayUsersFromFile(fileName);
        cout << "✔️" << endl << endl;
        passedTests++;
    } catch (const exception& e) {
        cerr << "Exception occurred: " << e.what() << endl;
        cout << "❌" << endl << endl;
    }

    // Test 6: Add more users and test displaying the 6th user
    cout << "Test 6: Adding more users and displaying the 6th user... " << endl << endl;
    // Add 6 users
    User user2("U000002", "Bob", "2345678901", "bob@example.com");
    user2.addUser(fileName);
    User user3("U000003", "Charlie", "3456789012", "charlie@example.com");
    user3.addUser(fileName);
    User user4("U000004", "David", "4567890123", "david@example.com");
    user4.addUser(fileName);
    User user5("U000005", "Eve", "5678901234", "eve@example.com");
    user5.addUser(fileName);
    User user6("U000006", "Frank", "6789012345", "frank@example.com");
    user6.addUser(fileName);

    // Display the 6th user
    try {
        User user1;
        user1.displayUsersFromFile(fileName);
        cout << "✔️" << endl << endl;
        passedTests++;
    } catch (const exception& e) {
        cerr << "Exception occurred: " << e.what() << endl;
        cout << "❌" << endl << endl;
    }

    // Clear contents of the file after tests
    clearFile(fileName);

    // Print test summary
    cout << "Test Summary:" << endl;
    cout << "-------------" << endl;
    cout << "Tests passed: " << passedTests << "/" << totalTests << endl;
    cout << "Tests failed: " << (totalTests - passedTests) << "/" << totalTests << endl;
    double passPercentage = (static_cast<double>(passedTests) / totalTests) * 100.0;
    cout << "Pass percentage: " << passPercentage << "%" << endl;
}
