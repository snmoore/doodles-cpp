// Sort a vector using insertion sort
//
// Insertion sort compares an item against those to the left, maintaining the
// sorted set on the left and the unsorted set on the right, and iterates until
// the entire set is sorted
//
// Executes in O(n^2) time

#include <algorithm>    // For move
#include <iostream>     // For std:cout etc
#include <string>       // For std::string
#include <vector>       // For std::vector

// Insertion sort, moving one element at a time
void sort_one(std::vector<int>& data) {
    // Work rightwards from the second element
    for(int j = 1; j < static_cast<int>(data.size()); j++) {
        // The current element will be overwritten
        int value = data[j];

        // Sort by comparing the current element to the elements to the left
        int i = j - 1;
        while(i >= 0 && value < data[i]) {
            // Move the larger element rightwards
            data[i + 1] = data[i];
            i--;
        }
        // Move the smaller element leftwards
        data[i + 1] = value;
    }
}

// Insertion sort, moving elements as a block
void sort_move(std::vector<int>& data) {
    // Work rightwards from the second element
    for(int j = 1; j < static_cast<int>(data.size()); j++) {
        // The current element will be overwritten
        int value = data[j];

        // Sort by comparing the current element to the elements to the left
        int i = j - 1;
        while(i >= 0 && value < data[i]) {
            --i;
        }
        // Move the larger elements rightwards
        std::move(data.begin() + i, data.begin() + j, data.begin() + i + 1);
        // std::move(&data[i], &data[j], &data[i + 1]);

        // Move the smaller element leftwards
        data[i + 1] = value;
    }
}

// Print all the elements of a vector
void print(const std::vector<int>& data) {
    for(auto iter : data) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}

// Test an implementation
void test(void (*function)(std::vector<int>& data), const std::string& label) {
    std::cout << label << ":" << std::endl;

    std::vector<int> data = { 23, 21, 76, 16, 52, 43 };
    std::cout << "\tUnsorted: ";
    print(data);

    function(data);
    std::cout << "\tSorted:   ";
    print(data);

    std::cout << std::endl;
}

int main() {
    // Test insertion sort, moving one element at a time
    test(sort_one, "Moving one element at a time");

    // Test insertion sort, moving elements as a block
    test(sort_move, "Moving elements as a block");
}
