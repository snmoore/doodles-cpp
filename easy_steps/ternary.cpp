#include <iostream>

using namespace std;

int main() {
    int a = 1, b = 2, max;

    cout << "Variable a is: ";
    cout << ((a != 1) ? "not one, " : "one, ");
    cout << (((a % 2) != 0) ? "odd" : "even") << endl;

    cout << "Variable b is: ";
    cout << ((b != 1) ? "not one, " : "one, ");
    cout << (((b % 2) != 0) ? "odd" : "even") << endl;

    max = (a > b) ? a : b;
    cout << "The greater value is: " << max << endl;

    return 0;
}
