// Round up an integer to the next highest power of 2
// Do not round up if the integer is a power of 2
//
// See https://graphics.stanford.edu/~seander/bithacks.html

#include <iostream>     // For cout etc
#include <limits>       // For UINT_MAX

using namespace std;

// The classic but non-obvious method
unsigned int roundup(unsigned int v) {
    // 0 should roundup to 1
    if(v == 0) {
        return 1;
    }
    // Or can do 'v += (v == 0);' and then continue

    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;

    return v;
}

// Slower but more obvious method
unsigned int obvious(unsigned int v) {
    // Is v a power of 2?
    if((v & (v - 1)) == 0) {
        // 0 should round up to 1
        v += (v == 0);
        return v;
    }
    else {
        // Find the MSB
        unsigned int bit = 1;
        while(v >>= 1) {
            bit++;
        }

        // Set the bit to the left of the MSB, unless it would wrap-around
        if(bit < 32) {
            return 1 << bit;
        }
        else {
            return 0;
        }
    }
}

int main() {
    cout << "Round up to the next highest power of 2:" << endl;
    for(unsigned int i = 0; i < 11; i++) {
        cout << i << ": " << roundup(i) << " " << obvious(i) << endl;
    }
    cout << UINT_MAX << ": " << roundup(UINT_MAX) << " " << obvious(UINT_MAX) << endl;
}
