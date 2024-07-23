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
#include <fstream>
#include <cstring> // For string manipulation functions
using namespace std;
//==================================================
class User {
public:
    // Constructors
    User (); 
    // Description: Default constructor initializing a User object with default values.

    User (const char* userID, const char* name, const char* phone, const char* email); 
    // Description: Parameterized constructor initializing userID, name, phone, and email with provided values.
    // Parameters:
    //   - userID: Pointer to a character array containing the user ID (input)
    //   - name: Pointer to a character array containing the user name (input)
    //   - phone: Pointer to a character array containing the user phone (input)
    //   - email: Pointer to a character array containing the email (input)

    // Getter methods
    //----------------------
    const char* getUserID () const;   
    // Description: Getter for retrieving user ID
    // Parameters: None
    // Returns: Pointer to a constant character array containing the user ID

    //----------------------
    const char* getName () const;     
    // Description: Getter for retrieving user name
    // Parameters: None
    // Returns: Pointer to a constant character array containing the user name

    //----------------------
    const char* getPhone () const;    
    // Description: Getter for retrieving user phone number
    // Parameters: None
    // Returns: Pointer to a constant character array containing the user phone number

    //----------------------
    const char* getEmail () const;    
    // Description: Getter for retrieving user email address
    // Parameters: None
    // Returns: Pointer to a constant character array containing the user email address

    // Setter methods
    //----------------------
    void setUserID (const char* userID); 
    // Description: Setter for setting user ID
    // Parameters:
    //   - userID: Pointer to a character array containing the user ID (input)

    //----------------------
    void setName (const char* name);     
    // Description: Setter for setting user name
    // Parameters:
    //   - name: Pointer to a character array containing the user name (input)

    //----------------------
    void setPhone (const char* phone);   
    // Description: Setter for setting user phone number
    // Parameters:
    //   - phone: Pointer to a character array containing the user phone (input)

    //----------------------
    void setEmail (const char* email);   
    // Description: Setter for setting user email address
    // Parameters:
    //   - email: Pointer to a character array containing the email (input)

    // Utility methods
    //----------------------
    void displayUserInfo () const;
    // Description: Displays user information from the currently managed file.
    // Exception:
    //   May throw an exception if the file cannot be accessed.

    //----------------------
    bool changeUserInfo ();
    // Description: Updates the user's information such as name, phone, email, and department in the currently managed file.
    // Returns:
    //   true if the user information was successfully updated; false otherwise.
    // Exception:
    //   May throw an exception if the file cannot be accessed.

    //----------------------
    User& checkUser (const char* userID);
    // Description: Searches the currently managed file for a user based on the provided userID 
    //              and returns a reference to the found User object if the user exists.
    // Parameters:
    //   - userID: Pointer to a character array containing the user ID to search for (input).
    // Returns:
    //   Reference to a User object representing the user with the given userID.
    // Exceptions:
    //   May throw an exception if the file cannot be accessed.

    //----------------------
    bool addUser ();
    // Description: Adds the user's details to the currently managed file.
    // Returns:
    //   true if the user details were successfully added; false otherwise.
    // Exceptions:
    //   May throw an exception if the file cannot be accessed.

    // Session management methods
    //----------------------
    void initUser (const char* fileName);
    // Description: Initializes the User object and opens the file for operations.

    //----------------------
    void closeUser ();
    // Description: Closes the file and performs any necessary cleanup.

    //----------------------
    User displayUsersFromFile() const;
    // Description: Displays users stored in the currently managed file in batches of 5, allowing scrolling.
    //              User can press Enter to view the next 5 users or 'q' to stop.
    //              Allows the user to select and returns that user.
    // Exceptions:
    //   May throw an exception if the file cannot be accessed.

private:
    char userID[9];   // Member variable for storing user ID (max length: 8 characters)
    char name[31];    // Member variable for storing user name (max length: 30 characters)
    char phone[13];   // Member variable for storing user phone number (max length: 12 characters)
    char email[25];   // Member variable for storing user email address (max length: 24 characters)
    static fstream fileStream; // Member variable for managing file operations
};

#endif // USER_H
