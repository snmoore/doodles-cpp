#include <iostream>

using namespace std;

int main() {
    int a = 1, b = 0;

    cout << "Boolean AND: " << endl;
    cout << "1 && 1: " << (a && a) << " (true)"  << endl;
    cout << "1 && 0: " << (a && b) << " (false)" << endl;
    cout << "0 && 0: " << (b && b) << " (false)" << endl;

    cout << "Boolean OR: " << endl;
    cout << "1 || 1: " << (a || a) << " (true)"  << endl;
    cout << "1 || 0: " << (a || b) << " (true)"  << endl;
    cout << "0 || 0: " << (b || b) << " (false)" << endl;

    cout << "Boolean XOR: " << endl;
    cout << "1 ^ 1: " << (a ^ a) << " (false)" << endl;
    cout << "1 ^ 0: " << (a ^ b) << " (true)"  << endl;
    cout << "0 ^ 0: " << (b ^ b) << " (false)" << endl;

    cout << "Boolean NOT: " << endl;
    cout << "a = " << a << " !a = " << !a << endl;
    cout << "b = " << a << " !b = " << !b << endl;

    return 0;
}
