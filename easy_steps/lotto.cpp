#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main() {
    int i, j, k;
    int nums[50];

    // Seed the random number generator with the current time
    srand((int)time(0));

    // Fill array elements 1..49 with integers 1..49
    for(i = 1; i < 50; i++) {
        nums[i] = i;
    }

    // Randomise the values in array elements 1..49
    for(i = 1; i < 50; i++) {
        j = (rand() % 49) + 1;      // random number in the range 1..49
        k       = nums[i];          // swap elements i and j
        nums[i] = nums[j];
        nums[j] = k;
    }

    // Output the first six numbers
    cout << "Your lucky numbers are: ";
    for(i = 1; i < 50; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}
