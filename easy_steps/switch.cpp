#include <iostream>

using namespace std;

int main() {
    int num = 6;

    switch(num) {
    case 1: cout << num << " : Monday" << endl; break;
    case 2: cout << num << " : Tuesday" << endl; break;
    case 3: cout << num << " : Wednesday" << endl; break;
    case 4: cout << num << " : Thursday" << endl; break;
    case 5: cout << num << " : Friday" << endl; break;
    default: cout << num << " : Weekend" << endl; break;
    }

    return 0;
}
