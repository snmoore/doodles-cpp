#include <iostream>

using namespace std;

int main() {
    int num = 3;
    char letter = 'B';

    if(num > 5) {
        cout << "Number exceeds five" << endl;

        if(letter == 'A') {
            cout << "Letter is A" << endl;
        }
    }
    else {
        cout << "Number is five or less" << endl;
    }

    return 0;
}
