// Compiler generated copy assignment operator
//      copy assignment operator    T& operator=(const T& rhs)
//
//  This is used in the following circumstances:
//      copy assignment operator    b = a
//
//  This is only generated if:
//      no move constructor and move assignment operator are explicitly declared
//      no destructor is explicitly declared (C++11)
//
//  This performs the following actions:
//      assign all the object's members from the corresponding members of the
//      assignment operator's argument, calling the copy assignment operators of
//      the object's class-type members, and doing a plain assignment of all
//      non-class type (e.g. int or pointer) data members

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
    int size;
    int* data;
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

    // Copy assignment operator
    cout << endl << "Copy assignment operator:" << endl;

    cout << left << setw(20) << "b = a";
    Vector b;
    b = a;              // compiler generates the copy assignment operator
    b.print();          // calls copy assignment operator for each class-type member
                        // but plain assignment for non-class types e.g. int, ptr

    cout << endl << left << setw(20) << "Change a: ";
    a.fill(11);         // fill a with 11 12 13 14 15 16 17 18 19 20
    a.print();
    cout << left << setw(20) << "b.data is a.data: ";
    b.print();
}
