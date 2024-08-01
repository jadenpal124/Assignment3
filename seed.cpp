// Command: g++ seed.cpp User.cpp Product.cpp Release.cpp changeRequest.cpp changeItem.cpp -o seed -std=c++11 && ./seed

#include <iostream>
#include <fstream>
#include <cstring>
#include "User.h"
#include "Product.h"
#include "Release.h"
#include "changeRequest.h"
#include "changeItem.h"

using namespace std;


void seedData(const char* productFile, const char* releaseFile, const char* userFile, const char* changeRequestFile, const char* changeItemFile) {

    User userTmp;
    Product prodTmp;
    Release relTmp;
    changeRequest chRTmp;
    changeItem chItemTmp;

    // Initialize files
    userTmp.initUser(userFile);
    prodTmp.initProduct(productFile);
    relTmp.initRelease(releaseFile);
    chRTmp.initChReq(changeRequestFile);
    chItemTmp.initChangeItem(changeItemFile);

    // Create users
    User users[20] = {
        User("user01", "Alice Smith", "123-456-7890", "alice.smith@example.com", "HR"),
        User("user02", "Bob Johnson", "234-567-8901", "bob.johnson@example.com", "IT"),
        User("user03", "Charlie Brown", "345-678-9012", "charlie.brown@example.com", "Finance"),
        User("user04", "David Wilson", "456-789-0123", "david.wilson@example.com", "Marketing"),
        User("user05", "Emma Davis", "567-890-1234", "emma.davis@example.com", ""),
        User("user06", "Frank Miller", "678-901-2345", "frank.miller@example.com", ""),
        User("user07", "Grace Lee", "789-012-3456", "grace.lee@example.com", "Sales"),
        User("user08", "Henry Clark", "890-123-4567", "henry.clark@example.com", "HR"),
        User("user09", "Ivy Lewis", "901-234-5678", "ivy.lewis@example.com", ""),
        User("user10", "Jack Walker", "012-345-6789", "jack.walker@example.com", "IT"),
        User("user11", "Karen Hall", "123-456-0000", "karen.hall@example.com", ""),
        User("user12", "Larry Allen", "234-567-1111", "larry.allen@example.com", "Finance"),
        User("user13", "Mona Young", "345-678-2222", "mona.young@example.com", ""),
        User("user14", "Nina King", "456-789-3333", "nina.king@example.com", "Marketing"),
        User("user15", "Oscar Scott", "567-890-4444", "oscar.scott@example.com", ""),
        User("user16", "Paul Wright", "678-901-5555", "paul.wright@example.com", "Sales"),
        User("user17", "Quinn Adams", "789-012-6666", "quinn.adams@example.com", ""),
        User("user18", "Rachel Hill", "890-123-7777", "rachel.hill@example.com", "HR"),
        User("user19", "Steve Green", "901-234-8888", "steve.green@example.com", ""),
        User("user20", "Tina Baker", "012-345-9999", "tina.baker@example.com", "IT")
    };

    // Initialize users and add to file
    User user;
    for (int i = 0; i < 20; ++i) {
        users[i].addUser();
    }
    user.closeUser();

    // Create products
    Product products[20];
    const char* productNames[] = {
        "Prod1", "Prod2", "Prod3", "Prod4", "Prod5", "Prod6", "Prod7", "Prod8", "Prod9", "Prod10",
        "Prod11", "Prod12", "Prod13", "Prod14", "Prod15", "Prod16", "Prod17", "Prod18", "Prod19", "Prod4WinOS"
    };

     const char* productIDs[] = {
        "Prod1ID", "Prod2ID", "Prod3ID", "Prod4ID", "Prod5ID", "Prod6ID", "Prod7ID", "Prod8ID", "Prod9ID", "Prod10ID",
        "Prod11ID", "Prod12ID", "Prod13ID", "Prod14ID", "Prod15ID", "Prod16ID", "Prod17ID", "Prod18ID", "Prod19ID", "Prod4WinOSID"
    };

    // Initialize products and add to file
    for (int i = 0; i < 20; ++i) {
        products[i].setName(productNames[i]);
        products[i].setProductID(productIDs[i]);
        products[i].addProduct();
    }

    // Create releases for Prod1
    Release releasesForProd1[20];
    for (int i = 1; i <= 20; ++i) {
        char releaseID[10];
        snprintf(releaseID, sizeof(releaseID), "rel.1.%02d", i);
        releasesForProd1[i-1] = Release(releaseID, products[0], releaseID);
        releasesForProd1[i-1].addRelease();
    }

    // Create releases for Prod4WinOS
    Release releasesForProd4WinOS[2];
    releasesForProd4WinOS[0] = Release("rel.4.01", products[19], "2024-04-01");
    releasesForProd4WinOS[1] = Release("rel.4.02", products[19], "2024-04-02");
    releasesForProd4WinOS[0].addRelease();
    releasesForProd4WinOS[1].addRelease();

    // Create one change item
    changeItem changeItem, newChangeItem;
    changeItem.setAssociatedProduct(products[0]);
    changeItem.setStatus("InProgress");

    relTmp.setProduct(products[0]);
    relTmp.setReleaseDate("2024/07/29");
    relTmp.setReleaseID("rel.1.20");
    relTmp.addRelease();

    cout << changeItem.getStatusAsString() << endl;
    changeItem.setDescription("MyItemDescription");
    changeItem.setAnticipatedRelease(relTmp);
    cout << changeItem.addChangeItem() << endl;

    // Create change requests
    changeRequest request;

    for (int i = 0; i < 20; ++i) {
        changeRequest req;
        req.setChangeItem(changeItem);  // Use the single change item
        req.setAssociatedRelease(releasesForProd1[i]);
        req.setDateRequested("2024-07-31");
        req.setUser(users[i % 20]); // Assign a user from the array
        req.addChangeRequest();
    }

    relTmp.setProduct(products[19]);
    relTmp.setReleaseDate("2024/07/29");
    relTmp.setReleaseID("rel.4.03");
    relTmp.addRelease();

    // Update the status of the change item to "Done" with final release "rel.4.01"
    newChangeItem.setStatus("Done");
    newChangeItem.setAssociatedProduct(products[19]);
    newChangeItem.setDescription("123456789012345678901234567890");
    newChangeItem.setAnticipatedRelease(relTmp);
    newChangeItem.addChangeItem();
    
    for (int i = 0; i < 2; ++i) {
        changeRequest req;
        req.setChangeItem(newChangeItem);  // Use the newly created change item
        req.setAssociatedRelease(releasesForProd4WinOS[i]);
        req.setDateRequested("2024-07-31");
        req.setUser(users[i]); // Assign a user from the array
        req.addChangeRequest();

        cout << req.getChangeItem().getChangeItemID() << endl;
        cout << req.getChangeItem().getStatusAsString() << endl;
    }

    
}

int main() {
    try {
        seedData("products.dat", "releases.dat", "users.dat", "changeRequests.dat", "changeItems.dat");
        cout << "Seed data added successfully." << endl;
    } catch (const exception& e) {
        cerr << "Error seeding data: " << e.what() << endl;
    }
    return 0;
}
