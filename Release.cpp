#include "Release.h"

Release::Release() {
    // Default constructor body (can be empty)
}

Release::Release(const char* releaseID, const Product& product, const char* releaseDate) : product(product) {
    setReleaseID(releaseID);
    setProduct(product);
    setReleaseDate(releaseDate);
}

// Copy constructor
Release::Release(const Release& other) {
    // Copy releaseID with null-termination
    strncpy(this->releaseID, other.releaseID, sizeof(this->releaseID) - 1);
    this->releaseID[sizeof(this->releaseID) - 1] = '\0';

    // Copy the Product object
    this->product = other.product;

    // Copy releaseDate with null-termination
    strncpy(this->releaseDate, other.releaseDate, sizeof(this->releaseDate) - 1);
    this->releaseDate[sizeof(this->releaseDate) - 1] = '\0';
}

// Overloaded= operator
Release& Release::operator=(const Release& other) {
    if (this != &other) {
        strncpy(this->releaseID, other.releaseID, sizeof(this->releaseID) - 1);
        this->releaseID[sizeof(this->releaseID) - 1] = '\0';

        this->product = other.product; // Use Product's assignment operator

        strncpy(this->releaseDate, other.releaseDate, sizeof(this->releaseDate) - 1);
        this->releaseDate[sizeof(this->releaseDate) - 1] = '\0';
    }
    return *this;
}

const char* Release::getReleaseID() const {
    return releaseID;
}

const Product Release::getProduct() const {
    return product;
}

const char* Release::getReleaseDate() const {
    return releaseDate;
}

void Release::setReleaseID(const char* releaseID) {
    strncpy(this->releaseID, releaseID, sizeof(this->releaseID) - 1);
    this->releaseID[sizeof(this->releaseID) - 1] = '\0'; // Ensure null-termination
}

void Release::setProduct(const Product& newProduct) {
    product = newProduct;
}

void Release::setReleaseDate(const char* releaseDate) {
    strncpy(this->releaseDate, releaseDate, sizeof(this->releaseDate) - 1);
    this->releaseDate[sizeof(this->releaseDate) - 1] = '\0'; // Ensure null-termination
}

bool Release::addRelease() {
    file.seekp(0, ios::end);
    file.write(reinterpret_cast<const char*>(this), sizeof(Release));
    return file.good();
}

bool Release::checkRelease(const char* releaseIDToFind) {
    file.clear();
    file.seekg(0, ios::beg);

    static Release release; // Static to ensure it persists after function ends
    bool found = false;

    // Search for the release by releaseID
    while (file.read(reinterpret_cast<char*>(&release), sizeof(Release))) {
        if (strcmp(release.releaseID, releaseIDToFind) == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        cerr << "Error: Release with ID " << releaseIDToFind << " not found." << endl;
        throw exception(); // Throwing exception if release not found
    }

    return found;
}

Release Release::findReleaseAndReturn(const char* releaseIDToFind, const char* productIDToFind) {
    file.clear();
    file.seekg(0, ios::beg);

    static Release release; // Static to ensure it persists after function ends
    bool found = false;
    Product tempProduct;

    // Search for the release by releaseID
    while (file.read(reinterpret_cast<char*>(&release), sizeof(Release))) {
        tempProduct = release.getProduct();
        if (strcmp(release.getReleaseID(), releaseIDToFind) == 0 && strcmp(tempProduct.getProductID(), productIDToFind) == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        cerr << "Error: Release with ID " << releaseIDToFind << " not found." << endl;
        throw exception(); // Throwing exception if release not found
    }

    return release;
}

void Release::initRelease(const char* fileName) {
    this->fileName = fileName;
    file.open(fileName, ios::in | ios::out | ios::binary);
    if (!file) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw runtime_error("File opening failed");
    }
}

void Release::closeRelease() {
    if (file.is_open()) {
        file.close();
    }
}
