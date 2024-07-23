/* Revision History: 
   Rev. 1 - 04/15/24 Original by JAWS */
//================================ 
/* This module implements the Product class, which encapsulates data related to a product.
   The class provides methods to access, modify, and manage product information,
   demonstrating the principles of abstraction and high cohesion by encapsulating
   related functionality within the Product class. */
//================================ 

#include "Product.h"

//================================ 

// Initialize the static member variable
fstream Product::file;

//================================ 

// Default constructor
//----------------------
Product::Product () {
    productID[0] = '\0';
    name[0] = '\0';
}
//----------------------
// Parameterized constructor

Product::Product (const char* productID, const char* name) {
// Parameterized constructor initializing productID and name with provided values.
// Parameters:
//   - productID: Pointer to a character array containing the product ID (input)
//   - name: Pointer to a character array containing the product name (input)
    strncpy(this->productID, productID, sizeof(this->productID) - 1);
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->productID[sizeof(this->productID) - 1] = '\0';
    this->name[sizeof(this->name) - 1] = '\0';
}

// Copy constructor
//----------------------
Product::Product (const Product& other) {
    strncpy(this->productID, other.productID, sizeof(this->productID) - 1);
    strncpy(this->name, other.name, sizeof(this->name) - 1);
    this->productID[sizeof(this->productID) - 1] = '\0';
    this->name[sizeof(this->name) - 1] = '\0';
}

// Assignment operator
//----------------------
Product& Product::operator= (const Product& other) {
    if (this != &other) {
        strncpy(this->productID, other.productID, sizeof(this->productID) - 1);
        strncpy(this->name, other.name, sizeof(this->name) - 1);
        this->productID[sizeof(this->productID) - 1] = '\0';
        this->name[sizeof(this->name) - 1] = '\0';
    }
    return *this;
}

// Getter methods
//----------------------
const char* Product::getProductID () const {
// Retrieves the product ID.
    return productID;
}

//----------------------
const char* Product::getName () const {
// Retrieves the product name.
    return name;
}


// Setter methods
//----------------------
void Product::setProductID (const char* productID) {
// Sets the product ID.
// Parameters:
//   - productID: Pointer to a character array containing the product ID (input)
    strncpy(this->productID, productID, sizeof(this->productID) - 1);
    this->productID[sizeof(this->productID) - 1] = '\0';
}

//----------------------
void Product::setName (const char* name) {
// Sets the product name.
// Parameters:
//   - name: Pointer to a character array containing the product name (input)
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0';
}

//----------------------
// Utility methods
Product& Product::checkProductExists (const char* productIDToFind) {
// Description: Checks if a product with the given Product ID exists in a file.
// Parameters:
//   - productIDToFind: Pointer to a character array containing the Product ID to search for (input)
// Returns:
//   - Reference to the Product object if the product with the given Product ID exists in the file.
// Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.
    file.seekg(0, ios::beg);
    while (file.read(reinterpret_cast<char*>(this), sizeof(Product))) {
        if (strcmp(this->productID, productIDToFind) == 0) {
            return *this;
        }
    }
    throw runtime_error("Product not found");
}

//----------------------
bool Product::addProduct () {
// Description: Creates a product and adds it to the file.
// Returns:
//   - true if the product is successfully added to the file, false otherwise.
// Exceptions: May throw an exception if the file specified by fileName does not exist or cannot be accessed.
    file.seekp(0, ios::end);
    file.write(reinterpret_cast<const char*>(this), sizeof(Product));
    return file.good();
}

//----------------------
Product Product::displayProductFromFile () const {
// Description: Displays and returns a product from the file.
// Parameters: None (no parameters).
// Returns: A Product object that matches the criteria.
// Exceptions: May throw an exception if the file cannot be accessed.
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
//----------------------
void Product::initProduct (const char* fileName) {
// Description: Initializes the obj with default constructor and opens the specified file for operations
// Parameters:
//   - fileName: Pointer to a character array containing the file name (input)
    this->fileName = fileName;
    file.open(fileName, ios::in | ios::out | ios::binary);
    if (!file) {
        throw runtime_error("Error: Could not open file");
    }
}

//----------------------
void Product::closeProduct () {
// Description: Deletes the Object and frees any memory allocated on the heap.
    file.close();
}
