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
#include "Product.h"
#include "User.h"
#include "changeRequest.h"
#include "Release.h"
#include "changeItem.h"

using namespace std;

//==================================================

// Function prototypes for operations handled by the control module

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

#endif // CONTROL_MODULE_H