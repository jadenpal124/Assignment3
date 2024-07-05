/* Revision History: 
   Rev. 1 - 04/07/24 Original by JAWS */
//==================================================
/* This module defines functions for handling various operations related to adding products, release's, and change requests,
   user updates, change requests, and reports within the system. */
//==================================================
/* Include Statements */
#ifndef CONTROL_MODULE_H
#define CONTROL_MODULE_H

#include <iostream>
#include "product.h"
#include "user.h"
#include "changeRequest.h"
#include "release.h"
#include "changeItem.h"

using namespace std;

//==================================================

// Function prototypes for operations handled by the control module

void AddProduct();
// Parameters: None
// Returns: void
// Description:
//   Executes 'Add Product' operation.

//--------------------
void AddRelease();
// Parameters: None
// Returns: void
// Description:
//   Executes 'Add Release' operation.

//--------------------
void AddChangeRequest();
// Parameters: None
// Returns: void
// Description:
//   Executes 'Add Change Request' operation.

//--------------------
void updateUser();
// Parameters: None
// Returns: void
// Description:
//   Executes 'Update User' operation.

//--------------------
void  updateChangeItem();
// Parameters: None
// Returns: void
// Description:
//   Executes 'Update Single Issue' operation.

//--------------------
void displayRemReport();
// Parameters: None
// Returns: void
// Description:
//   Executes 'Remaining Items Report' operation.

//--------------------
void displayNotifyReport();
// Parameters: None
// Returns: void
// Description:
//   Executes 'Users to be Notified Report' operation.

//--------------------
void getStatus();
// Parameters: None
// Returns: void
// Description:
//   Executes 'Status of Change Items' operation.

#endif // CONTROL_MODULE_H
