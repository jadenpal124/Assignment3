// TO RUN PROGRAM:  
//   g++ -std=c++11  Main.cpp UI.cpp changeItem.cpp controlModule.cpp changeRequest.cpp User.cpp Product.cpp Release.cpp -o program && ./program


// Revision History:
// Rev. 1 - 04/07/24 Original by JAWS
//==================================================
// Description: This module is the main.cpp and initializes and runs the UI module.
//==================================================
#include <iostream>
#include "UI.cpp" // Include the UI module source file

using namespace std;
//==================================================

//----------------------
int main() {
    UIModule uiModule; // Create an instance of UIModule
    uiModule.run();    // Call the run() method to start the UI module
    return 0;
}
// Description: Initializes and runs the UI module.
// Parameters: None.
// Exceptions: None.



/*
******Coding Convention******

Revision History: 
Rev. 1 - 04/07/24 Original by JAWS
//==================================================
Description: Here write a couple sentences on what this module is for 
//==================================================
Any include statements will go here
//==================================================
Any static, exported, global, etc variables, functions
will go here
//==================================================
Any class definitions will go here in the following order
Classes:
1. Public:
2. Protected:
3. Private:
//==================================================
Function bodies should look like this:
//----------------------
void funcName(parameters) { // Brace on same line as name.
    // Indent function and loop blocks by 4 spaces.
    int i = 3;
}
The following comments must follow each main function.
//Description: A paragraph describing the function on what it does
               what it will do with its parameters if any, and what 
               it will return
//Parameters: List each parameter and describe its purpose, along with
              if it is input or output e.g. 

             - releaseID: Pointer to a character array containing the release ID (input)

//Exceptions: If any exceptions may be caused describe them here.

NOTE: 
    All general comments will be to the right of line statements. e.g.

        Product product; // Product object to reference Product class

    All names will follow cammel case, first word lower case then all 
    proceeding words will be Capitalized. e.g. 

        thisIsAnExample

    There will be a space following each word and after any symbols e.g.

        void setReleaseDate (const char* releaseDate) {};

        there is a space between setReleaseDate and (const char* releaseDate);
        also there is a space between () {}.

*/







