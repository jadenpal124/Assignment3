#include "Release.h"

Release::Release () {
    initRelease();
}

Release::Release (const char* releaseID, const Product& product, const char* releaseDate) : product (product) {
    initRelease(); // Initialize object upon startup
    setReleaseID(releaseID);
    setProduct(product);
    setReleaseDate(releaseDate);
}

const char* Release::getReleaseID () const {
    return releaseID;
}

const Product& Release::getProduct () const {
    return product;
}

const char* Release::getReleaseDate () const {
    return releaseDate;
}

void Release::setReleaseID (const char* releaseID) {
    strncpy (this->releaseID, releaseID, sizeof (this->releaseID) - 1);
    this->releaseID[sizeof(this->releaseID) - 1] = '\0'; // Ensure null-termination
}

void Release::setProduct (const Product& product) {
    this->product = product;
    this->product[sizeof(this->product) - 1] = '\0'; // Ensure null-termination
}

void Release::setReleaseDate (const char* releaseDate) {
    strncpy (this->releaseDate, releaseDate, sizeof (this->releaseDate) - 1);
    this->releaseDate[sizeof(this->releaseDate) - 1] = '\0'; // Ensure null-termination
}

bool Release::addRelease (const char* fileName) {
    ofstream outFile(fileName, ios::binary | ios::app);
    if (!outFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }

    // Write release information to file
    outFile.write(reinterpret_cast<const char*>(this), sizeof(Release));
    outFile.close();
    return true;
}

bool Release::checkRelease (const char* fileName, const char* releaseIDToFind) {
    ifstream inFile(fileName, ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        throw exception(); // Throwing exception if file cannot be opened
    }

    static Release release; // Static to ensure it persists after function ends
    bool found = false;

    // Search for the release by releaseID
    while (inFile.read(reinterpret_cast<char*>(&release), sizeof(Release))) {
        if (strcmp(release.releaseID, releaseID) == 0) {
            found = true;
            break;
        }
    }

    inFile.close();

    if (!found) {
        cerr << "Error: Release with ID " << releaseID << " not found." << endl;
        throw exception(); // Throwing exception if release not found
    }

    return found;
}

void Release::initRelease () {
    // Initialize object upon startup
    memset(releaseID, 0, sizeof(releaseID));
    memset(product, 0, sizeof(Product));
    memset(releaseDate, 0, sizeof(releaseDate));
}

void Release::closeRelease () {

}
