#include "contact.h"

#include <stdexcept>

/**
  * Can throw invalid_argument exception.
  * firstName, lastName, and email can't be empty strings.
  * Constructor with least information required.
*/
Contact::Contact(const std::string & firstName,
                 const std::string & lastName, const std::string & email) {
    this->setFirstName(firstName);
    this->setLastName(lastName);
    this->setEmail(email);

    _middleInitial = ' ';
    _streetAddress = "";
    _zip = 0;
    _city = "";
    _state = "";
    _phone = 0;
    _id = -1;
}

/**
  * Can throw invalid_argument exception.
  * firstName, lastName, and email can't be empty strings.
  * Constructor with all information.
*/
Contact::Contact(const std::string & firstName, char middleInitial,
                 const std::string & lastName, const std::string & streetAddress, int zip,
                 const std::string & city, const std::string & state, const std::string & email,
                 long long phone, long id) :
    _middleInitial(middleInitial), _streetAddress(streetAddress), _zip(zip),
    _city(city), _state(state), _phone(phone), _id(id) {
    this->setFirstName(firstName);
    this->setLastName(lastName);
    this->setEmail(email);
}

/**
  * Can throw invalid_argument exception.
  * Sets _firstName member if argument isn't empty.
*/
void Contact::setFirstName(const std::string &firstName) {
    if (firstName != "") {
        _firstName  = firstName;
    } else {
        throw std::invalid_argument("Error in Contact.setFirstName: can't set first name to nothing");
    }
}

void Contact::setMiddleInitial(char middleInitial) {
    _middleInitial = middleInitial;
}

/**
  * Can throw invalid_argument exception.
  * Sets _lastName member if argument isn't empty.
*/
void Contact::setLastName(const std::string &lastName) {
    if (lastName != "") {
        _lastName = lastName;
    } else {
        throw std::invalid_argument("Error in Contact.setLastName: can't set last name to nothing.");
    }
}

void Contact::setStreetAddress(const std::string &streetAddress) {
    _streetAddress = streetAddress;
}

void Contact::setZip(int zip) {
    _zip = zip;
}

void Contact::setCity(const std::string &city) {
    _city = city;
}

void Contact::setState(const std::string &state) {
    _state = state;
}

/**
  * Can throw invalid_argument exception.
  * Sets _email member if argument isn't empty.
*/
void Contact::setEmail(const std::string &email) {
    if (email != "") {
        _email = email;
    } else {
        throw std::invalid_argument("Error in Contact.setEmail: can't set email to nothing");
    }
}

void Contact::setPhone(long long phone) {
    _phone = phone;
}

// Should only be called by the datamanager
void Contact::setID(long int id) {
    _id = id;
}
