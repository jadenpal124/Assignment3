// testFileOps.cpp
// Revision History:
// Rev. 2 - 22/07/28 Original by JAWS
//==================================================
// Description: This module is the testFileOps.cpp and runs the unit test.
//==================================================
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring> // for strcmp
#include <limits> // for std::cin.ignore()
#include "User.h"
#include "User.cpp"

using namespace std;
//==================================================

// Function prototypes for unit tests
//----------------------
void testUserClass();

int main() {
    cout << "Running unit tests for User class...\n";

    // Initialize user file for operations
    User userSession;
    userSession.initUser("usr.dat");

    // Call your unit tests here
    testUserClass();

    // Close user file after operations
    userSession.closeUser();

    cout << "All tests completed!\n";

    return 0;
}

// Unit tests for User class
//----------------------
void testUserClass() {
    // Description:
    //   test functionality of User class
    const char* fileName = "usr.dat";
    int passedTests = 0;
    int totalTests = 5; // Total number of tests

    cout << "Starting testUserOperations...\n";

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
    bool added = user1.addUser();
    assert(added);
    cout << "✔️" << endl;
    passedTests++;

    // Test 4: Retrieve user from file and verify data
    cout << "Test 4: Retrieving user from file and verifying data... ";
    try {
        User retrievedUser = User().checkUser("U000001");
        assert(strcmp(retrievedUser.getUserID(), "U000001") == 0);
        assert(strcmp(retrievedUser.getName(), "Alice Smith") == 0);
        assert(strcmp(retrievedUser.getPhone(), "9876543210") == 0);
        assert(strcmp(retrievedUser.getEmail(), "alice.smith@example.com") == 0);
        cout << "✔️" << endl;
        passedTests++;
    } catch (const exception& e) {
        cerr << "Exception occurred: " << e.what() << endl;
        cout << "❌" << endl;
        return;
    }

    // Test 5: Add two more users and verify the total count
    cout << "Test 5: Adding two more users and verifying count... ";
    User users[2] = {
        User("U000002", "Bob", "1111111111", "bob@example.com"),
        User("U000003", "Charlie", "2222222222", "charlie@example.com")
    };

    bool allAdded = true;
    for (int i = 0; i < 2; ++i) {
        if (!users[i].addUser()) {
            allAdded = false;
        }
    }
    if (!allAdded) {
        cout << "❌" << endl;
        return;
    }
    cout << "✔️" << endl;
    passedTests++;

    // Print test summary
    cout << "Test Summary:" << endl;
    cout << "-------------" << endl;
    cout << "Tests passed: " << passedTests << "/" << totalTests << endl;
    cout << "Tests failed: " << (totalTests - passedTests) << "/" << totalTests << endl;
    double passPercentage = (static_cast<double>(passedTests) / totalTests) * 100.0;
    cout << "Pass percentage: " << passPercentage << "%" << endl;
}