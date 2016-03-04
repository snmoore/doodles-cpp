// Generate numbers in the Fibonacci sequence
//
// In mathematical terms, the sequence Fn of Fibonacci numbers is defined by
// the recurrence relation
//      F{n} = F{n-1} + F{n-2}
//  with seed values
//      F{1} = 1, F{2} = 1
//  or (modern usage)
//      F{0} = 0, F{1} = 1
//
// The first 21 Fibonacci numbers are:
// F0 F1 F2 F3 F4 F5 F6 F7 F8 F9 F10 F11 F12 F13 F14 F15 F16 F17  F18  F19  F20
// 0  1  1  2  3  5  8  13 21 34 55  89  144 233 377 610 987 1597 2584 4181 6765
//
// See https://en.wikipedia.org/wiki/Fibonacci_number

#include <iostream> // For std:cout etc
#include <string>   // For std:string

// Iteratively calculate numbers in the Fibonacci sequence
unsigned int iterative(unsigned int n) {
    if(n <= 1) {
        return n;
    }
    else {
        unsigned int Fn_2 {0}; // F{0} = 0
        unsigned int Fn_1 {1}; // F{1} = 1
        unsigned int Fn   {0};
        for(unsigned int i = 2; i <= n; i++) {
            Fn   = Fn_1 + Fn_2;
            Fn_2 = Fn_1;
            Fn_1 = Fn;
        }
        return Fn;
    }
}

// Recursively calculate numbers in the Fibonacci sequence
unsigned int recursive(unsigned int n) {
    if(n <= 1) {
        return n;
    }
    else {
        return recursive(n - 1) + recursive(n - 2);
    }
}

// Test a given implementation
void test(unsigned int (*function)(unsigned int n), std::string label) {
    std::cout << label << ": ";
    for(unsigned int i = 0; i < 21; i++) {
        std::cout << function(i);
        std::cout << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Test the iterative implementation
    test(iterative, "Iterative");

    // Test the recursive implementation
    test(recursive, "Recursive");
}
