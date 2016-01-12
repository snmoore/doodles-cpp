#include <iostream>

using namespace std;

int main() {
    for(int i = 1; i < 4; i++) {
        cout << "Loop iteration: " << i << endl;

        for(int j = 1; j < 4; j++) {
            cout << "\tInner loop iteration: " << j << endl;
        }
    }

    return 0;
}
