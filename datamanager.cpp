#include "datamanager.h"
#include "contact.h"
#include "group.h"
#include "strings.h"
#include "helperfunctions.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QString>
#include <QVariant>

#include <map>
#include <iostream>
#include <sstream>
#include <string>
using std::endl; using std::cout;

#include <stdexcept>

/**
  * Call in constructor to set up database connection
*/
void DataManager::connectToDatabase() {
    // This code was mainly taken from the CustomerDB app
    database = QSqlDatabase::addDatabase("QODBC");

    std::stringstream ss;
    ss << "Driver={ODBC Driver 13 for SQL Server};" <<
          "Server=" << Strings::SERVER_NAME << ",1433;" <<
          "Database=" << Strings::DATABASE_NAME << ";" <<
          "Uid=" << Strings::DATABASE_USER_ID << ";" <<
          "Pwd=" << Strings::DATABASE_PASSWORD << ";" <<
          "Encrypt=yes;TrustServerCertificate=no;ConnectionTimeout=30;";


    database.setDatabaseName(QString::fromStdString(ss.str()));
}

/**
  * Can throw runtime_error exception.
  * Call in constructor to get group and contact information from the server.
*/
void DataManager::fetchGroupsAndContacts() {
    bool dbOpen = database.open();

    // If database can be accessed, pull information
    if (dbOpen) {
        cout << "Database connection opened" << endl;

        QSqlQuery queryContacts;
        queryContacts.setForwardOnly(true);

        queryContacts.prepare("SELECT * FROM Contacts");

        if (queryContacts.exec()) {                     // Execute query, if successful...
            while (queryContacts.next()) {              // Process each row returned by query
                string firstName = queryContacts.value(0).toString().toStdString();
                string lastName = queryContacts.value(1).toString().toStdString();
                char middleInitial = queryContacts.value(2).toString().toStdString()[0];
                long long int phone = queryContacts.value(3).toLongLong();
                string email = queryContacts.value(4).toString().toStdString();
                string streetAddress = queryContacts.value(5).toString().toStdString();
                string cityAddress = queryContacts.value(6).toString().toStdString();
                string stateAddress = queryContacts.value(7).toString().toStdString();
                int zipCode = queryContacts.value(8).toInt();
                long int id = queryContacts.value(10).toLongLong();

                Contact contact = Contact(firstName, middleInitial, lastName,
                                          streetAddress, zipCode, cityAddress,
                                          stateAddress, email, phone, id);

                this->Contacts.insert(std::pair<long int, Contact>(id, contact));
            }
        } else {
            throw std::runtime_error("Error in DataManager.fetchGroupsAndContacts: Couldn't get Contacts");
        }

        QSqlQuery queryGroups;
        queryGroups.setForwardOnly(true);

        queryGroups.prepare("SELECT * FROM Groups");

        if (queryGroups.exec()) {                     // Execute query, if successful...
            while (queryGroups.next()) {              // Process each row returned by query
                string name = queryGroups.value(0).toString().toStdString();
                string customerIDs = queryGroups.value(1).toString().toStdString();
                long int id = queryGroups.value(2).toLongLong();

                // Customer ids are returned as a string, comma delimited
                vector<long int> ids = HelperFunctions::splitString(customerIDs, ',');

                Group group = Group(name, ids, id);

                this->Groups.insert(std::pair<int, Group>(id, group));
            }
        } else {
            throw std::runtime_error("Error in DataManager.fetchGroupsAndContacts: Couldn't get Groups");
        }
    } else {
        throw std::runtime_error("Error in DataManager.fetchGroupsAndContacts: "
                                 "Database connection failed to open");
    }
}

// Only constructor
DataManager::DataManager() {
    this->connectToDatabase();
    this->fetchGroupsAndContacts();
}

// Clean up
DataManager::~DataManager() {
    database.close();
    cout << "Database connection closed successfully" << endl;
}

/**
  * Can throw invalid_argument exception.
  * Can throw runtime_error exception.
  * Contacts must provide a first name, last name, and email
  * Add contact to Contacts map. If contact exists, throw error.
  * Add contact to database if needed.
  * Sets the contact's id after insertion.
*/
void DataManager::addContact(Contact &contact) {
    // If contact exists...
    if (this->Contacts.find(contact.getID()) != this->Contacts.end()) {
        throw std::invalid_argument("Error in DataManager.addContact: Contact already exists");

    // Otherwise, add to Contacts map and update database
    } else {
        QSqlQuery query;
        query.setForwardOnly(true);

        std::stringstream sql;
        sql << "INSERT INTO Contacts (firstName, lastName, middleInitial, phone,"
               "email, streetAddress, cityAddress, stateAddress, zipAddress) VALUES ('"
            << contact.getFirstName() << "', '" << contact.getLastName() << "', '"
            << contact.getMiddleInitial() << "', '" << contact.getPhone() << "', '"
            << contact.getEmail() << "', '" << contact.getStreetAddress() << "', '"
            << contact.getCity() << "', '" << contact.getState() << "', '"
            << contact.getZip() << "');";

        query.prepare(QString::fromStdString(sql.str()));

        // If database was updated...
        if (query.exec()) {
            QSqlQuery q;
            q.setForwardOnly(true);
            q.prepare("SELECT MAX(id) FROM Contacts");
            q.exec();
            q.next();
            long int id = q.value(0).toLongLong();
            contact.setID(id);

            this->Contacts.insert(std::pair<long int, Contact>(contact.getID(), contact));

            cout << "Successfully added contact to database" << endl;
        } else {
            throw std::runtime_error("Error in DataManager.addContact: "
                                     "Failed to add contact to database");
        }
    }
}

/**
  * Can throw runtime_error exception.
  * Updates contact in database.
  * Called internally by the datamanager.
*/
void DataManager::updateContact(Contact &contact) {
    QSqlQuery query;
    query.setForwardOnly(true);

    std::stringstream sql;
    sql << "UPDATE Contacts SET " <<
           "firstName = '" << contact.getFirstName() <<
           "', lastName = '" << contact.getLastName() <<
           "', middleInitial = '" << contact.getMiddleInitial() <<
           "', phone = '" << contact.getPhone() <<
           "', email = '" << contact.getEmail() <<
           "', streetAddress = '" << contact.getStreetAddress() <<
           "', cityAddress = '" << contact.getCity() <<
           "', stateAddress = '" << contact.getState() <<
           "', zipAddress = '" << contact.getZip() <<
           "' WHERE id = '" << contact.getID() << "';";

    query.prepare(QString::fromStdString(sql.str()));

    if (query.exec()) {                     // Execute query, if successful...
        cout << "Successfully updated contact" << endl;
    } else {
        throw std::runtime_error("Error in DataManager.updateContact: couldn't execute query");
    }
}

/**
  * Can throw runtime_error exception.
  * Can throw invalid_argument exception.
  * Updates contact locally and in database.
*/
void DataManager::updateContact(const string & firstName, char middleInitial,
                                const string & lastName,
                                const string & streetAddress, int zip,
                                const string & city, const string & state,
                                const string & email, long long int phone,
                                long int id) {
    if (Contacts.find(id) == Contacts.end())
        throw std::invalid_argument("Error in DataManager.updateContact: given id dones't exist");

    Contact & contact = Contacts.find(id)->second;

    // Variables used to revert changes in event of failure
    string _firstName;
    string _lastName;
    char _middleInitial;
    long long int _phone;
    string _email;
    string _streetAddress;
    string _cityAddress;
    string _stateAddress;
    int _zip;

    try {
        _firstName = contact.getFirstName();
        contact.setFirstName(firstName);

        _lastName = contact.getLastName();
        contact.setLastName(lastName);

        _middleInitial = contact.getMiddleInitial();
        contact.setMiddleInitial(middleInitial);

        _phone = contact.getPhone();
        contact.setPhone(phone);

        _email = contact.getEmail();
        contact.setEmail(email);

        _streetAddress = contact.getStreetAddress();
        contact.setStreetAddress(streetAddress);

        _cityAddress = contact.getCity();
        contact.setCity(city);

        _stateAddress = contact.getState();
        contact.setState(state);

        _zip = contact.getZip();
        contact.setZip(zip);
    } catch (std::invalid_argument e) {
        // Make caller deal with error
        throw e;
    }

    try {
        this->updateContact(contact);
    } catch (std::runtime_error e) {
        contact.setFirstName(_firstName);
        contact.setLastName(_lastName);
        contact.setMiddleInitial(_middleInitial);
        contact.setPhone(_phone);
        contact.setEmail(_email);
        contact.setStreetAddress(_streetAddress);
        contact.setCity(_cityAddress);
        contact.setState(_stateAddress);
        contact.setZip(_zip);

        // Make caller deal with error
        throw e;
    }


}

/**
  * Can throw runtime_error exception.
  * Can throw invalid_argument exception.
  * Deletes contact locally and in database.
*/
void DataManager::deleteContact(long int id) {
    if (Contacts.find(id) == Contacts.end()) {
        throw std::invalid_argument("Error in DataManager.deleteContact: given id dones't exist");

    // Otherwise, delete contact from database and locally
    } else {
        QSqlQuery query;
        query.setForwardOnly(true);

        std::stringstream sql;
        sql << "DELETE FROM Contacts WHERE id = '" << id << "';";

        query.prepare(QString::fromStdString(sql.str()));

        // If database was updated...
        if (query.exec()) {
            map<long int, Contact>::iterator iter = Contacts.find(id);

            Contacts.erase(iter);

            cout << "Successfully deleted contact from database" << endl;
        } else {
            throw std::runtime_error("Error in DataManager.deleteContact: "
                                     "Failed to delete contact from database");
        }
    }
}

/**
  * Can throw invalid_argument exception.
  * Can throw runtime_error exception.
  * Groups must provide a name
  * Add group to Groups map. If group exists, throw error.
  * If two grops have same name, throw error.
  * Add group to database if needed.
  * Sets the group's id after insertion.
*/
void DataManager::addGroup(Group &group) {
    // Check if group with same name exists
    bool sameName = false;
    map<long int, Group>::iterator iter;
    for (iter = this->Groups.begin(); iter != this->Groups.end(); ++iter) {
        if (iter->second.getName() == group.getName())
            sameName = true;
    }

    // If group exists...
    if (this->Groups.find(group.getID()) != this->Groups.end() || sameName) {
        throw std::invalid_argument("Error in DataManager.addGroup: Group already exists");

    // Otherwise, add to Groups map and update database
    } else {
        QSqlQuery query;
        query.setForwardOnly(true);

        std::stringstream sql;
        sql << "INSERT INTO Groups (groupName, contactKey) VALUES ('"
            << group.getName() << "', '";

        if (group.ContactIDs.size() > 0) {
            vector<long int>::iterator iter;
            for (iter = group.ContactIDs.begin(); iter != group.ContactIDs.end(); ++iter) {
                if (iter != group.ContactIDs.end() - 1)
                    sql << *iter << ",";
                else
                    sql << *iter << "');";
            }
        } else {
            sql << "');";
        }

        query.prepare(QString::fromStdString(sql.str()));

        // If database was updated...
        if (query.exec()) {
            QSqlQuery q;
            q.setForwardOnly(true);
            q.prepare("SELECT MAX(id) FROM Groups");
            q.exec();
            q.next();
            long int id = q.value(0).toLongLong();
            group.setID(id);

            this->Groups.insert(std::pair<long int, Group>(group.getID(), group));

            cout << "Successfully added group to database" << endl;
        } else {
            throw std::runtime_error("Error in DataManager.addGroup: "
                                     "Failed to add group to database");
        }
    }
}

/**
  * Can throw runtime_error exception.
  * Updates group in database.
  * Called internally by the datamanager.
*/
void DataManager::updateGroup(Group &group) {
    QSqlQuery query;
    query.setForwardOnly(true);

    std::stringstream sql;
    sql << "UPDATE Contacts SET " <<
           "groupName = '" << group.getName() <<
           "', contactKey = '";;

    if (group.ContactIDs.size() > 0) {
        vector<long int>::iterator iter;
        for (iter = group.ContactIDs.begin(); iter != group.ContactIDs.end(); ++iter) {
            if (iter != group.ContactIDs.end() - 1)
                sql << *iter << ",";
            else
                sql << *iter << "'";
        }
    } else {
        sql << "'";
    }

    sql << " WHERE id = '" << group.getID() << "';";

    query.prepare(QString::fromStdString(sql.str()));

    if (query.exec()) {                     // Execute query, if successful...
        cout << "Successfully updated group" << endl;
    } else {
        throw std::runtime_error("Error in DataManager.updateGroup: couldn't execute query");
    }
}

/**
  * Can throw runtime_error exception.
  * Can throw invalid_argument exception.
  * Updates group locally and in database.
*/
void DataManager::updateGroup(const string & groupName,
                            vector<long int> & contactIDs, long int id) {
    if (Groups.find(id) == Groups.end())
        throw std::invalid_argument("Error in DataManager.updateGroup: given id dones't exist");

    Group & group = Groups.find(id)->second;

    // Variables used to revert changes in event of failure
    string _groupName;
    vector<long int> _contactIDs;

    try {
        _groupName = group.getName();
        group.setName(groupName);

        _contactIDs = group.ContactIDs;
        group.ContactIDs = contactIDs;
    } catch (std::invalid_argument e) {
        // Make caller deal with errors
        throw e;
    }

    try {
        this->updateGroup(group);
    } catch (std::runtime_error e) {
        group.setName(_groupName);
        group.ContactIDs = contactIDs;

        // Make caller deal with errors
        throw e;
    }
}

/**
  * Can throw runtime_error exception.
  * Can throw invalid_argument exception.
  * Deletes group locally and in database.
*/
void DataManager::deleteGroup(long int id) {
    if (Groups.find(id) == Groups.end()) {
        throw std::invalid_argument("Error in DataManager.deleteGroup: given id dones't exist");

    // Otherwise, delete group from database and locally
    } else {
        QSqlQuery query;
        query.setForwardOnly(true);

        std::stringstream sql;
        sql << "DELETE FROM Contacts WHERE id = '" << id << "';";

        query.prepare(QString::fromStdString(sql.str()));

        // If database was updated...
        if (query.exec()) {
            map<long int, Contact>::iterator iter = Contacts.find(id);

            Contacts.erase(iter);

            cout << "Successfully deleted contact from database" << endl;
        } else {
            throw std::runtime_error("Error in DataManager.deleteContact: "
                                     "Failed to delete contact from database");
        }
    }
}

/**
  * Can throw runtime_error exception.
  * Can throw invalid_argument exception.
  * Adds contact to group locally and in database.
*/
void DataManager::addContactToGroup(Group &group, Contact &contact) {
    try {
        group.addContact(contact.getID());
    } catch (std::invalid_argument e) {
        // Make caller handle error
        throw e;
    }

    try {
        this->updateGroup(group);
    } catch (std::runtime_error e) {
        group.removeContact(contact.getID());

        // Make caller handle error
        throw e;
    }
}

/**
  * Can throw runtime_error exception.
  * Can throw invalid_argument exception.
  * Removes contact from group locally and in database.
*/
void DataManager::removeContactFromGroup(Group &group, Contact &contact) {
    try {
        group.removeContact(contact.getID());
    } catch (std::invalid_argument e) {
        // Make caller handle error
        throw e;
    }

    try {
        this->updateGroup(group);
    } catch (std::runtime_error e) {
        group.addContact(contact.getID());

        // Make caller handle error
        throw e;
    }
}

// Prints all contacts to the standard output
void DataManager::printAllContacts() {
    cout << "All contacts:" << endl;
    cout << "===============================================================" << endl;

    map<long int, Contact>::iterator iter;
    for (iter = this->Contacts.begin(); iter != this->Contacts.end(); ++iter) {
        cout << iter->second.getFirstName() << "    " << iter->second.getLastName() <<
                "   " << iter->second.getMiddleInitial() << "   " << iter->second.getPhone() <<
                "   " << iter->second.getEmail() << "   " << iter->second.getStreetAddress() <<
                "   " << iter->second.getCity() << "   " << iter->second.getState() <<
                "   " << iter->second.getZip() << "   " << iter->second.getID() << endl;
    }
}

// Prints all groups to the standard output
void DataManager::printAllGroups() {
    cout << "All groups:" << endl;
    cout << "===============================================================" << endl;

    map<long int, Group>::iterator iter;
    for (iter = this->Groups.begin(); iter != this->Groups.end(); ++iter) {
        std::stringstream ss;

        vector<long int>::iterator it;
        for (it = iter->second.ContactIDs.begin(); it != iter->second.ContactIDs.end(); ++it) {
            if (it != iter->second.ContactIDs.end() - 1)
                ss << *it << ",";
            else
                ss << *it;
        }

        cout << iter->second.getName() << "   " << ss.str() << "   " << iter->second.getID() << endl;
    }
}
