// Sort a vector using insertion sort
//
// Insertion sort compares an item against those to the left, maintaining the
// sorted set on the left and the unsorted set on the right, and iterates until
// the entire set is sorted
//
// Executes in O(n^2) time

#include <algorithm>    // For move
#include <iostream>     // For cout etc
#include <vector>       // For vector

using namespace std;

void print(vector<int> data) {
    for(auto value : data) {
        cout << value << " ";
    }
    cout << endl;
}

// Sort the elements, moving elements rightwards one at a time
void sort(vector<int>& data) {
    // Work rightwards through the vector, keeping sorted elements on the left
    for(int j = 1; j < (int)data.size(); j++) {
        // The value being sorted
        int value = data[j];

        // Compare against values to left to find the insertion point
        int i = j - 1;
        while((i >= 0) && (value < data[i])) {
            // Move the larger elements rightwards
            data[i+1] = data[i];
            i--;
        }
        // Insert the value at the insertion point
        data[i+1] = value;
    }
}

// Sort the elements, moving elements rightwards as a block
void sort_move(vector<int>& data) {
    // Work rightwards through the vector, keeping sorted elements on the left
    for(int j = 1; j < (int)data.size(); j++) {
        // The value being sorted
        int value = data[j];

        // Compare against values to left to find the insertion point
        int i = j - 1;
        while((i >= 0) && (value < data[i])) {
            i--;
        }

        // Move the larger elements rightwards as a block
        move(data.begin()+i, data.begin()+j, data.begin()+i+1);

        // Insert the value at the insertion point
        data[i+1] = value;
    }
}

int main() {
    // Start with some unsorted data
    vector<int> data = { 23, 21, 76, 16, 52, 43 };
    cout << "Unsorted:" << endl;
    print(data);

    // Sort the elements, moving elements rightwards one at a time
    sort(data);
    cout << endl << "Sorted:" << endl;
    print(data);

    // Some more unsorted data
    vector<int> more = { 11, 5, 3, 7, 9, 1 };
    cout << endl << "Unsorted:" << endl;
    print(more);

    // Sort the elements, moving elements rightwards one at a time
    sort_move(more);
    cout << endl << "Sorted:" << endl;
    print(more);
}
