#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "contact.h"
#include "group.h"

#include <string>
using std::string;
#include <vector>
using std::vector;

#include <QtSql/QSqlDatabase>

// DataManager manages all contacts and groups, and handles
// connecting to and updating the database
class DataManager {
private:
    //=========================================================================
    // Private data members
    //=========================================================================
    // Used for connecting to the database
    const string SERVER_NAME = "";
    const string USER_NAME = "";
    const string USER_PASSWORD = "";
    QSqlDatabase database;

    // Contacts and groups
    vector<Contact> _contacts;
    vector<Group> _groups;

    //=========================================================================
    // Private helper functions
    //=========================================================================
    void connectToDatabase();       // Establish database connection
    void fetchGroupsAndContacts();  // Get all groups and contacts
public:
    //=========================================================================
    // Constructor automatically connects to database and fetches data
    //=========================================================================
    DataManager();

    //=========================================================================
    // Getters
    //=========================================================================
    vector<Contact> getContacts() const { return _contacts; }
    Contact & getContact() const;
    vector<Group> getGroups() const { return _groups; }

    //=========================================================================
    // Public helper functions
    //=========================================================================
    // Managing contacts in the contacts vector
    void addContact(Contact & contact);
    void updateContact(Contact & contact);
    void deleteContact(Contact & contact);

    // Managing groups in the groups vector
    void addGroup(Group & group);
    void updateGroup(Group & group);
    void deleteGroup(Group & group);
    void addContactToGroup(Group & group, Contact & contact);
    void removeContactFromGroup(Group & group, Contact & contact);

    // Sorting functions
    void sertContacts(bool ascending);
    void sortGroups(bool ascending);
};

#endif // DATAMANAGER_H





