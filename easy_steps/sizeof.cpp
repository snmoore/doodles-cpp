#include <iostream>

using namespace std;

class Class {
    short short_int;
    bool boolean;
    // beware of alignment/padding
    int plain_int;

    // only non-static data members count for sizeof
    static int not_counted;
};

int main() {
    bool boolean;
    bool booleans[10];

    char plain_char;
    char chars[10];

    short int short_int;
    int plain_int;
    long int long_int;
    long long int long_long_int; // C++11 extension
    int ints[10];

    float plain_float;
    float floats[10];

    double plain_double;
    long double long_double;
    double doubles[10];

    Class object;

    cout << "Size of bool:        " << sizeof(boolean)       << endl;
    cout << "Size of bool[10]:    " << sizeof(booleans)      << endl;
    cout << endl;

    cout << "Size of char:        " << sizeof(plain_char)    << endl;
    cout << "Size of char[10]:    " << sizeof(chars)         << endl;
    cout << endl;

    cout << "Size of short int:   " << sizeof(short_int)     << endl;
    cout << "Size of int:         " << sizeof(plain_int)     << endl;
    cout << "Size of long:        " << sizeof(long_int)      << endl;
    cout << "Size of long long:   " << sizeof(long_long_int) << endl;
    cout << "Size of int[10]:     " << sizeof(ints)          << endl;
    cout << endl;

    cout << "Size of float:       " << sizeof(plain_float)   << endl;
    cout << "Size of float[10]:   " << sizeof(floats)        << endl;
    cout << endl;

    cout << "Size of double:      " << sizeof(plain_double)  << endl;
    cout << "Size of long_double: " << sizeof(long_double)   << endl;
    cout << "Size of double[10]:  " << sizeof(doubles)       << endl;
    cout << endl;

    cout << "Size of Class:       " << sizeof(Class)        << endl;
    cout << "Size of object:      " << sizeof(object)       << endl;

    return 0;
}
