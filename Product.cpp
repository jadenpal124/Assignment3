
#include "Product.h"
#include <iostream>
#include <fstream>
#include <iomanip> // for std::setw
#include <cstdlib> // for std::exit

// Initialize the static member variable
fstream Product::file;

// Default constructor
Product::Product() {
    productID[0] = '\0';
    name[0] = '\0';
}

// Parameterized constructor
Product::Product(const char* productID, const char* name) {
    strncpy(this->productID, productID, sizeof(this->productID) - 1);
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->productID[sizeof(this->productID) - 1] = '\0';
    this->name[sizeof(this->name) - 1] = '\0';
}

// Copy constructor
Product::Product(const Product& other) {
    strncpy(this->productID, other.productID, sizeof(this->productID) - 1);
    strncpy(this->name, other.name, sizeof(this->name) - 1);
    this->productID[sizeof(this->productID) - 1] = '\0';
    this->name[sizeof(this->name) - 1] = '\0';
}

// Assignment operator
Product& Product::operator=(const Product& other) {
    if (this != &other) {
        strncpy(this->productID, other.productID, sizeof(this->productID) - 1);
        strncpy(this->name, other.name, sizeof(this->name) - 1);
        this->productID[sizeof(this->productID) - 1] = '\0';
        this->name[sizeof(this->name) - 1] = '\0';
    }
    return *this;
}

// Getter methods
const char* Product::getProductID() const {
    return productID;
}

const char* Product::getName() const {
    return name;
}

// Setter methods
void Product::setProductID(const char* productID) {
    strncpy(this->productID, productID, sizeof(this->productID) - 1);
    this->productID[sizeof(this->productID) - 1] = '\0';
}

void Product::setName(const char* name) {
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0';
}

// Utility methods
Product& Product::checkProductExists(const char* productIDToFind) {
    file.seekg(0, ios::beg);
    while (file.read(reinterpret_cast<char*>(this), sizeof(Product))) {
        if (strcmp(this->productID, productIDToFind) == 0) {
            return *this;
        }
    }
    throw runtime_error("Product not found");
}

void Product::displayProductInfo() const {
    cout << "Product ID: " << productID << endl;
    cout << "Product Name: " << name << endl;
}

bool Product::addProduct() {
    file.seekp(0, ios::end);
    file.write(reinterpret_cast<const char*>(this), sizeof(Product));
    return file.good();
}

Product Product::displayProductFromFile() const {
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
        file.clear();
        file.seekg(startRecord * sizeof(Product), ios::beg);

        for (int i = 0; i < numRecordsPerPage; ++i) {
            Product product;
            if (!file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
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
                file.clear();
                file.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                Product product;
                while (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
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
                file.clear();
                file.seekg((selectedNumber - 1) * sizeof(Product), ios::beg);
                Product product;
                if (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
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
                file.clear();
                file.seekg(0, ios::beg); // Move file pointer to beginning
                bool found = false;
                Product product;
                while (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
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
                file.clear();
                file.seekg((selectedNumber - 1) * sizeof(Product), ios::beg);
                Product product;
                if (file.read(reinterpret_cast<char*>(&product), sizeof(Product))) {
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

    if (productSelected) {
        return selectedProduct; // Return the selected product
    } else {
        return Product(); // Return a default product if none selected
    }
}

// Session management methods
void Product::initProduct(const char* fileName) {
    this->fileName = fileName;
    file.open(fileName, ios::in | ios::out | ios::binary);
    if (!file) {
        throw runtime_error("Error: Could not open file");
    }
}

void Product::closeProduct() {
    file.close();
}
