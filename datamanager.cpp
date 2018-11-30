#include "datamanager.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QString>
#include <QVariant>

void DataManager::connectToDatabase()
{

}

void DataManager::fetchGroupsAndContacts()
{

}

DataManager::DataManager() {

}

Contact &DataManager::getContact() const
{

}

void DataManager::addContact(Contact &contact)
{

}

void DataManager::updateContact(Contact &contact)
{

}

void DataManager::deleteContact(Contact &contact)
{

}

void DataManager::addGroup(Group &group)
{

}

void DataManager::updateGroup(Group &group)
{

}

void DataManager::deleteGroup(Group &group)
{

}

void DataManager::addContactToGroup(Group &group, Contact &contact)
{

}

void DataManager::removeContactFromGroup(Group &group, Contact &contact)
{

}

void DataManager::sertContacts(bool ascending)
{

}

void DataManager::sortGroups(bool ascending)
{

}
