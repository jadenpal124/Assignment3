#include "changeRequest.h" 

changeRequest::changeRequest () {
    initChangeRequest ();
}

changeRequest (const changeItem& changeItem, const User& user, const Product& product, const Release* associatedRelease) {
    setChangeItem (changeItem);
    setUser (user);
    setProduct (product);
    setAssociatedRelease (associatedRelease);
}

const changeRequest::getProduct () const {
    return product;
}


const changeRequest::getUser () const {
    return user;
}


const changeRequest::getChangeItem () const {
    return ChangeItem ;
}


const changeRequest::getAssociatedRelease () const {
    return associatedRelease;
}


void changeRequest::setProduct (const Product& product) {
    this->product = product;
}

void changeRequest::setUser (const User& user) {
    this->user = user;
}


void changeRequest::setChangeItem (const changeItem& changeItem) {
    this->ChangeItem = changeItem;
}


void changeRequest::setAssociatedRelease (const Release& associatedRelease) {
    this->associatedRelease = associatedRelease;
}

bool changeRequest::addChangeRequest (const char* fileName) {
    ofstream writeFile(fileName, ios::binary | ios::app);
    if (!writeFile) {
        cerr << "Error: Could not open file " << fileName << endl;
        return false;
    }
    writeFile.write(reinterpret_cast<const char*>(this), sizeof(changeRequest));
    writeFile.close();
    return true;

}

void changeRequest::initChangeRequest () {
    memset(user, null, sizeof(user));
    memset(product, null, sizeof(product));
    memset(changeItem, null, sizeof(changeItem));
    memset(associatedRelease, null, sizeof(associatedRelease));

}

void changeRequest::closeChangeRequest () {};

