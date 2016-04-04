// Compiler generated move assignment operator
//      move assignment operator    T& operator=(T&& rhs)
//
//  This is used in the following circumstances:
//      move assignment operator    b = std::move(a)
//                                  return a
//
//  This is only generated if:
//      no copy constructor, copy assignment operator, move constructor and
//      destructor are explicitly declared
//
//  This performs the following actions:
//      moves the source object members
//      - which could just be a copy for simple types like int, ptr
//      unclear if it clears/initialises the source object members
//       - it does not appear to in this specific example

#include <iomanip>      // For setw
#include <iostream>     // For cout etc
#include <utility>      // For move

using namespace std;

class Vector {
public:
    // No default constructor
    // No copy constructor
    // No copy assignment operator
    // No move constructor
    // No move assignment operator
    // No destructor defined

    void fill(int first);                   // fill the vector with values
    void print() const;                     // print the vector

private:
    int size  = {0};
    int* data = {nullptr};
};

// Fill the vector with values
void Vector::fill(int first) {
    if(data == nullptr) {
        size = 10;
        data = new int[size];
    }

    // Fill
    for(int i = 0; i < size; i++) {
        data[i] = first + i;
    }
}

// Print the vector
void Vector::print() const {
    cout << "size = " << size << ", data = " << data;

    if(data != nullptr) {
        cout << ", values = ";
        for(int i = 0; i < size; i++) {
            cout << setw(2) << data[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    // Object to copy
    cout << endl << "Object to copy:" << endl;

    cout << left << setw(20) << "Vector a";
    Vector a;           // compiler generates the default constructor
    a.print();

    cout << left << setw(20) << endl << "Fill a: ";
    a.fill(1);          // fill a with 1 2 3 4 5 6 7 8 9 10
    a.print();

    // Move assignment operator
    cout << endl << "Move assignment operator:" << endl;

    cout << left << setw(20) << "b = move(a)";
    Vector b;
    b = move(a);        // compiler generates the move assignment operator
    b.print();          // this does not clear a.data or a.size in this case

    // Check the moved objects
    cout << left << setw(20) << endl << "Moved a: ";
    a.print();
    cout << endl;
}
