/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS /
//==================================================
/ This module defines functions for handling various operations related to adding products, release's, and change requests,
   user updates, change requests, and reports within the system. /
//==================================================
/ Include Statements */
#ifndef CONTROL_MODULE_H
#define CONTROL_MODULE_H

#include <iostream>
#include <cstring>

#include "ChangeItem.h"
#include "ChangeRequest.h"
#include "User.h"
#include "Release.h"
#include "Product.h"


using namespace std;

//==================================================

extern User userTmp;
extern Product prodTmp;
extern Release relTmp;
extern changeRequest chRTmp;
extern changeItem chItemTmp;

extern const char* changeItemFile;
extern const char* productFile;
extern const char* releaseFile;
extern const char* userFile;
extern const char* changeRequestFile;

//==================================================

// Function prototypes for operations handled by the control module
void initialize ();
// Description: 
//   Initialize files

void close ();
//Description: 
//   Closes All files

void addProductControl ();
// Description:
//   Executes 'Add Product' operation.

//--------------------
void addReleaseControl ();
// Description:
//   Executes 'Add Release' operation.

//--------------------
void addChangeRequestControl ();
// Description:
//   Executes 'Add Change Request' operation.

//--------------------
void updateUserControl ();
// Description:
//   Executes 'Update User' operation.

//--------------------
void  updateChangeItemControl ();
// Description:
//   Executes 'Update Single Issue' operation.

//--------------------
void displayRemReportControl ();
// Description:
//   Executes ' Displays list Remaining Items Report' operation.

//--------------------
void displayNotifyReportControl ();
// Description:
//   Executes ' Displays Users to be Notified Report' operation.

//--------------------
void getStatusControl ();
// Description:
//   Executes ' Displays list of Status of Change Items' operation.

//==================================================
#endif // CONTROL_MODULE_H