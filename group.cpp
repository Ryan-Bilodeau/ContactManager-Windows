#include "group.h"

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>

#include <stdexcept>

/**
  * Can throw invalid_argument exception.
  * groupName can't be an empty string.
  * Constructor with least information required.
*/
Group::Group(const string & groupName) {
    this->setName(groupName);

    ContactIDs = vector<long int>();
    _id = -1;
}

/**
  * Can throw invalid_argument eception.
  * groupName can't be an empty string.
  * Constructor with all information.
*/
Group::Group(const string & groupName, vector<long int> & contactIDs, long int id)
    : _id(id), ContactIDs(contactIDs) {
    this->setName(groupName);
}

/**
  * Can throw invalid_argument exception.
  * Sets group name if argument isn't empty.
*/
void Group::setName(const string & groupName) {
    if (groupName != "") {
        _name  = groupName;
    } else {
        throw std::invalid_argument("Error in Group.setName: can't set group name to nothing");
    }
}

// Should only be called by the datamanager
void Group::setID(long int id) {
    _id = id;
}

/**
  * Can throw invalid_argument exception.
  * Adds a contact to the ContactIDs if not existing.
*/
void Group::addContact(long int id) {
    vector<long int>::iterator iter;
    for (iter = ContactIDs.begin(); iter != ContactIDs.end(); ++iter) {
        if (*iter == id) {
            throw std::invalid_argument("Error in Group.addContact: No matching id");
        }
    }

    ContactIDs.push_back(id);
}

/**
  * Can throw invalid_argument exception.
  * Removes a contact from the ContactIDs if existing.
*/
void Group::removeContact(long int id) {
    vector<long int>::iterator iter = std::find(ContactIDs.begin(), ContactIDs.end(), id);

    if (iter != ContactIDs.end()) {
        ContactIDs.erase(iter);
    } else {
        throw std::invalid_argument("Error in Group.removeContact: No matching id");
    }
}
