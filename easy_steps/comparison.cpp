#include <iostream>

using namespace std;

int main() {
    int nil = 0, num = 0, max = 1;
    char cap = 'A', low = 'a';

    cout << "Equality comparisons: " << endl;
    cout << "0 == 0: " << (nil == num) << " (true)" << endl;
    cout << "A == a: " << (cap == low) << " (false)" << endl;

    cout << "Inequality comparison: " << endl;
    cout << "0 != 1: " << (nil != max) << " (true)" << endl;

    cout << "Greater comparison: " << endl;
    cout << "0 > 1: " << (nil > max) << " (false)" << endl;

    cout << "Lesser comparison: " << endl;
    cout << "0 < 1: " << (nil < max) << " (true)" << endl;

    cout << "Greater or equal comparison: " << endl;
    cout << "0 >= 0: " << (nil >= num) << " (true)" << endl;

    cout << "Lesser or equal comparison: " << endl;
    cout << "1 <= 0: " << (max <= num) << " (false)" << endl;

    return 0;
}
