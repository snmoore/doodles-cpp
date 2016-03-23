// Sort a vector using quick sort, using the Lomuto partition scheme
//
// See https://en.wikipedia.org/wiki/Quicksort
//
// Executes in O(n log n) time, or O(n^2) in the worst case

#include <algorithm>    // For std::swap
#include <iostream>     // For std::cout et al
#include <vector>       // For std::vector

// Print all the elements of a vector
void print(const std::vector<int>& data) {
    for(auto iter : data) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}

size_t partition(std::vector<int>& data, size_t lo, size_t hi) {
    // Select the rightmost element as the pivot
    int pivot = data[hi];

    // Position to swap to
    size_t i = {lo};

    // Compare each element against the pivot and swap if less
    for(size_t j = lo; j < hi; j++) {
        // Swap lesser elements
        if(data[j] <= pivot) {
            std::swap(data[j], data[i]);
            i++;
        }
    }
    // Swap the pivot
    std::swap(data[hi], data[i]);

    // i is now the partition point
    return i;
}

// Quicksort split into two function
void quick_sort_split(std::vector<int>& data, size_t lo, size_t hi) {
    if(lo < hi) {
        // Sort and partition into left and right sub-arrays
        size_t p = partition(data, lo, hi);

        // Recurse into the left sub-array
        if(p > 0) { // avoid underflow
            quick_sort_split(data, lo, p - 1);
        }

        // Recurse into the right sub-array
        quick_sort_split(data, p + 1, hi);
    }
}

// Quicksort in a single function
void quick_sort_combined(std::vector<int>& data, size_t lo, size_t hi) {
    if(lo < hi) {
        // Select the rightmost element as the pivot
        int pivot = data[hi];

        // Start the partition point at the leftmost element
        size_t partition = {lo};

        // Compare each element against the pivot
        for(size_t i = lo; i < hi; i++) {
            if(data[i] <= pivot) {
                // Swap lesser elements with the partition element
                std::swap(data[i], data[partition]);

                // Move the partition rightwards
                partition++;
            }
        }

        // Swap the pivot with the partition element
        std::swap(data[hi], data[partition]);

        // Recurse into the sub-array left of the partition
        if(partition > 0) {  // guard against underflow
            quick_sort_combined(data, lo, partition - 1);
        }

        // Recurse into the sub-array right of the partition
        quick_sort_combined(data, partition + 1, hi);
    }
}

void test(std::vector<int>& data) {
    std::cout << "Unsorted: ";
    print(data);

    quick_sort_combined(data, 0, data.size() - 1);

    std::cout << "Sorted:   ";
    print(data);

    std::cout << std::endl;
}

int main() {
    std::vector<int> data = { 23, 21, 76, 16, 52, 43 };
    test(data);

    std::vector<int> data2 = { 1, 3, 9, 8, 2, 7, 5 };
    test(data2);

    std::vector<int> data3 = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    test(data3);
}
