/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS */
//==================================================
/* This module implements the User class, encapsulating user data and operations.

   Attributes include userID, name, phone, and email, each managed with specific getter 
   and setter methods for accessing and modifying user information. The class also provides 
   utility methods for displaying user info and managing user data in a file.

   Procedures are cohesive as they collectively manage and abstract user-related data 
   and operations, ensuring encapsulation and promoting reusability across modules. */
//==================================================
#ifndef USER_H
#define USER_H

#include <iostream>
#include <cstring> // For string manipulation functions
using namespace std;
//==================================================
class User {
public:
    // Constructors
    User(); // Default constructor

    User(const char* userID, const char* name, const char* phone, const char* email); 
    // Description: Parameterized constructor initializing userID, name, phone, and email with provided values.
    // Parameters:
    //   - userID: Pointer to a character array containing the user ID (input)
    //   - name: Pointer to a character array containing the user name (input)
    //   - phone: Pointer to a character array containing the user phone (input)
    //   - email: Pointer to a character array containing the email (input)

    // Getter methods
    //----------------------
    const char* getUserID() const;   
    // Description: Getter for retrieving user ID
    // Parameters: None
    // Returns: Pointer to a constant character array containing the user ID

    //----------------------
    const char* getName() const;     
    // Description: Getter for retrieving user name
    // Parameters: None
    // Returns: Pointer to a constant character array containing the user name

    //----------------------
    const char* getPhone() const;    
    // Description: Getter for retrieving user phone number
    // Parameters: None
    // Returns: Pointer to a constant character array containing the user phone number

    //----------------------
    const char* getEmail() const;    
    // Description: Getter for retrieving user email address
    // Parameters: None
    // Returns: Pointer to a constant character array containing the user email address

    // Setter methods
    //----------------------
    void setUserID(const char* userID); 
    // Description: Setter for setting user ID
    // Parameters:
    //   - userID: Pointer to a character array containing the user ID (input)

    //----------------------
    void setName(const char* name);     
    // Description: Setter for setting user name
    // Parameters:
    //   - name: Pointer to a character array containing the user name (input)

    //----------------------
    void setPhone(const char* phone);   
    // Description: Setter for setting user phone number
    // Parameters:
    //   - phone: Pointer to a character array containing the user phone (input)

    //----------------------
    void setEmail(const char* email);   
    // Description: Setter for setting user email address
    // Parameters:
    //   - email: Pointer to a character array containing the email (input)

    // Utility methods
    //----------------------
    void displayUserInfo(const char* fileName) const;
    // Description: Displays user information from the specified file.
    // Parameters: 
    //   - fileName: Pointer to a character array containing the file name where user information is stored (input).
    // Exception:
    //   May throw an exception if the specified file (fileName) does not exist or cannot be accessed.

    //----------------------
    bool changeUserInfo(const char* fileName);
    // Description: Updates the user's information such as name, phone, email, and department in the specified file.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name where user information is stored (input).
    // Returns:
    //   true if the user information was successfully updated in the file; false otherwise.
    // Exception:
    //   May throw an exception if the specified file (fileName) does not exist or cannot be accessed.

    //----------------------
    User& checkUser(const char* fileName, const char* userID);
    // Description: Searches the specified file for a user based on the provided userID 
    //              and returns a reference to the found User object if the user exists.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input).
    //   - userID: Pointer to a character array containing the user ID to search for (input).
    // Returns:
    //   Reference to a User object representing the user with the given userID.
    // Exceptions:
    //   May throw an exception if the file specified by fileName does not exist.

    //----------------------
    bool addUser(const char* fileName);
    // Description: Adds the user's details to the specified file.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input).
    // Returns:
    //   true if the user details were successfully added to the file; false otherwise.
    // Exceptions:
    //   May throw an exception if the file specified by fileName does not exist.

private:
    char userID[8];   // Member variable for storing user ID (max length: 8 characters)
    char name[30];    // Member variable for storing user name (max length: 30 characters)
    char phone[12];   // Member variable for storing user phone number (max length: 12 characters)
    char email[24];   // Member variable for storing user email address (max length: 24 characters)
};

#endif // USER_H
