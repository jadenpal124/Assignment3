#include "Product.h"

Product::Product () : productID (""), name ("") {
  
}

Product::Product (const char* productID, const char* name) {
    strncpy (this->productID, productID, sizeof (this->productID) - 1);
    strncpy (this->name, name, sizeof (this->name) - 1);
}

const char* Product::getProductID () const {
    return productID;
}

const char* Product::getName () const {
    return name;
}

void Product::setProductID (const char* productID) {
    strncpy(this->productID, productID, sizeof (this->productID) - 1);
}

void Product::setName (const char* name) {
    strncpy(this->name, name, sizeof (this->name) - 1);
}

bool Product::addProduct(const char* fileName) {
    // to be implemented
    return true;
}

Product& Product::checkUserExists(const char* fileName, const char* productIDToFind) {
    // to be implemented
    return *this;
}

void Product::initProduct () {

}

void Product::closeProduct () {

}
