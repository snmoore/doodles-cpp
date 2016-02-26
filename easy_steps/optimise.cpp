#include <iostream>

using namespace std;

// Optimised recursive function to compute the factorial of n
inline unsigned int factorial(unsigned int n) { return n <= 1 ? 1 : n*factorial(n-1); }

// Recursive function to compute the factorial of n
#if 0
unsigned int factorial(unsigned int n) {
    int result;

    if(n <= 1) {
        result = 1;
    }
    else {
        result = factorial(n-1) * n;
    }
    return result;
}
#endif

// Recursive function to compute a range of factorials from num..max
void computeFactorials(unsigned int num, unsigned int max) {
   cout << "Factorial of " << num << " is " << factorial(num) << endl;
   num++;
   if(num <= max) {
       computeFactorials(num, max);
   }
}

int main() {
    // Compute 0!, 1!, 2! .. 8!
    computeFactorials(0, 8);
}
