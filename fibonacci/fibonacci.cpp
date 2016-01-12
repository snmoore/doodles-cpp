// Generate the first 13 terms of the Fibonacci sequence:
//      0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ...
//
// In mathematical terms, the sequence Fn of Fibonacci numbers is defined by the recurrence relation
//      F{n} = F{n-1} + F{n-2}
//  with seed values
//      F{1} = 1, F{2} = 1
//  or (modern usage)
//      F{0} = 0, F{1} = 1
//
// See https://en.wikipedia.org/wiki/Fibonacci_number

#include <iostream>     // For cout etc

using namespace std;

// Value of the nth term of the Fibonacci sequence, using iteration
unsigned int iterative(unsigned int n) {
    if(n <= 1) {
        return n;
    }
    else {
        unsigned int Fn   = 0;
        unsigned int Fn_1 = 1;
        unsigned int Fn_2 = 0;
        for(unsigned int i = 2; i <= n; i++) {
            Fn   = Fn_1 + Fn_2;
            Fn_2 = Fn_1;
            Fn_1 = Fn;
        }
        return Fn;
    }
}

// Value of the nth term of the Fibonacci sequence, using recursion
unsigned int recursive(unsigned int n) {
    if(n <= 1) {
        return n;
    }
    else {
        return recursive(n-1) + recursive(n-2);
    }
}

int main(void) {
    cout << "Iterative:" << endl;
    for(unsigned int n = 0; n < 13; n++) {
        cout << iterative(n) << " ";
    }
    cout << endl;

    cout << "Recursive:" << endl;
    for(unsigned int n = 0; n < 13; n++) {
        cout << recursive(n) << " ";
    }
    cout << endl;
}
