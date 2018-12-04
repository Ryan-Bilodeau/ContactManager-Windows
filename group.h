#ifndef GROUP_H
#define GROUP_H

#include "contact.h"
#include <string>
using std::string;
#include <vector>
using std::vector;

// Group class stores the name of a group and the contacts
// that belong to that group
class Group {
private:
    //=========================================================================
    // Private data members
    //=========================================================================
    string _name;
    long int _id;
public:
    //=========================================================================
    // Constructors to create a new group, name is required but contacts aren't
    //=========================================================================
    Group(const string & groupName);
    Group(const string & groupName, vector<long int> & contactIDs, long int id);

    vector<long int> ContactIDs;

    //=========================================================================
    // Getters
    //=========================================================================
    const string & getName() const { return _name; }
    long int getID() const { return _id; }

    //=========================================================================
    // Setters
    //=========================================================================
    void setName(const string & groupName);
    void setID(long int id);

    //=========================================================================
    // Public helper functions
    //=========================================================================
    void addContact(long int id);     // Called by the datamanager
    void removeContact(long int id);  // Called by the datamanager
};

#endif // GROUP_H
