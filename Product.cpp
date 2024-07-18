
#include "Product.h"
#include <iostream>
#include <fstream>
#include <iomanip> // for std::setw
#include <cstdlib> // for std::exit

// Default constructor
Product::Product () {
  initProduct ();
}

// Parameterized constructor
Product::Product (const char* productID, const char* name) {
    initProduct ();
    setProductID (productID);
    setName (name);
}

// Getter methods
const char* Product::getProductID () const {
    return productID;
}

const char* Product::getName () const {
    return name;
}

// Setter methods
void Product::setProductID (const char* productID) {
    strncpy(this->productID, productID, sizeof (this->productID) - 1);
    this->productID[sizeof(this->productID) - 1] = '\0';
}

void Product::setName (const char* name) {
    strncpy(this->name, name, sizeof (this->name) - 1);
    this->productID[sizeof(this->name) - 1] = '\0';
}



// Utility methods

void Product::displayProductInfo(const char* fileName) const {
    ifstream inFile(fileName, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw exception(); // Throwing exception if file cannot be opened
    }

    // Read product info from file
    while (inFile.read(reinterpret_cast<char*>(const_cast<Product*>(this)), sizeof(Product))) {
        cout << "Product ID: " << productID << endl;
        cout << "Name: " << name << endl;
    }

    inFile.close();
}

bool Product::addProduct(const char* fileName) {
    ofstream outFile(fileName, ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    // Write product information to file
    outFile.write(reinterpret_cast<const char*>(this), sizeof(Product));
    outFile.close();
    return true;
}

Product& Product::checkProductExists(const char* fileName, const char* productIDToFind) {
    ifstream inFile(fileName, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw exception(); // Throwing exception if file cannot be opened
    }

    static Product product; // Static to ensure it persists after function ends
    bool found = false;

    // Search for the product by productID
    while (inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
        if (strcmp(product.getProductID(), productIDToFind) == 0) {
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) {
        cerr << "Error: Product with ID " << productID << " not found." << endl;
        throw exception(); // Throwing exception if product not found
    }

    return product;
}

void Product::displayProductFromFile(const char* fileName) const {
    ifstream readFile(fileName, ios::binary);
    if (!readFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw exception(); // Throwing exception if file cannot be opened
    }

    readFile.seekg(0, ios::end);
    size_t fileSize = readFile.tellg();
    size_t totalItems = fileSize / sizeof(Product);
    readFile.seekg(0, ios::beg);

    int pageTotal = (totalItems + 4) / 5; // Total pages, rounded up
    int pageCount = 0;
    char userInput;

    do {
        cout << "Product List (Page " << pageCount + 1 << "/" << pageTotal << ")" << endl;
        cout << setw(2) << "#" << " "
             << setw(10) << "ProductID" << " "
             << setw(15) << "Product name" << endl;
        cout << setw(2) << "--" << " "
             << setw(10) << "---------" << " "
             << setw(15) << "------------" << endl;

        readFile.clear(); // Clear EOF flag
        readFile.seekg(pageCount * 5 * sizeof(Product), ios::beg);

        for (int i = 0; i < 5 && pageCount * 5 + i < totalItems; ++i) {
            Product tempProduct;
            readFile.read(reinterpret_cast<char*>(&tempProduct), sizeof(Product));
            cout << setw(2) << pageCount * 5 + i + 1 << " "
                 << setw(10) << tempProduct.getProductID() << " "
                 << setw(15) << tempProduct.getName() << endl;
        }

        cout << "\nPress <enter> to display the next 5 rows, or “q” to go back." << endl;
        cout << "If the Product ID is known enter “s”." << endl;
        cout << "Type number # to select a product." << endl;
        cout << "Enter Selection: ";
        userInput = cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

        if (userInput == 'q') {
            if (pageCount > 0) {
                --pageCount;
            } else {
                cout << "Already at the first page." << endl;
            }
        } else if (userInput == '\n') {
            if (pageCount < pageTotal - 1) {
                ++pageCount;
            } else {
                cout << "Already at the last page." << endl;
            }
        } else if (userInput == 's') {
            char searchID[10];
            cout << "Enter Product ID to search: ";
            cin.getline(searchID, 10);
            bool found = false;

            readFile.clear();
            readFile.seekg(0, ios::beg);
            Product tempProduct;
            while (readFile.read(reinterpret_cast<char*>(&tempProduct), sizeof(Product))) {
                if (strcmp(tempProduct.getProductID(), searchID) == 0) {
                    cout << "Product found: " << tempProduct.getName() << endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Product ID not found." << endl;
            }
        } else if (isdigit(userInput)) {
            int selection = userInput - '0';
            if (selection > 0 && selection <= totalItems) {
                readFile.clear();
                readFile.seekg((selection - 1) * sizeof(Product), ios::beg);
                Product tempProduct;
                readFile.read(reinterpret_cast<char*>(&tempProduct), sizeof(Product));
                cout << "Product selected: " << tempProduct.getName() << endl;
            } else {
                cout << "Invalid selection." << endl;
            }
        }
    } while (userInput != 'q');
}


void Product::initProduct () {
    memset(productID, 0, sizeof(productID));
    memset(name, 0, sizeof(name));
}

void Product::closeProduct () {
    // Delete the Object and frees any memory allocated on the heap.
    // This class does not use heap memory, so nothing to do here.
}
