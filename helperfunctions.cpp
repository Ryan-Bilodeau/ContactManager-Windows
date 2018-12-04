#include "helperfunctions.h"

#include <vector>
#include <string>
#include <sstream>
using std::vector; using std::string; using std::istringstream;

/*
 * This function was taken from exercise 7
 * splitString - function that takes a constant string &text
 * and splits it on the given delimiter character (char sep).
 * Returns the fields of the split string as a vector<string>
*/
vector<long int> HelperFunctions::splitString(const string &text, char sep) {
    vector<long int> fields;
    istringstream sstream(text);
    string field;

    while (getline(sstream, field, sep)) {
        fields.push_back(stol(field));
    }

    return fields;
}
