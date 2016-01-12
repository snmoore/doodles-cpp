#include <iostream>
#include <string>

using namespace std;

int main() {
    int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    int* ptr = nums;
    cout << "Pointer at " << ptr << " holds " << *ptr << endl;
    ptr++;
    cout << "Pointer at " << ptr << " holds " << *ptr << endl;
    ptr++;
    cout << "Pointer at " << ptr << " holds " << *ptr << endl;

    ptr -= 2;
    cout << "Pointer at " << ptr << " holds " << *ptr << endl;
    cout << endl;

    for(int i = 0; i < 10; i++) {
        cout << endl << "Element: " << i;
        cout << "\tValue: " << *ptr;
        ptr++;
    }
    cout << endl;

    return 0;
}



