#include <iostream>
#include <string>

using namespace std;

void writeOutput(int* value);
void computeTriple(int* value);

int main() {
    int num = 5;
    int* ptr = &num;

    writeOutput(ptr);

    *ptr += 15;
    writeOutput(ptr);

    computeTriple(ptr);
    writeOutput(ptr);

    return 0;
}

void writeOutput(int* value) {
    cout << "Current value: " << *value << endl;
}

void computeTriple(int* value) {
    *value *= 3;
}
