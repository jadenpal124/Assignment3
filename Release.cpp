/* Revision History:
   Rev. 1 - 04/15/24 Original by JAWS */
//==================================================
/* This module implements the Release class, which encapsulates data related to a release.
   The class provides methods to access, modify, and manage release information,
   including functionalities to add, check, and find releases in a file. The class
   uses a single file stream for efficient file operations. */
//==================================================

#include "Release.h"

//==================================================

// Default constructor
//----------------------
Release::Release () {
    // Description: Default constructor initializing a Release object with default values.
}

// Parameterized constructor
//----------------------
Release::Release (const char* releaseID, const Product& product, const char* releaseDate) : product(product) {
    // Description: Parameterized constructor initializing releaseID, product, and releaseDate with provided values.
    // Parameters:
    //   - releaseID: Pointer to a character array containing the release ID (input)
    //   - product: Product object representing the associated product (input)
    //   - releaseDate: Pointer to a character array containing the release date (input)
    setReleaseID(releaseID);
    setProduct(product);
    setReleaseDate(releaseDate);
}

// Copy constructor
//----------------------
Release::Release (const Release& other) {
    // Description: Copy constructor initializing a Release object with values from another Release object.
    // Parameters:
    //   - other: Another Release object to copy from (input)

    // Copy releaseID with null-termination
    strncpy(this->releaseID, other.releaseID, sizeof(this->releaseID) - 1);
    this->releaseID[sizeof(this->releaseID) - 1] = '\0';

    // Copy the Product object
    this->product = other.product;

    // Copy releaseDate with null-termination
    strncpy(this->releaseDate, other.releaseDate, sizeof(this->releaseDate) - 1);
    this->releaseDate[sizeof(this->releaseDate) - 1] = '\0';
}

// Overloaded assignment operator
//----------------------
Release& Release::operator= (const Release& other) {
    if (this != &other) {
        // Description: Assignment operator to assign values from another Release object.
        // Parameters:
        //   - other: Another Release object to assign from (input)

        // Copy releaseID with null-termination
        strncpy(this->releaseID, other.releaseID, sizeof(this->releaseID) - 1);
        this->releaseID[sizeof(this->releaseID) - 1] = '\0';

        // Assign Product object using Product's assignment operator
        this->product = other.product;

        // Copy releaseDate with null-termination
        strncpy(this->releaseDate, other.releaseDate, sizeof(this->releaseDate) - 1);
        this->releaseDate[sizeof(this->releaseDate) - 1] = '\0';
    }
    return *this;
}

// Getter methods
//----------------------
const char* Release::getReleaseID () const {
    // Description: Getter for retrieving release ID
    // Parameters: None
    // Returns: Pointer to a constant character array containing the release ID
    return releaseID;
}

//----------------------
const Product Release::getProduct () const {
    // Description: Getter for retrieving the associated Product object
    // Parameters: None
    // Returns: Product object representing the associated product
    return product;
}

//----------------------
const char* Release::getReleaseDate () const {
    // Description: Getter for retrieving release date
    // Parameters: None
    // Returns: Pointer to a constant character array containing the release date
    return releaseDate;
}

// Setter methods
//----------------------
void Release::setReleaseID (const char* releaseID) {
    // Description: Setter for setting release ID
    // Parameters:
    //   - releaseID: Pointer to a character array containing the release ID (input)
    strncpy(this->releaseID, releaseID, sizeof(this->releaseID) - 1);
    this->releaseID[sizeof(this->releaseID) - 1] = '\0'; // Ensure null-termination
}

//----------------------
void Release::setProduct (const Product& newProduct) {
    // Description: Setter for setting the associated Product object
    // Parameters:
    //   - newProduct: Product object representing the associated product (input)
    product = newProduct;
}

//----------------------
void Release::setReleaseDate (const char* releaseDate) {
    // Description: Setter for setting release date
    // Parameters:
    //   - releaseDate: Pointer to a character array containing the release date (input)
    strncpy(this->releaseDate, releaseDate, sizeof(this->releaseDate) - 1);
    this->releaseDate[sizeof(this->releaseDate) - 1] = '\0'; // Ensure null-termination
}

// Utility methods
//----------------------
bool Release::addRelease () {
    // Description: Adds the release's details to the currently managed file.
    // Returns:
    //   true if the release details were successfully added; false otherwise.
    // Exceptions:
    //   May throw an exception if the file cannot be accessed.
    file.seekp(0, std::ios::end); // Move to end to append
    file.write(reinterpret_cast<const char*>(this), sizeof(Release));
    return file.good();
}

//----------------------
bool Release::checkRelease (const char* releaseIDToFind) {
    // Description: Checks if a release with the specified releaseID exists in the file.
    // Parameters:
    //   - releaseIDToFind: Pointer to a character array containing the release ID to search for (input)
    // Returns:
    //   true if the release is found; false otherwise.
    // Exceptions:
    //   Throws an exception if the release is not found.
    file.clear();
    file.seekg(0, std::ios::beg);

    static Release release; // Static to ensure it persists after function ends
    bool found = false;

    // Search for the release by releaseID
    while (file.read(reinterpret_cast<char*>(&release), sizeof(Release))) {
        if (std::strcmp(release.releaseID, releaseIDToFind) == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        std::cerr << "Error: Release with ID " << releaseIDToFind << " not found." << std::endl;
        throw std::exception(); // Throwing exception if release not found
    }

    return found;
}

//----------------------
Release Release::findReleaseAndReturn (const char* releaseIDToFind, const char* productIDToFind) {
    // Description: Searches for a release with the specified releaseID and associated productID, and returns it.
    // Parameters:
    //   - releaseIDToFind: Pointer to a character array containing the release ID to search for (input)
    //   - productIDToFind: Pointer to a character array containing the product ID to match (input)
    // Returns:
    //   The Release object matching the specified criteria.
    // Exceptions:
    //   Throws an exception if the release is not found.
    file.clear();
    file.seekg(0, std::ios::beg);

    static Release release; // Static to ensure it persists after function ends
    bool found = false;
    Product tempProduct;

    // Search for the release by releaseID and associated productID
    while (file.read(reinterpret_cast<char*>(&release), sizeof(Release))) {
        tempProduct = release.getProduct();
        if (std::strcmp(release.getReleaseID(), releaseIDToFind) == 0 && std::strcmp(tempProduct.getProductID(), productIDToFind) == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        std::cerr << "Error: Release with ID " << releaseIDToFind << " not found." << std::endl;
        throw std::exception(); // Throwing exception if release not found
    }

    return release;
}

//----------------------
void Release::initRelease(const char* fileName) {
    // Description: Initializes the Release object and opens the file for operations.
    // Parameters:
    //   - fileName: Pointer to a character array containing the file name (input)
    
    // Attempt to open the file for reading and writing in binary mode
    file.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
    
    if (!file.is_open()) {
        // File does not exist or could not be opened; attempt to create it
        file.clear(); // Clear any error state
        file.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc); // Create a new file
        if (!file) {
            throw std::runtime_error("Error: Could not open or create file");
        }
        file.close(); // Close the file and reopen in the required mode
        file.open(fileName, std::ios::in | std::ios::out | std::ios::binary);
    }

    if (!file) {
        throw std::runtime_error("Error: Could not open file after creation attempt");
    }
}

//----------------------
void Release::closeRelease () {
    // Description: Closes the file and performs any necessary cleanup.
    // Parameters: None
    if (file.is_open()) {
        file.close();
    }
}
