#include <iostream>

using namespace std;

void add(int& a, int* b);

int main() {
    int num = 100, sum = 500;
    int& rNum = num;
    int* ptr = &num;
    void (*func)(int& a, int* b) = add;

    cout << "Reference: " << rNum << endl;
    cout << "Pointer: " << *ptr << endl;

    ptr = &sum;
    cout << "Pointer now: " << *ptr << endl;

    func(rNum, ptr);

    return 0;
}

void add(int& a, int* b) {
    cout << "Total: " << (a + *b) << endl;
}
