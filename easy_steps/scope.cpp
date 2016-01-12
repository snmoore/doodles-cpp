#include <iostream>

using namespace std;

float bodyTempC();
float bodyTempF();

float temperature = 0.1;

int main() {
    float temperature = 1.2;

    cout << "Centigrade: " << bodyTempC() << endl;
    cout << "Fahrenheit: " << bodyTempF() << endl;

    return 0;
}

float bodyTempC() {
    float temperature = 37.0;
    return temperature;
}

float bodyTempF() {
    float temperature = 98.6;
    return temperature;
}
