// Convert a string to an integer
//
// See http://pubs.opengroup.org/onlinepubs/009695399/functions/atoi.html

#include <cstdlib>      // For std::atoi()
#include <iomanip>      // For setw()
#include <iostream>     // For cout etc
#include <sstream>      // For stringstream
#include <vector>       // For vector

using namespace std;

// Convert using a stringstream
namespace stream {
int atoi(string s) {
    int i { 0 };
    stringstream stream(s);
    stream >> i;
    return i;
}
}

// Convert C-like using a range-for statement
namespace range {
int atoi(string s) {
    int sign { 1 };
    int i { 0 };

    for(char& c : s) {
        if(c == '+') {
            sign = 1;
            continue;
        }

        if(c == '-') {
            sign = -1;
            continue;
        }

        if(isdigit(c)) {
            i *= 10;
            i += c - '0';
        }
        else {
            break;
        }
    }

    return sign * i;
}
}

// Convert C-like using an iterator
namespace iterate {
int atoi(string s) {
    int sign { 1 };
    int i { 0 };

    for(auto iter = s.begin(); iter != s.end(); iter++) {
        if(*iter == '+') {
            sign = 1;
            continue;
        }

        if(*iter == '-') {
            sign = -1;
            continue;
        }

        if(isdigit(*iter)) {
            i *= 10;
            i += *iter - '0';
        }
        else {
            break;
        }
    }

    return sign * i;
}
}

int main() {
    vector<string> strings { "0", "11", "+11", "-11", "2147483647", "abc", "" };
                                                      /* INT_MAX */

    cout << left << setw(15) << "String";
    cout << left << setw(15) << "std::atoi";
    cout << left << setw(15) << "stream::atoi";
    cout << left << setw(15) << "range::atoi";
    cout << left << setw(15) << "iterate::atoi" << endl;

    for(auto s : strings) {
        cout << left << setw(15) << "\"" + s + "\"";
        cout << left << setw(15) << std::atoi(s.c_str());
        cout << left << setw(15) << stream::atoi(s);
        cout << left << setw(15) << range::atoi(s);
        cout << left << setw(15) << iterate::atoi(s) << endl;
    }
}
