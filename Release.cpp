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
fstream Release::file;
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
// Copy assignment operator assigns the values from another Release object to this object.
// Parameters:
//   - other: Reference to another Release object to copy from (input)
// Returns:
//   - A reference to the assigned Release object (output)
    if (this != &other) {

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
bool Release::addRelease() {
    // Description: Adds the release's details to the currently managed file.
    // Returns:
    //   true if the release details were successfully added; false otherwise.

    if (!file.is_open()) {
        return false;
    }

    file.seekp(0, std::ios::end); // Move to end to append
    if (!file.good()) {
        return false;
    }

    file.write(reinterpret_cast<const char*>(this), sizeof(Release));
    if (!file.good()) {
        return false;
    }

    file.flush();
    file.clear();
    return true;
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
Release Release::findReleaseAndReturn (const Product prod) {
    // Description: Searches for a release with the specified releaseID and associated productID, and returns it.
    // Parameters:
    //   - releaseIDToFind: Pointer to a character array containing the release ID to search for (input)
    //   - prod: Pointer to a character array containing the product ID to match (input)
    // Returns:
    //   The Release object matching the specified criteria.
    // Exceptions:
    //   Throws an exception if the release is not found.
    const int numRecordsPerPage = 5; // Number of records to display per page
    int startRecord = 0; // Starting record index
    bool displayNextPage = true;
    Release selectedRel; // To store the selected release
    bool releaseSelected = false; // Flag to track if a release was selected

    // Display table items loop
    while (displayNextPage) {
        // Display header
        std::cout << "Release List for Product ID: " << prod.getProductID() << std::endl;
        std::cout << "Page " << (startRecord / numRecordsPerPage + 1) << std::endl;
        std::cout << std::setw(2) << "#" << "  ";
        std::cout << std::setw(15) << "Release ID" << "  ";
        std::cout << std::setw(12) << "Release Date" << endl;
        std::cout << std::setw(2) << "--" << "  ";
        std::cout << std::setw(15) << "-----------" << "  ";
        std::cout << std::setw(12) << "------------" << endl;

        // Display records
        bool endOfFile = false;
        int displayedCount = 0;
        file.clear();
        file.seekg(startRecord * sizeof(Release), std::ios::beg);

        for (int i = 0; i < numRecordsPerPage; ++i) {
            Release release;
            if (!file.read(reinterpret_cast<char*>(&release), sizeof(Release))) {
                endOfFile = true; // End of file
                break;
            }
            if (strcmp(release.getProduct().getProductID(), prod.getProductID()) == 0) {
                std::cout << std::setw(2) << (startRecord + i + 1) << "  ";
                std::cout << std::setw(15) << release.getReleaseID() << "  ";
                std::cout << std::setw(12) << release.getReleaseDate() << endl;
           
                ++displayedCount;
            }
        }

        // Prompt user for input
        if (!endOfFile) {
            std::cout << std::endl;
            std::cout << "Press <enter> to display the next " << numRecordsPerPage << " rows, or \"q\" to go back." << std::endl;
            std::cout << "If you would like to select a release, type the number #." << std::endl;
            std::cout << "If a Release ID is known, type \"s\" to enter it." << std::endl;

            std::string selection;
            std::cout << "Enter Selection: ";
            std::getline(std::cin, selection);

            // Handle user input
            if (selection.empty()) {
                // Default action: Display next page
                startRecord += numRecordsPerPage;
            } else if (selection == "q") {
                // Quit action
                displayNextPage = false; // Exit loop
            } else if (selection == "s") {
                // Enter Release ID action
                std::cout << "Enter Release ID: ";
                std::string releaseID;
                std::getline(std::cin, releaseID);
                file.clear();
                file.seekg(0, std::ios::beg); // Move file pointer to beginning
                bool found = false;
                Release release;
                while (file.read(reinterpret_cast<char*>(&release), sizeof(Release))) {
                    if (strcmp(release.getReleaseID(), releaseID.c_str()) == 0 && strcmp(release.getProduct().getProductID(), prod.getProductID()) == 0) {
                        selectedRel = release;
                        found = true;
                        releaseSelected = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Release ID not found." << std::endl;
                } else {
                    displayNextPage = false; // Exit loop if release is found
                }
            } else if (isdigit(selection[0])) {
                // Select by number action
                int selectedNumber = std::stoi(selection);
                file.clear();
                file.seekg((startRecord + selectedNumber - 1) * sizeof(Release), std::ios::beg);
                Release release;
                if (file.read(reinterpret_cast<char*>(&release), sizeof(Release))) {
                    selectedRel = release;
                    releaseSelected = true;
                    displayNextPage = false; // Exit loop if release is selected
                } else {
                    std::cout << "Invalid selection." << std::endl;
                }
            } else {
                std::cout << "Invalid selection." << std::endl;
            }
        } else {
            // End of file reached
            std::cout << "End of file reached. Press 'q' to go back." << std::endl;
            std::cout << "If you would like to select a release, type the number #." << std::endl;
            std::cout << "If a Release ID is known, type \"s\" to enter it." << std::endl;

            std::string selection;
            std::cout << "Enter Selection: ";
            std::getline(std::cin, selection);

            if (selection == "q") {
                displayNextPage = false; // Exit loop
            } else if (selection == "s") {
                // Enter Release ID action
                std::cout << "Enter Release ID: ";
                std::string releaseID;
                std::getline(std::cin, releaseID);
                file.clear();
                file.seekg(0, std::ios::beg); // Move file pointer to beginning
                bool found = false;
                Release release;
                // Read items from file loop
                while (file.read(reinterpret_cast<char*>(&release), sizeof(Release))) {
                    if (strcmp(release.getReleaseID(), releaseID.c_str()) == 0 && strcmp(release.getProduct().getProductID(), prod.getProductID()) == 0) {
                        selectedRel = release;
                        found = true;
                        releaseSelected = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Release ID not found." << std::endl;
                } else {
                    displayNextPage = false; // Exit loop if release is found
                }
            } else if (isdigit(selection[0])) {
                // Select by number action
                int selectedNumber = std::stoi(selection);
                if (selectedNumber > 0 && selectedNumber <= numRecordsPerPage) {
                    file.clear();
                    file.seekg((startRecord + selectedNumber - 1) * sizeof(Release), std::ios::beg);
                    Release release;
                    if (file.read(reinterpret_cast<char*>(&release), sizeof(Release))) {
                        selectedRel = release;
                        releaseSelected = true;
                        displayNextPage = false; // Exit loop if release is selected
                    } else {
                        std::cout << "Invalid selection." << std::endl;
                    }
                } else {
                    std::cout << "Invalid selection." << std::endl;
                }
            } else {
                std::cout << "Invalid selection." << std::endl;
            }
        }
    }
    return selectedRel; // Return the selected release
}

//----------------------
void Release::initRelease (const char* fileName) {
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
