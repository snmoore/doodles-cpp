#include <iostream>

using namespace std;

int main() {
    int a = 8, b = 4;

    cout << "Addition: " << a + b << endl;
    cout << "Subtraction: " << a - b << endl;
    cout << "Multiplication: " << a * b << endl;
    cout << "Division: " << a / b << endl;
    cout << "Modulus: " << a % b << endl;

    cout << "Postfix increment: " << a++ << endl;
    cout << "Postfix result: " << a << endl;
    cout << "Prefix increment: " << ++b << endl;
    cout << "Prefix result: " << b << endl;

    return 0;
}
