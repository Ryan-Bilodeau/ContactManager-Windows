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
    Contact(const string & firstName,const string & lastName,const string & email);
    Contact(const string & firstName, char middleInitial, const string & lastName,
            const string & streetAddress, int zip, const string & city, const string & state,
            const string & email, long long int phone, long int id);

    //=========================================================================
    // Getters
    //=========================================================================
    const string & getFirstName() const { return _firstName; }
    char getMiddleInitial() const { return _middleInitial; }
    const string & getLastName() const { return _lastName; }
    const string & getStreetAddress() const { return _streetAddress; }
    int getZip() const { return _zip; }
    const string & getCity() const { return _city; }
    const string & getState() const { return _state; }
    const string & getEmail() const { return _email; }
    long long int getPhone() const { return _phone; }
    long int getID() const { return _id; }

    //=========================================================================
    // Setters
    //=========================================================================
    void setFirstName(const string & firstName);
    void setMiddleInitial(char middleInitial);
    void setLastName(const string & lastName);
    void setStreetAddress(const string & streetAddress);
    void setZip(int zip);
    void setCity(const string & city);
    void setState(const string & state);
    void setEmail(const string & email);
    void setPhone(long long int phone);
    void setID(long int id);
};

#endif // CONTACT_H
