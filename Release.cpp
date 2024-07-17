#include "Release.h"

Release::Release () : releaseID (""), product (), releaseDate ("") {
  
}

Release::Release (const char* releaseID, const Product& product, const char* releaseDate) : product (product) {
    strncpy (this->releaseID, releaseID, sizeof (this->releaseID) - 1);
    strncpy (this->releaseDate, releaseDate, sizeof (this->releaseDate) - 1);
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
}

void Release::setProduct (const Product& product) {
    this->product = product;
}

void Release::setReleaseDate (const char* releaseDate) {
    strncpy (this->releaseDate, releaseDate, sizeof (this->releaseDate) - 1);
}

bool Release::addRelease (const char* fileName) {
    // to be implemented
    return true;
}

bool Release::checkRelease (const char* fileName, const char* releaseIDToFind) {
    // to be implemented
    return true;
}

void Release::initRelease () {

}

void Release::closeRelease () {

}
