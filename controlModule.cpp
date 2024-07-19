#include "controlModule.h"

using namespace std;


void addProductControl () {

}

void addReleaseControl () {

}

void addChangeRequestControl () {

}

void updateUserControl () {

}

void updateChangeItemControl (const char* fileNameProduct, const char* fileNameChangeItem) {
    Product tempProduct;
    Product* tempProductPtr;
    changeItem tempChangeItem;

    tempProductPtr = &(tempProduct.displayProductFromFile(fileNameProduct));
    tempChangeItem = tempChangeItem.displayAndReturnChangeItem(fileNameChangeItem, tempProductPtr);
    tempChangeItem.updateChangeItem(fileNameChangeItem,tempChangeItem);

}

void displayRemReportControl () {

}

void displayNotifyReportControl () {

}

void getStatusControl () {

}


