// Count the number of bits set in a 32-bit word
//
// See https://graphics.stanford.edu/~seander/bithacks.html

#include <bitset>   // For std::bitset
#include <iomanip>  // For std::setw
#include <iostream> // For std::cout etc
#include <string>   // For std::string

#define NELEMENTS(array)    ((sizeof(array))/(sizeof(array[0])))

// Obvious implementation to count the number of bits, up to 32 iterations
unsigned int obvious(unsigned int value) {
    // Check each bit and count
    unsigned int bits {0};
    for(; value; value >>= 1) {
        bits += value & 1;
    }
    return bits;
}

// Obvious implementation with shortcut, up to 32 iterations
unsigned int shortcut(unsigned int value) {
    // Shortcut on powers-of-2
    if((value & (value - 1)) == 0) {    // is value a power-of-2?
        return value != 0;              // 0 is not really a power-of-2
    }

    // Check each bit and count
    unsigned int bits {0};
    for(; value; value >>= 1) {
        bits += value & 1;
    }
    return bits;
}

// Kernighan's method, only as many iterations as there are bits set
unsigned int kernighan(unsigned int value) {
    // Count bits whilst clearing the LSB
    unsigned int bits {0};
    for(; value; bits++) {
        value &= value - 1;
    }
    return bits;
}

// Test a given implementation
void test(unsigned int (*function)(unsigned int value), std::string label) {
    const unsigned int tests[] = {
            0, 1, 2, 3, 4, 5, 7, 8, 9, 10,
            8, 16, 32, 64, 128, 256, 512,
            0xFF, 0xFFFF, 0xFFFFFF, 0xFFFFFFFF
    };

    std::cout << label << ":" << std::endl;
    for(size_t i = 0; i < NELEMENTS(tests); i++) {
        std::cout << std::setw(10) << std::showbase << std::hex << tests[i];
        std::cout << std::setw(34) << std::bitset<32>(tests[i]);
        std::cout << std::setw(4) << std::dec << function(tests[i]);
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    // Test the obvious implementation
    test(obvious, "Obvious");

    // Test the obvious implementation with shortcut
    test(shortcut, "Obvious with shortcut");

    // Test Kernighan's method
    test(kernighan, "Kernighan's Method");
}
