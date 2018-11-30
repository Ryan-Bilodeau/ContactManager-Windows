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
    vector<Contact> _contacts;
    long int _id;
public:
    //=========================================================================
    // Constructors to create a new group, name is required but contacts aren't
    Group(string & groupName);
    Group(string & groupName, vector<Contact> & contacts);

    //=========================================================================
    // Getters
    //=========================================================================
    string getName() const { return _name; }
    vector<Contact> getContacts() const { return _contacts; }
    long int getID() const { return _id; }

    //=========================================================================
    // Setters
    //=========================================================================
    void setName(string & groupName);

    //=========================================================================
    // Public helper functions
    //=========================================================================
    void addContact(Contact & contact);     // Called by the datamanager
    void removeContact(Contact & contact);  // Called by the datamanager
};

#endif // GROUP_H
