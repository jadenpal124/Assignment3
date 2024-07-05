// mainTest.cpp

#include <iostream>
#include "User.h" // Include the header file for User class

using namespace std;

// Function prototypes for unit tests
void testUserClass();

int main() {
    cout << "Running unit tests for User class...\n";

    // Call your unit tests here
    testUserClass();

    cout << "All tests passed!\n";

    return 0;
}

// Unit tests for User class
void testUserClass() {
    // Test case 1: Default constructor
    User user1;
    cout << "Test case 1: Default constructor\n";
    user1.displayUserInfo();

    // Test case 2: Parameterized constructor
    User user2("U1234567", "John Doe", "123-456-7890", "john.doe@example.com");
    cout << "\nTest case 2: Parameterized constructor\n";
    user2.displayUserInfo();

    // Test case 3: Getter and setter methods
    cout << "\nTest case 3: Getter and setter methods\n";
    const char* newUserID = "U7654321";
    const char* newName = "Jane Smith";
    const char* newPhone = "987-654-3210";
    const char* newEmail = "jane.smith@example.com";

    user2.setUserID(newUserID);
    user2.setName(newName);
    user2.setPhone(newPhone);
    user2.setEmail(newEmail);

    cout << "Updated user information:\n";
    user2.displayUserInfo();

    // Add more test cases as needed
}
