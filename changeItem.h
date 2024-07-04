#ifndef CHANGEITEM_H
#define CHANGEITEM_H

#include <iostream>
#include <cstring>
#include "Release.h" // Include Release class header

using namespace std;

class changeItem {
public:
    // Enum for status
    enum Status {
        Cancelled,
        NewRequest,
        ReviewRequest,
        InProgress,
        Done
    };

    // Constructors
    changeItem(); // Default constructor
    changeItem(int changeItemID, const char* description, const char* releaseID, const char* anticipatedReleaseID, const Release* releasePtr);

    // Getter methods
    int getChangeItemID() const;
    const char* getDescription() const;
    const char* getReleaseID() const;
    const char* getAnticipatedReleaseID() const; // Getter for anticipatedReleaseID
    Status getStatus() const; // Getter for status
    const Release* getAssociatedRelease() const; // Getter for associated Release

    // Setter methods
    void setChangeItemID(int changeItemID);
    void setDescription(const char* description);
    void setReleaseID(const char* releaseID);
    void setAnticipatedReleaseID(const char* anticipatedReleaseID); // Setter for anticipatedReleaseID
    void setStatus(Status status); // Setter for status
    void setAssociatedRelease(const Release* releasePtr); // Setter for associated Release

    // Utility methods
    bool checkChangeItemIDExists(const char* fileName, int changeItemIDToFind);
    bool addChangeItem(const char* fileName);
    int searchChangeItemID(const char* fileName, int changeItemIDToFind);
    

private:
    int changeItemID; //integer from [0, 999 999]
    char description[100]; // Assuming maximum length for description
    char releaseID[8]; // Assuming a fixed length for release ID
    char anticipatedReleaseID[8]; // Assuming a fixed length for anticipated release ID
    Status status; // Status attribute
    const Release* associatedRelease; // Pointer to associated Release object
};

#endif // CHANGEITEM_H
