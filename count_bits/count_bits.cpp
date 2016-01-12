// Count the number of bits set in a 32-bit word
//
// See https://graphics.stanford.edu/~seander/bithacks.html

#include <iostream>     // For cout etc

using namespace std;

// Count using the obvious method; 32 iterations
int obvious(unsigned int v) {
    int bits;
    for(bits = 0; v; v >>= 1) {
//        if(v & 1) {
//            bits++;
//        }
        bits += v & 1;
    }
    return bits;
}

// Count using Kernighan's method; as many iterations as there are bits set
int kernighan(unsigned int v) {
    int bits;
    for(bits = 0; v; bits++) {
        v &= v - 1; // clear the least significant bit
    }

    return bits;
}

int main(void) {
    unsigned int values[] = { 0, 1, 2, 3, 4, 5, 7, 8, 10, 64, 128, 255 };

    // Count the number of bits set using the obvious method
    cout << "Obvious method:" << endl;
    for(auto v : values) {
        cout << "Value: " << v << " Bits: " << obvious(v) << endl;
    }

    // Count the number of bits set using Kernighan's method
    cout << "Kernighan's method:" << endl;
    for(auto v : values) {
        cout << "Value: " << v << " Bits: " << kernighan(v) << endl;
    }
}
