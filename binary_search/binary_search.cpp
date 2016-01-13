// Find the position of a target value (a key) in a sorted array using a binary
// search.
//
// Compare the target value to the value at the middle element of the set.
// If equal, return the position of the middle element. If the target value is
// smaller than the value at the middle element then continue the search in the
// lower half of the set, otherwise continue the search in the upper half of the
// set. Repeat until the target value is found or there are no more elements
// left to search, in which case the target value is not present in the set.
//
// This typically executes in log_2(N) time
//
// See https://en.wikipedia.org/wiki/Binary_search_algorithm

#include <algorithm>    // For binary_search, find
#include <iostream>     // For cout etc
#include <vector>       // For vector

using namespace std;

const int NOT_FOUND {-1};

// Recursive binary search
int recursive(vector<int>& values, int key, int lower, int upper) {
    if(lower > upper) {
        // The key was not found
        return NOT_FOUND;
    }

    // Split the set into 2
    int midpoint = (lower + upper) / 2;

    if(key == values[midpoint]) {
        // Found the key
        return midpoint;
    }
    else if(key < values[midpoint]) {
        // Continue searching in the lower-half
        return recursive(values, key, lower, midpoint - 1);
    }
    else {
        // Continue searching in the upper-half
        return recursive(values, key, midpoint + 1, upper);
    }
}

// Iterative binary search
int iterative(vector<int>& values, int key) {
    size_t lower {0};
    size_t upper {values.size() - 1};

    while(lower <= upper) {
        // Split the set into 2
        int midpoint = (lower + upper) / 2;

        if(key == values[midpoint]) {
            // Found the key
            return midpoint;
        }
        else if(key < values[midpoint]) {
            // Continue searching in the lower-half
            upper = midpoint - 1;
        }
        else {
            // Continue searching in the upper-half
            lower = midpoint + 1;
        }
    }

    // The key was not found
    return NOT_FOUND;
}

// Built-in find (may not be a binary search!)
//
// std::binary_search() returns if a key is present or not, not its index
// std::find() returns an iterator to the first element if present
// std::distance() allows to find the index by comparing to the original vector
int builtin_find(vector<int>& values, int key) {
    auto iter = find(values.begin(), values.end(), key);

    if(iter != values.end()) {
        return distance(values.begin(),iter);
    }
    else {
        return NOT_FOUND;
    }
}

int main(void) {
    vector<int> values { 1, 2, 3, 4, 5, 7, 8, 9, 11, 13, 16, 17, 23, 27, 29, 32, 31, 37, 64, 81 };

    cout << "Recursive:  1 ==> " << recursive(values,  1, 0, values.size() - 1) << endl;
    cout << "Recursive:  3 ==> " << recursive(values,  3, 0, values.size() - 1) << endl;
    cout << "Recursive: 14 ==> " << recursive(values, 14, 0, values.size() - 1) << endl;
    cout << "Recursive: 81 ==> " << recursive(values, 81, 0, values.size() - 1) << endl;
    cout << endl;
    cout << "Iterative:  1 ==> " << iterative(values,  1) << endl;
    cout << "Iterative:  3 ==> " << iterative(values,  3) << endl;
    cout << "Iterative: 14 ==> " << iterative(values, 14) << endl;
    cout << "Iterative: 81 ==> " << iterative(values, 81) << endl;
    cout << endl;
    cout << "Built-in binary_search:   1 ==> " << boolalpha << binary_search(values.begin(), values.end(),  1) << endl;
    cout << "Built-in binary_search:   3 ==> " << boolalpha << binary_search(values.begin(), values.end(),  3) << endl;
    cout << "Built-in binary_search:  14 ==> " << boolalpha << binary_search(values.begin(), values.end(), 14) << endl;
    cout << "Built-in binary_search:  81 ==> " << boolalpha << binary_search(values.begin(), values.end(), 81) << endl;
    cout << endl;
    cout << "Built-in find:  1 ==> " << builtin_find(values,  1) << endl;
    cout << "Built-in find:  3 ==> " << builtin_find(values,  3) << endl;
    cout << "Built-in find: 14 ==> " << builtin_find(values, 14) << endl;
    cout << "Built-in find: 81 ==> " << builtin_find(values, 81) << endl;
}
