// Find the median of a vector of values using quickselect
//
// This works like quicksort, but only recurses into one side – the side with
// the element it is searching for - and it can stop as soon as the partition
// reaches the median position
//
// This has an average case performance of O(n)
//
// See https://en.wikipedia.org/wiki/Quickselect

#include <algorithm>    // For std::swap
#include <iostream>     // For std::cout etc
#include <vector>       // For std::vector

// Print a vector of values
void print(const std::string& msg, const std::vector<int>& elements) {
    std::cout << msg;
    for(auto const& elem : elements) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Find the median in an vector of values using quickselect
int quickselect(std::vector<int>& data, size_t lo, size_t hi) {
    if(lo < hi) {
        // Select the rightmost element as the pivot
        int pivot = data[hi];

        // Partition using Lomuto partitioning
        size_t partition = lo;
        for(size_t i = lo; i < hi; i++) {
            // Move smaller elements to the left
            if(data[i] <= pivot) {
                // Swap the element with the partition
                std::swap(data[i], data[partition]);

                // Move the partition rightwards
                partition++;
            }
        }

        // Swap the pivot with the partition
        std::swap(data[hi], data[partition]);

        print("During:        ", data);

        // Is the partition at the mid-point?
        if(partition == (data.size() / 2)) {
            // Found the median
            return data[partition];
        }
        // Is the partition to the right of the mid-point?
        else if(partition > (data.size() / 2)) {
            // Recurse into the left partition
            return quickselect(data, lo, partition - 1);
        }
        // Is the partition to the left of the mid-point?
        else {
            // Recurse into the right partition
            return quickselect(data, partition + 1, hi);
        }
    }
    else {
        // Only one element left
        return data[lo];
    }
}

int main() {
    // Create an array of unsorted data
    std::vector<int> data = { 23, 21, 76, 16, 43, 52, 18 };
    print("Unsorted:      ", data);

    // Find the median using the quick select algorithm
    int median = quickselect(data, 0, data.size() - 1);
    print("Partly sorted: ", data);
    std::cout << "Median value:  " << median << std::endl;
}
