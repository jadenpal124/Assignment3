#ifndef changeItem_H
#define changeItem_H

#include <iostream>
#include <cstring>

using namespace std;

class changeItem {

public:
    // Constructors
    changeItem(); // Default constructor
    changeItem(const int ChangeItemID, const char* description, const char* releaseID);

    // Getter methods
    const int getChangeItemID() const;
    const char* getDescription() const;
    const char* getReleaseID() const;

    // Setter methods
    void setChangeItemID(const int changeItemID);
    void setDescription(const char* description);
    void setReleaseID(const char* releaseID);

    // Utility methods
    bool checkChangeItemIDExists(const char* fileName, const int changeItemIDToFind);
    bool addChangeItem(const char* fileName);
    const int searchChangeItemID(const char* fileName, const int changeItemIDToFind);

private:
    int changeItemID;
    char description[100]; // Req Spec Inconsistence
    char releaseID[8];
};

#endif // changeItem_H
