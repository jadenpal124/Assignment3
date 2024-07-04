#ifndef CHANGEREQUEST_H
#define CHANGEREQUEST_H

#include <iostream>
#include <cstring>
#include "user.h"
#include "product.h"
#include "changeItem.h"

using namespace std;

class changeRequest {
public:
    // Constructors
    changeRequest();
    changeRequest(const char* changeRequestID, const changeItem& changeItem, const User& user); 

    // Getter methods
    const char* getChangeRequestID() const;
    const Product& getProduct() const;
    const User& getUser() const;
    const changeItem& getChangeItem() const;

    // Setter methods
    void setUser(const User& user);
    void setProduct(const Product& product);
    void setChangeItem(const changeItem& ChangeItem);

    // Utility methods
    bool addChangeRequest(const char* fileName);

    private:
    char changeRequestID[8];
    User user;
    Product product;
    changeItem ChangeItem;
};

#endif // CHANGEREQUEST_H
