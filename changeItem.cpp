#include "changeItem.h"
#include <iomanip>

changeItem::changeItem () {
    initChangeItem();
}   

changeItem::changeItem (int changeItemID, const char* description, const Product* product, const Release* releasePtr) {
    setChangeItemID (changeItemID);
    setDescription (description);
    setAnticipatedRelease (releasePtr);
    setAssociatedProduct (product);
}

int changeItem::getChangeItemID () const {
    return changeItemID;
}    

const char* changeItem::getDescription () const {
    return description;
}  

const char* changeItem::getAnticipatedReleaseID () const {
    return anticipatedRelease->getReleaseID();
}    

changeItem::Status changeItem::getStatus () const {
    return status;
}    
 
const Product* changeItem::getAssociatedProduct () const {
    return associatedProduct;
}  
 
void changeItem::setChangeItemID (int changeItemID) {
    this->changeItemID = changeItemID;
}   

void changeItem::setDescription (const char* description) {
    strncpy(this->description, description, sizeof(this->description) - 1);
    this->description[sizeof(this->description) - 1] = '\0'; // Ensure null-termination
}

void changeItem::setStatus (Status status) {
    this->status = status;
}    

void changeItem::setAnticipatedRelease (const Release* releasePtr) {
    this->anticipatedRelease = releasePtr;
} 

void changeItem::setAssociatedProduct (const Product* productPtr) {
    this->associatedProduct = productPtr;
}

changeItem& changeItem::checkChangeItem (const char* fileName, int changeItemIDToFind) {
    ifstream inFile(fileName, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw exception(); // Throwing exception if file cannot be opened
    }

    static changeItem ChangeItem; // Static to ensure it persists after function ends
    bool found = false;

    // Search for the user by userID
    while (inFile.read(reinterpret_cast<char*>(&ChangeItem), sizeof(changeItem))) {
        if (ChangeItem.getChangeItemID() == changeItemIDToFind) {
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) {
        cerr << "Error: Change Item with ID " << changeItemIDToFind << " not found." << endl;
        throw exception(); // Throwing exception if user not found
    }

    return ChangeItem;
}    

bool changeItem::updateChangeItem (const char* fileName, int changeItemIDToFind){
    fstream file(fileName, ios::in | ios::out | ios::binary);
    if (!file) {
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    bool found = false;
    changeItem temp;

    // Search for the user by userID and update information
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(changeItem))) {
        if (temp.getChangeItemID() == changeItemIDToFind ) {
            // Update information
            temp.setDescription(description);
            temp.setAnticipatedRelease(anticipatedRelease);
            temp.setAssociatedProduct(associatedProduct);

            // Write back to file
            file.seekp(-static_cast<int>(sizeof(changeItem)), ios::cur);
            file.write(reinterpret_cast<const char*>(&temp), sizeof(changeItem));
            found = true;
            break;
        }
    }

    file.close();
    return found;
}    

bool changeItem::addChangeItem (const char* fileName) {
    ofstream outFile(fileName, ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    // Write user information to file
    outFile.write(reinterpret_cast<const char*>(this), sizeof(changeItem));
    outFile.close();
    return true;
}    

int changeItem::searchChangeItemID (const char* fileName, int changeItemIDToFind) {
    ifstream readFile(fileName, ios::binary);
    if (!readFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw exception(); // Throwing exception if file cannot be opened
    }

    static changeItem ChangeItem; // Static to ensure it persists after function ends
    int thePlace = -1; // the place of the change item in the file

    // Search for the user by userID
    while (readFile.read(reinterpret_cast<char*>(&ChangeItem), sizeof(changeItem))) {
        ++thePlace;
        if (ChangeItem.getChangeItemID() == changeItemIDToFind) {
            break;
        }
    }

    readFile.close();
    return thePlace;
}    

void changeItem::displayRemainingReports (const char* fileName) const {
    ifstream readFile(fileName, ios::binary);
    if (!readFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw exception(); // Throwing exception if file cannot be opened
    }

    static changeItem ChangeItem;
    static Product tempProduct;
    static int thePlace = 0;

    //we need a function from product.h that displays all the products so use can choose the product - according to assignment2 we need to display all th products

    std::cout << std::setw(2) << "#" << " "
            << std::setw(10) << "ProductID" << " "
            << std::setw(10) << "changeID" << " "
            << std::setw(10) << "ReleaseID" << " "
            << std::setw(10) << "Status" << " "
            << std::setw(20) << "Description" << std::endl;
    std::cout << std::setw(10) << "--"
            << std::setw(10) << "---------"
            << std::setw(10) << "---------"
            << std::setw(10) << "---------"
            << std::setw(10) << "---------"
            << std::setw(20) << "--------------------" << std::endl;
    while (readFile.read(reinterpret_cast<char*>(&ChangeItem), sizeof(changeItem))) {
        ++thePlace;
        if (ChangeItem.getStatus() != Status::Done || ChangeItem.getStatus() != Status::Cancelled) {
            tempProduct = ChangeItem.getAssociatedProduct();
            std::cout << std::setw(2) << thePlace << " "
            << std::setw(10) << tempProduct.getProductID() << " "
            << std::setw(10) << ChangeItem.getChangeItemID() << " "
            << std::setw(10) << ChangeItem.getAnticipatedReleaseID() << " "
            << std::setw(10) << ChangeItem.getStatus() << " "
            << std::setw(20) << ChangeItem.getDescription() << std::endl;  
        }
    }

}   

void changeItem::displayNotifyReport (const char* fileName) const {

}    


void changeItem::initChangeItem ();

void changeItem::closeChangeItem ();


