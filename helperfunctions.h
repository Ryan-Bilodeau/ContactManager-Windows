#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <string>
using std::string;
#include <vector>
using std::vector;

class HelperFunctions
{
public:
    static vector<long int> splitString(const string &text, char sep);
};

#endif // HELPERFUNCTIONS_H
