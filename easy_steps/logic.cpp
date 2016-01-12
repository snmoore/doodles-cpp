#include <iostream>

using namespace std;

int main() {
    int a = 1, b = 0;

    cout << "Boolean AND: ";
    cout << "a && a: " << (a && a) << " (true) ";
    cout << "a && b: " << (a && b) << " (false) ";
    cout << "b && b: " << (b && b) << " (false) " << endl;

    cout << "Boolean OR: ";
    cout << "a || a: " << (a || a) << " (true) ";
    cout << "a || b: " << (a || b) << " (true) ";
    cout << "b || b: " << (b || b) << " (false) " << endl;

    cout << "Boolean XOR: ";
    cout << "a ^ a: " << (a ^ a) << " (false) ";
    cout << "a ^ b: " << (a ^ b) << " (true) ";
    cout << "b ^ b: " << (b ^ b) << " (false) " << endl;

    cout << "Boolean NOT: ";
    cout << "a = " << a << " !a = " << !a << " ";
    cout << "b = " << a << " !b = " << !b << endl;

    return 0;
}
