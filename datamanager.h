#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "contact.h"
#include "group.h"

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;

#include <QtSql/QSqlDatabase>

// DataManager manages all contacts and groups, and handles
// connecting to and updating the database
class DataManager {
private:
    //=========================================================================
    // Private data members
    //=========================================================================
    QSqlDatabase database;

    //=========================================================================
    // Private helper functions
    //=========================================================================
    void connectToDatabase();       // Establish database connection
    void fetchGroupsAndContacts();  // Get all groups and contacts
    void updateGroup(Group & group);
public:
    //=========================================================================
    // Constructor automatically connects to database and fetches data
    //=========================================================================
    DataManager();
    ~DataManager();

    map<long int, Contact> Contacts;
    map<long int, Group> Groups;

    //=========================================================================
    // Public helper functions
    //=========================================================================
    // Managing contacts in the contacts vector
    void addContact(Contact & contact);
    void updateContact(Contact & contact);
    void updateContact(const string & firstName, char middleInitial, const string & lastName,
                       const string & streetAddress, int zip, const string & city, const string & state,
                       const string & email, long long int phone, long int id);
    void deleteContact(long int id);

    // Managing groups in the groups vector
    void addGroup(Group & group);
    void updateGroup(const string & groupName, vector<long int> & contactIDs, long int id);
    void deleteGroup(long int id);
    void addContactToGroup(Group & group, Contact & contact);
    void removeContactFromGroup(Group & group, Contact & contact);

    // Debugging functions
    void printAllContacts();
    void printAllGroups();
};

#endif // DATAMANAGER_H





