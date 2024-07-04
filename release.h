#ifndef RELEASE_H
#define RELEASE_H

#include <iostream>
#include <cstring> // For string manipulation functions
#include "product.h" // Include Product class header

using namespace std;

class Release {
public:
    // Constructors
    Release(); // Default constructor
    Release(const char* releaseID, const Product& product, const char* releaseDate); // Parameterized constructor

    // Getter methods
    const char* getReleaseID() const;
    const Product& getProduct() const;
    const char* getReleaseDate() const;

    // Setter methods
    void setReleaseID(const char* releaseID);
    void setProduct(const Product& product);
    void setReleaseDate(const char* releaseDate);

    // Utility methods
    bool checkReleaseExists(const char* fileName, const char* releaseIDToFind); // Check if release exists in file
    bool addRelease(const char* fileName); // Add release to file
    const char* searchRelease(const char* fileName, const char* releaseIDToFind); // Search for release in file

    private:
    char releaseID[8];
    Product product; // Product object to reference Product class
    char releaseDate[11]; // Assuming release date format YYYY-MM-DD
};

#endif // RELEASE_H
