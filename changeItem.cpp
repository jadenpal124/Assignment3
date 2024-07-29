#include "changeItem.h"
#include <iomanip>
#include <vector>


changeItem::changeItem() {
    // Default constructor body (can be empty)
}   

changeItem::changeItem(int changeItemID, const char* description, const Product* product, const Release* releasePtr) {
    setChangeItemID (changeItemID);
    setDescription (description);
    setAnticipatedRelease (releasePtr);
    setAssociatedProduct (product);
}

// Copy constructor
changeItem::changeItem(const changeItem& other) {
    this->changeItemID = other.changeItemID;
    this->associatedProduct = other.associatedProduct;
    this->anticipatedRelease = other.anticipatedRelease;
    this->description = other.description;
}

// Overloaded= operator
changeItem& changeItem::operator=(const changeItem& other) {
    if (this != &other) {
        this->changeItemID = other.changeItemID;
        this->associatedProduct = other.associatedProduct;
        this->anticipatedRelease = other.anticipatedRelease;
        this->description = other.description;
    }
    return *this;
}

int changeItem::getChangeItemID () const {
    return changeItemID;
}    

const string* changeItem::getDescription () const {
    return &description;
}  

const Release changeItem::getAnticipatedRelease () const {
    return anticipatedRelease;
}

const char* changeItem::getAnticipatedReleaseID () const {
    return anticipatedRelease.getReleaseID();
}    

changeItem::Status changeItem::getStatus () const {
    return status;
}  

const Product changeItem::getAssociatedProduct () const {
    return associatedProduct;
}
 
const char* changeItem::getAssociatedProductID () const {
    return associatedProduct.getProductID() ;
}  
 
void changeItem::setChangeItemID (int changeItemID) {
    this->changeItemID = changeItemID;
}   

void changeItem::setDescription (const string descriptionNew) {
    description = descriptionNew; // Ensure null-termination
}

void changeItem::setStatus (Status status) {
    this->status = status;
}    

void changeItem::setAnticipatedRelease (const Release* releasePtr) {
    this->anticipatedRelease = *releasePtr;
} 

void changeItem::setAssociatedProduct (const Product* productPtr) {
    this->associatedProduct = *productPtr;
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

bool changeItem::updateChangeItem (const char* fileName, int changeItemToIDfind){
    fstream file(fileName, ios::in | ios::out | ios::binary);
    if (!file) {
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    bool found = false;
    int changeItemToFindID;
    changeItem temp;
    char userInput;
    char* userInput3;
    char userInput2;
    Release tempRelease;
    Release tempReleaseFound;
    Status tempStatus;
    

    //changeItemToFindID = changeItemTofind.getChangeItemID();

    // Search for the user by changeItemID and update information
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(changeItem))) {
        if (temp.getChangeItemID() == changeItemToFindID ) {
            std::cout << "Current details for Change ID: " << std::endl
            << "ProductID: " << temp.getAssociatedProductID() << std::endl
            << "ChangeID: " << temp.getChangeItemID() << std::endl
            << "Anticipated ReleaseID: " << temp.getAnticipatedReleaseID() << std::endl
            << "Status: " << temp.getStatus() << std::endl
            << "Description: " << temp.getDescription() << std::endl
            << std::endl 
            << "Enter the number of the field you want to update:" << std::endl
            << "    1) ReleaseID" << std::endl
            << "    2) Status" << std::endl
            << "    3) Description" << std::endl
            << "    0) Quit" << std::endl;
            std::cin >> userInput ;

            switch (userInput)
            {
            case '1':
                while (true) {
                std::cout << "Enter new Release ID (1-8 Character Length):";
                std::cin >> userInput3;
                std::cout << "Do you want to update Release ID to" << userInput << "(select Y/N)?";
                std::cin >> userInput2;
                if (userInput2 == 'Y') {
                   tempReleaseFound = tempRelease.findReleaseAndReturn(userInput3, associatedProduct.getProductID() );
                    anticipatedRelease = tempReleaseFound;
                    std::cout << "Release ID Successfully updated." << std::endl;
                break;
                }
                }
                break;
            case '2':
                while (true) {
                    std::cout << "Enter new Status:" << endl 
                    << "    1) NewRequest" << std::endl
                    << "    2) ReviewRequest" << std::endl
                    << "    3) InProgress" << std::endl
                    << "    4) Done" << std::endl
                    << "    5) Cancelled" << std::endl;
                    std::cin >> userInput;
                    if (userInput == 1) {
                        tempStatus = NewRequest;
                    }
                    if (userInput == 2) {
                        tempStatus = ReviewRequest;
                    }
                    if (userInput == 3) {
                        tempStatus = InProgress;
                    }
                    if (userInput == 4) {
                        tempStatus = Done;
                    }
                    if (userInput == 5) {
                        tempStatus = Cancelled;
                    }
                    std::cout << "Do you want to update Status to" << tempStatus << "(select Y/N)?";
                    std::cin >> userInput2;
                    if (userInput2 == 'Y') {
                        status = tempStatus;
                        std::cout << "Status Successfully updated." << std::endl;
                        break;
                    }
                }
                break;
            case '3':
                while (true) {
                    std::cout << "Enter new Description (1-30 Character Length):";
                    std::cin >> userInput3;
                    std::cout << "Do you want to update the description to" << userInput3 << "(select Y/N)?";
                    std::cin >> userInput2;
                    if (userInput2 == 'Y') {
                        description = userInput3;
                        std::cout << "Description Successfully updated." << std::endl;
                        break;
                    }
                    break;
                }
            case '0':
                break;
            }
            
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
    tempProduct = tempProduct.displayProductFromFile();

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
        if ( !(ChangeItem.getStatus() == Status::Done || ChangeItem.getStatus() == Status::Cancelled)&& ChangeItem.getAssociatedProductID() == tempProduct.getProductID()) {
            std::cout << std::setw(2) << thePlace << " "
            << std::setw(10) << tempProduct.getProductID() << " "
            << std::setw(10) << ChangeItem.getChangeItemID() << " "
            << std::setw(10) << ChangeItem.getAnticipatedReleaseID() << " "
            << std::setw(10) << ChangeItem.getStatus() << " "
            << std::setw(20) << ChangeItem.getDescription() << std::endl;  
        }
    }

}   

changeItem changeItem::displayAndReturnChangeItem(const char* fileName, const char* productIDToFind) {
    ifstream readFile(fileName, ios::binary);
    if (!readFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw exception(); // Throwing exception if file cannot be opened
    }

    //Product tempProduct = *productToFind;
    changeItem changeItemTemp;
    int itemTotal = 0;          //total number of items with the specific productID
    int pageTotal = 0;          //total pages to show the data, it is totalItem divided by 5
    int pageCount= 0;           //just for counting how many pages we have shown so far
    int itemCount = 0;          //just for counting how many items we have shown so far
    int d;
    char userinput ;
    vector<changeItem> changeItemVector;

    while (readFile.read(reinterpret_cast<char*>(&changeItemTemp), sizeof(changeItem))) {
        if (changeItemTemp.getAssociatedProductID() == productIDToFind) {
        ++itemTotal;
        changeItemVector.push_back(changeItemTemp);  //making a vector of changeItem objects so later we can return the object we are looking for
        }
    }
    readFile.close();


    pageTotal = itemTotal / 5;
    
    for (int i = 1 ; i < pageCount ; i++ ) {
    std::cout << "Change Item of Product(Page " << i << "/" << pageCount+1 <<")" << endl;
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

    for (int q= 0; q<5; q++ ) {    
        //if (changeItemTemp.getAssociatedProduct() == productToFind) {
            if (itemCount >= itemTotal) {
                break;
            }
            std::cout << std::setw(2) << itemCount+1 << " "
            << std::setw(10) << changeItemVector[itemCount].getAssociatedProductID() << " "  // can be changed to a var
            << std::setw(10) << changeItemVector[itemCount].getChangeItemID() << " "
            << std::setw(10) << changeItemVector[itemCount].getAnticipatedReleaseID() << " "
            << std::setw(10) << changeItemVector[itemCount].getStatus() << " "
            << std::setw(20) << changeItemVector[itemCount].getDescription() << std::endl;  
        //}
        ++itemCount;
    }
    std::cout << "Press <enter> to display the next 5 rows, or “q” to go back." << endl;
    std::cout << "If the change ID is known enter “s”." << endl;
    std::cout << "Type number # to select a change item." << endl;
    std::cout << "To return to menu type “0”:" << endl;
    std::cin >> userinput ;

    switch (userinput)
    {
    case 'n':
        ++pageCount;
        break;

    case 'q':
        itemCount = pageCount*5;
        break;

    case 's':

    default:    //not checking for invalid input yet
    int x = userinput - '0';
    changeItem *changeItemTempPtr = &changeItemVector[x];
    return *changeItemTempPtr;   
    break;
    }
    }
    return changeItemVector[userinput];
}


void changeItem::initChangeItem (const char* fileName) {
    this->fileName = fileName;
    file.open(fileName, ios::in | ios::out | ios::binary);
    if (!file) {
        throw runtime_error("Error: Could not open file");
    }
}

void changeItem::closeChangeItem () {

}


