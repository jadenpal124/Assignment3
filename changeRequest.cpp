
#include "changeRequest.h" 

changeRequest::changeRequest () {
    initChangeRequest ();
}

changeRequest::changeRequest (const changeItem& changeItem, const User& user, const Product& product, const Release& associatedRelease) {
    setChangeItem (changeItem);
    setUser (user);
    setProduct (product);
    setAssociatedRelease (associatedRelease);
}

const Product &changeRequest::getProduct () const {
    return product;
}


const User &changeRequest::getUser () const {
    return user;
}


const changeItem &changeRequest::getChangeItem () const {
    return ChangeItem ;
}


const Release &changeRequest::getAssociatedRelease () const {
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
    memset(user, 0, sizeof(user));
    memset(product, 0, sizeof(product));
    memset(ChangeItem, 0, sizeof(changeItem));
    memset(associatedRelease, 0, sizeof(associatedRelease));

}

void changeRequest::closeChangeRequest () {};
