#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    string term = "100";
    int number = 100;

    int num;                // to store a converted string
    string text;            // to store a converted integer
    stringstream stream;    // to perform conversions

    stream << term;         // load the string
    stream >> num;          // extract the integer
    num /= 4;
    cout << "Integer value: " << num << endl;

    stream.str("");         // empty the contents
    stream.clear();         // clear the bit flags

    stream << number;       // load the integer
    stream >> text;         // extract the string
    text += " percent";
    cout << "String value: " << text << endl;

    return 0;
}
