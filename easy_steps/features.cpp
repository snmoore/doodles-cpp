#include <iostream>
#include <string>

using namespace std;

void computeFeatures(string text);

int main() {
    string text = "C++ is fun";
    computeFeatures(text);

    text += " for everyone";
    computeFeatures(text);

    text = "C++ fun";
    computeFeatures(text);

    text.clear();
    computeFeatures(text);

    return 0;
}

void computeFeatures(string text) {
    cout << "String: "     << text            << endl;
    cout << "\tSize:     " << text.size()     << endl;
    cout << "\tCapacity: " << text.capacity() << endl;
    cout << "\tSizeof:   " << sizeof(text)    << endl;
    cout << "\tEmpty?:   " << text.empty()    << endl;
    cout << endl;
}
