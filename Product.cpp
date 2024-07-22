
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


// Copy constructor
Product::Product(const Product& other) {
    // Copy data from other object
    strncpy(this->productID, other.productID, sizeof(this->productID) - 1);
    this->productID[sizeof(this->productID) - 1] = '\0';

    strncpy(this->name, other.name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0';
}

// Assignment operator
Product& Product::operator=(const Product& other) {
    if (this != &other) { // Self-assignment check
        // Copy data from other object
        strncpy(this->productID, other.productID, sizeof(this->productID) - 1);
        this->productID[sizeof(this->productID) - 1] = '\0';

        strncpy(this->name, other.name, sizeof(this->name) - 1);
        this->name[sizeof(this->name) - 1] = '\0';
    }
    return *(this);
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

Product Product::displayProductFromFile(const char* fileName) const {
    ifstream inFile(fileName, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        return Product(); // Return a default product in case of error
    }

    const int numRecordsPerPage = 5; // Number of records to display per page
    int startRecord = 0; // Starting record index
    bool displayNextPage = true;
    Product selectedProduct; // To store the selected product
    bool productSelected = false; // Flag to track if a product was selected

    while (displayNextPage) {
        // Display header
        cout << "Product List - Select a Product:" << endl;
        cout << "Page " << (startRecord / numRecordsPerPage + 1) << endl;
        cout << setw(2) << "#" << "  ";
        cout << setw(10) << "Product ID" << "  ";
        cout << setw(15) << "Product Name" << endl;
        cout << setw(2) << "--" << "  ";
        cout << setw(10) << "----------" << "  ";
        cout << setw(15) << "-------------" << endl;

        // Display records
        bool endOfFile = false;
        int displayedCount = 0;
        inFile.clear();
        inFile.seekg(startRecord * sizeof(Product), ios::beg);

        for (int i = 0; i < numRecordsPerPage; ++i) {
            Product product;
            if (!inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
                endOfFile = true; // End of file
                break;
            }
            cout << setw(2) << startRecord + i + 1 << "  ";
            cout << setw(10) << product.getProductID() << "  ";
            cout << setw(15) << product.getName() << endl;
            ++displayedCount;
        }

        // Prompt user for input
        if (!endOfFile) {
            cout << endl;
            cout << "Press <enter> to display the next " << numRecordsPerPage << " rows, or \"q\" to go back." << endl;
            cout << "If you would like to select a product type the number #." << endl;
            cout << "If a Product ID is known type \"s\" to enter it." << endl;

            string selection;
            cout << "Enter Selection: ";
            getline(cin, selection);

            // Handle user input
            if (selection.empty()) {
                // Default action: Display next page
                startRecord += numRecordsPerPage;
            } else if (selection == "q") {
                // Quit action
                displayNextPage = false; // Exit loop
            } else if (selection == "s") {
                // Enter Product ID action
                cout << "Enter Product ID: ";
                string productID;
                getline(cin, productID);
                inFile.clear();
                inFile.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                Product product;
                while (inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
                    if (strcmp(product.getProductID(), productID.c_str()) == 0) {
                        cout << "Product found: " << product.getName() << endl;
                        selectedProduct = product;
                        found = true;
                        productSelected = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Product ID not found." << endl;
                } else {
                    displayNextPage = false; // Exit loop if product is found
                }
            } else if (isdigit(selection[0])) {
                // Select by number action
                int selectedNumber = stoi(selection);
                inFile.clear();
                inFile.seekg((selectedNumber - 1) * sizeof(Product), ios::beg);
                Product product;
                if (inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
                    cout << "Product selected: " << product.getName() << endl;
                    selectedProduct = product;
                    productSelected = true;
                    displayNextPage = false; // Exit loop if product is selected
                } else {
                    cout << "Invalid selection." << endl;
                }
            } else {
                cout << "Invalid selection." << endl;
            }
        } else {
            // End of file reached
            cout << "End of file reached. Press 'q' to go back." << endl;
            cout << "If you would like to select a product type the number #." << endl;
            cout << "If a Product ID is known type \"s\" to enter it." << endl;

            string selection;
            cout << "Enter Selection: ";
            getline(cin, selection);

            if (selection == "q") {
                displayNextPage = false; // Exit loop
            } else if (selection == "s") {
                // Enter Product ID action
                cout << "Enter Product ID: ";
                string productID;
                getline(cin, productID);
                inFile.clear();
                inFile.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                Product product;
                while (inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
                    if (strcmp(product.getProductID(), productID.c_str()) == 0) {
                        cout << "Product found: " << product.getName() << endl;
                        selectedProduct = product;
                        found = true;
                        productSelected = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Product ID not found." << endl;
                } else {
                    displayNextPage = false; // Exit loop if product is found
                }
            } else if (isdigit(selection[0])) {
                // Select by number action
                int selectedNumber = stoi(selection);
                inFile.clear();
                inFile.seekg((selectedNumber - 1) * sizeof(Product), ios::beg);
                Product product;
                if (inFile.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
                    cout << "Product selected: " << product.getName() << endl;
                    selectedProduct = product;
                    productSelected = true;
                    displayNextPage = false; // Exit loop if product is selected
                } else {
                    cout << "Invalid selection." << endl;
                }
            } else {
                cout << "Invalid selection." << endl;
            }
        }
    }

    inFile.close();
    if (productSelected) {
        return selectedProduct; // Return the selected product
    } else {
        return Product(); // Return a default product if none selected
    }
}


void Product::initProduct () {
    memset(productID, 0, sizeof(productID));
    memset(name, 0, sizeof(name));
}

void Product::closeProduct () {
    // Delete the Object and frees any memory allocated on the heap.
    // This class does not use heap memory, so nothing to do here.
}
