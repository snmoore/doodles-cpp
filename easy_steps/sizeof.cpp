#include <iostream>

using namespace std;

int main() {
    bool boolean;
    bool booleans[10];

    char plain_char;
    char chars[10];

    short int short_int;
    int plain_int;
    long int long_int;
    int ints[10];

    float plain_float;
    float floats[10];

    double plain_double;
    long double long_double;
    double doubles[10];

    cout << "Size of bool: " << sizeof(boolean) << endl;
    cout << "Size of bool[10]: " << sizeof(booleans) << endl;
    cout << endl;

    cout << "Size of char: " << sizeof(plain_char) << endl;
    cout << "Size of char[10]: " << sizeof(chars) << endl;
    cout << endl;

    cout << "Size short int: " << sizeof(short_int) << endl;
    cout << "Size int: " << sizeof(plain_int) << endl;
    cout << "Size long: " << sizeof(long_int) << endl;
    cout << "Size of int[10]: " << sizeof(ints) << endl;
    cout << endl;

    cout << "Size of float: " << sizeof(plain_float) << endl;
    cout << "Size of float[10]: " << sizeof(floats) << endl;
    cout << endl;

    cout << "Size of double: " << sizeof(plain_double) << endl;
    cout << "Size of long_double: " << sizeof(long_double) << endl;
    cout << "Size of double[10]: " << sizeof(doubles) << endl;
    cout << endl;

    return 0;
}
