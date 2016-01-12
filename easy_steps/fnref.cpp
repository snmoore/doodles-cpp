#include <iostream>
#include <string>

using namespace std;

void writeOutput(int& value);
void computeTriple(int& value);

int main() {
    int num = 5;
    int& ref = num;

    writeOutput(ref);

    ref += 15;
    writeOutput(ref);

    computeTriple(ref);
    writeOutput(ref);

    return 0;
}

void writeOutput(int& value) {
    cout << "Current value: " << value << endl;
}

void computeTriple(int& value) {
    value *= 3;
}

