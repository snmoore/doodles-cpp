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
    cout << endl << "String: " << text << endl;
    cout << "Size: " << text.size();
    cout << "\tCapacity: " << text.capacity();
    cout << "\tSizeof: " << sizeof(text);
    cout << "\tEmpty?: " << text.empty() << endl;
}
