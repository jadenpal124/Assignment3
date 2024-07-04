/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS */
//================================ 
/* This module is the implementation of the User class. 
   User class contains all the data about user and functions to access them. */
//================================ 
#ifndef USER_H
#define USER_H

#include <iostream>
#include <cstring> // For string manipulation functions
using namespace std;
//================================ 
class User {
public:
    // Constructors
    User(); // Default constructor
    User(const char* userID, const char* name, const char* phone, const char* email); // Parameterized constructor

    // Getter methods
    const char* getUserID() const;
    const char* getName() const;
    const char* getPhone() const;
    const char* getEmail() const;

    // Setter methods
    void setUserID(const char* userID);
    void setName(const char* name);
    void setPhone(const char* phone);
    void setEmail(const char* email);

    // Utility methods (if any)
    void displayUserInfo() const; // Example utility method to display user information

private:
    char userID[8];
    char name[30];
    char phone[12];
    char email[24];
};

#endif // USER_H
