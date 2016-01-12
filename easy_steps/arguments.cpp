#include <iostream>

using namespace std;

float FtoC(float degreesF = 32.0);

int main() {
    float fahrenheit, centigrade;

    cout << "Enter a fahrenheit temperature: ";
    cin >> fahrenheit;

    centigrade = FtoC(fahrenheit);
    cout << fahrenheit << "F is " << centigrade << "C" << endl;
    cout << "Freezing point is " << FtoC() << "C" << endl;

    return 0;
}

float FtoC(float degreesF) {
    float degreesC = (5.0 / 9.0) * (degreesF - 32.0);
    return degreesC;
}
