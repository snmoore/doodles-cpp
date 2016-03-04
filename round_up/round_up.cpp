
#include <iomanip>  // For std:setw
#include <iostream> // For std::cout etc
#include <string>   // For std::string

#define NELEMENTS(array)    ((sizeof(array))/(sizeof(array[0])))

// Obvious implementation to round-up a number to the nearest power-of-2
unsigned int obvious(unsigned int value) {
    // Existing powers-of-2 should remain unchanged
    if((value & (value - 1)) == 0) {
        value += (value == 0); // 0 should round up to 1
        return value;
    }

    // Find the highest bit that is set, then set the next bit
    unsigned int bit {1};
    while(value >>= 1) {
        bit++;
    }
    return 1 << bit;
}

// Magic implementation to round-up a number to the nearest power-of-2
unsigned int magic(unsigned int value) {
    value += (value == 0);  // 0 should round up to 1

    value--;                // existing powers-of-2 should remain unchanged
    value |= value >>  1;   // set all the bits to the right of the MSB
    value |= value >>  2;
    value |= value >>  4;
    value |= value >>  8;
    value |= value >> 16;
    value++;                // increment to get the power-of-2

    return value;
}

// Test a given implementation
void test(unsigned int (*function)(unsigned int value), std::string label) {
    const unsigned int tests[] = {
            0, 1, 2, 3, 4, 5, 7, 8, 9, 10,
            7, 15, 31, 63, 127, 255, 511,
            8, 16, 32, 64, 128, 256, 512,
    };

    std::cout << label << ":" << std::endl;
    for(size_t i = 0; i < NELEMENTS(tests); i++) {
        std::cout << std::setw(3) << tests[i] << " : ";
        std::cout << std::setw(3) << function(tests[i]);
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    // Test the obvious implementation
    test(obvious, "Obvious");

    // Test the magic implementation
    test(magic, "Magic");
}
