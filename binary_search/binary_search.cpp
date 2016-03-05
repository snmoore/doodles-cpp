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

#include <algorithm>    // For std::binary_search
#include <iostream>     // For std::cout etc
#include <vector>       // For std::vector

const int NOT_FOUND {-1};

// Iterative binary search, returns index where key == values[index]
long int iterative(const std::vector<int>& values, const int key) {
    unsigned long int lower {0};
    unsigned long int upper {values.size() - 1};

    while(lower <= upper) {
        // Calculatr the midpoint
        unsigned long int midpoint = (lower + upper) / 2;

        // Is the key at the midpoint?
        if(key == values[midpoint]) {
            // Found the key
            return static_cast<int>(midpoint);
        }
        // Is the key within the lower half range?
        else if(key < values[midpoint]) {
            // Keep searching in the lower half
            upper = midpoint - 1;
        }
        // The key is within the upper half range
        else {
            // Keep searching in the upper half
            lower = midpoint + 1;
        }
    }

    // The key is not present
    return NOT_FOUND;
}

// Recursive binary search, returns index where key == values[index]
int recursive(const std::vector<int>& values, const int key, unsigned int lower, unsigned int upper) {
    // Is the key not present?
    if(lower > upper) {
        return NOT_FOUND;
    }

    // Find the midpoint
    unsigned int midpoint = (lower + upper) / 2;

    // Is the key at the midpoint?
    if(key == values[midpoint]) {
        // Found the key
        return static_cast<int>(midpoint);
    }
    // Is the key within the lower half range?
    else if(key < values[midpoint]) {
        // Keep searching in the lower half
        return recursive(values, key, lower, midpoint - 1);
    }
    // The key is within the upper half range
    else {
        // Keep searching in the upper half
        return recursive(values, key, midpoint + 1, upper);
    }
}

// Use std::find, returns index where key == values[index]
//
// Beware that this may not be implemented as a binary search
int builtin_find(const std::vector<int>& values, const int key) {
    // Find returns an iterator to the appropriate element
    auto iter = std::find(values.begin(), values.end(), key);
    if(iter == values.end()) {
        return NOT_FOUND;
    }
    else {
        // Distance allows us to calculate the index
        return distance(iter, values.begin());
    }
}

int main() {
    std::vector<int> values { 1, 2, 3, 4, 5, 7, 8, 9, 11, 13, 16, 17, 23, 27, 29, 32, 31, 37, 64, 81 };

    // Test the iterative implementation
    std::cout << "Iterative:  1 ==> " << iterative(values,  1) << std::endl;
    std::cout << "Iterative:  3 ==> " << iterative(values,  3) << std::endl;
    std::cout << "Iterative: 14 ==> " << iterative(values, 14) << std::endl;
    std::cout << "Iterative: 81 ==> " << iterative(values, 81) << std::endl;
    std::cout << std::endl;

    // Test the recursive implementation
    std::cout << "Recursive:  1 ==> " << recursive(values,  1, 0, values.size() - 1) << std::endl;
    std::cout << "Recursive:  3 ==> " << recursive(values,  3, 0, values.size() - 1) << std::endl;
    std::cout << "Recursive: 14 ==> " << recursive(values, 14, 0, values.size() - 1) << std::endl;
    std::cout << "Recursive: 81 ==> " << recursive(values, 81, 0, values.size() - 1) << std::endl;
    std::cout << std::endl;

    // Test std::binary_search
    std::cout << "std::binary_search:  1 ==> " << std::boolalpha << std::binary_search(values.begin(), values.end(),  1) << std::endl;
    std::cout << "std::binary_search:  3 ==> " << std::boolalpha << std::binary_search(values.begin(), values.end(),  3) << std::endl;
    std::cout << "std::binary_search: 14 ==> " << std::boolalpha << std::binary_search(values.begin(), values.end(), 14) << std::endl;
    std::cout << "std::binary_search: 81 ==> " << std::boolalpha << std::binary_search(values.begin(), values.end(), 81) << std::endl;
    std::cout << std::endl;

    // Test std::find
    std::cout << "Using std::find:  1 ==> " << builtin_find(values,  1) << std::endl;
    std::cout << "Using std::find:  3 ==> " << builtin_find(values,  3) << std::endl;
    std::cout << "Using std::find: 14 ==> " << builtin_find(values, 14) << std::endl;
    std::cout << "Using std::find: 81 ==> " << builtin_find(values, 81) << std::endl;
    std::cout << std::endl;
}
