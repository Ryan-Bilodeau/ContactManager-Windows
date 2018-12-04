#ifndef STRINGS_H
#define STRINGS_H

#include <string>
using std::string;

// Holds all sensitive strings in the project
class Strings {
public:
    static const string SERVER_NAME;
    static const string DATABASE_NAME;
    static const string DATABASE_USER_ID;
    static const string DATABASE_PASSWORD;
};

#endif // STRINGS_H
