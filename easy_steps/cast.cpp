#include <iostream>

using namespace std;

int main() {
    int num = 7, factor = 2;
    char letter = 'A';
    float result = 0.0;
    void* data;

    cout << "Integer division: " << (num / factor) << endl;

    result = ((float)num)/factor;
    cout << "Cast float division: " << result << endl;

    num = static_cast<int>(letter);
    cout << "Cast char to int: " << num << endl;

    letter = static_cast<char>(70);
    cout << "Cast int to char: " << letter << endl;

    data = reinterpret_cast<void*>(num);
    cout << "Cast int to void*: " << data << endl;

    return 0;
}
