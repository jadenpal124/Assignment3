#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include <iostream>
#include <cstring>
#include "User.h"
#include "Product.h"
#include "changeItem.h"
#include "Release.h"

using namespace std;

class changeRequest {
public:
    // Constructors
    changeRequest();
    changeRequest(const changeItem& changeItem, const User& user, const Release* associatedRelease);

    // Getter methods
    const Product& getProduct() const;
    const User& getUser() const;
    const changeItem& getChangeItem() const;
    const Release* getAssociatedRelease() const;

    // Setter methods
    void setProduct(const Product& product);
    void setUser(const User& user);
    void setChangeItem(const changeItem& changeItem);
    void setAssociatedRelease(const Release* associatedRelease);

    // Utility methods
    bool addChangeRequest(const char* fileName);

private:
    User user; //*
    Product product; 
    changeItem ChangeItem; //*
    const Release* associatedRelease;
    char dateRequested[11];
};

#endif // CHANGEREQUEST_H
