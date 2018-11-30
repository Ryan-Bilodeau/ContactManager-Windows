#ifndef CONTACT_H
#define CONTACT_H

#include <string>
using std::string;

// Contact class stores information about each contact
class Contact {
private:
    //=========================================================================
    // Private data members
    //=========================================================================
    string _firstName;
    char _middleInitial;
    string _lastName;

    string _streetAddress;
    int _zip;
    string _city;
    string _state;

    string _email;
    long long int _phone;
    long int _id;

    //=========================================================================
    // TODO: Add image type
    //=========================================================================
public:
    //=========================================================================
    // Constructors - firstName, lastName, and email are required to instantiate
    //=========================================================================
    Contact(string & firstName, string & lastName, string email);
    Contact(string & firstName, char middleInitial, string & lastName,
            string & streetAddress, int zip, string & city, string & state,
            string & email, long long int phone, long int id);

    //=========================================================================
    // Getters
    //=========================================================================
    string getFirstName() const { return _firstName; }
    char getMiddleInitial() const { return _middleInitial; }
    string getLastName() const { return _lastName; }
    string getStreetAddress() const { return _streetAddress; }
    int getZip() const { return _zip; }
    string getCity() const { return _city; }
    string getState() const { return _state; }
    string getEmail() const { return _email; }
    long long int getPhone() const { return _phone; }
    long int getID() const { return _id; }

    //=========================================================================
    // Setters
    //=========================================================================
    void setFirstName(string & firstName);
    void setMiddleInitial(char middleInitial);
    void setLastName(string & lastName);
    void setStreetAddress(string & streetAddress);
    void setZip(int zip);
    void setCity(string & city);
    void setState(string & state);
    void setEmail(string & email);
    void setPhone(long long int phone);
};

#endif // CONTACT_H
