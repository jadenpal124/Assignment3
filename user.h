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
    User(); 
    // Description: Default constructor initializing usertID ,name ,phone and email to empty strings.

    User(const char* userID, const char* name, const char* phone, const char* email); // Parameterized constructor
    // Description: Parameterized constructor initializing usertID ,name ,phone and email with provided values.
    // Parameters:
    //   - userID: Pointer to a character array containing the user ID (input)
    //   - name: Pointer to a character array containing the user name (input)
    //   - phone: Pointer to a character array containing the user phone (input)
    //   - email: Pointer to a character array containing the email (input)

    // Getter methods
    //----------------------
    const char* getUserID() const;   
    // Description: Retrieves the user ID

    //----------------------
    const char* getName() const;     
    // Description: Retrieves the user name

    //----------------------
    const char* getPhone() const;    
    // Description: Retrieves the user phone number

    //----------------------
    const char* getEmail() const;    
    // Description: Retrieves the user email address

    // Setter methods
    //----------------------
    void setUserID(const char* userID); 
    // Description: Sets the user ID
    // Parameters:
    //   - userID: Pointer to a character array containing the user ID (input)

    //----------------------
    void setName(const char* name);     
    // Description: Sets the user name
    // Parameters:
    //   - name: Pointer to a character array containing the user name (input)

    //----------------------
    void setPhone(const char* phone);   
    // Description: Sets the user phone number
    // Parameters:
    //   - phone: Pointer to a character array containing the user phone (input)

    //----------------------
    void setEmail(const char* email);   
    // Description: Sets the user email address
    // Parameters:
    //   - email: Pointer to a character array containing the email (input)

    // Utility methods (if any)
    //----------------------
    void displayUserInfo() const; 
    // Description: Example utility method to display user information, 

private:
    char userID[8]; // Member variable for storing user ID (max length: 8 characters)
    char name[30];  // Member variable for storing user name (max length: 30 characters)
    char phone[12]; // Member variable for storing user phone number (max length: 30 characters)
    char email[24]; // Member variable for storing user email address (max length: 30 characters)
};

#endif // USER_H
