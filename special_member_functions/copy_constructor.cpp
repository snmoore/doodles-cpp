// Compiler generated copy constructor
//      copy constructor            T(const T& rhs)
//
//  This is used in the following circumstances:
//      copy constructor            T b(a)
//                                  T b = a
//                                  T b{a}
//
//  This is only generated if:
//      no move constructor and move assignment operator are explicitly declared
//      no destructor is explicitly declared (C++11)

//  This performs the following actions:
//      construct all the object's members from the corresponding members of the
//      copy constructor's argument, calling the copy constructors of the
//      object's class-type members, and doing a plain assignment of all
//      non-class type (e.g., int or pointer) data members

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

    // Copy constructor
    cout << endl << "Copy constructor:" << endl;

    cout << left << setw(20) << "Vector b(a)";
    Vector b(a);        // compiler generates the copy constructor
    b.print();          // calls copy constructors for each class-type member
                        // but plain assignment for non-class types e.g. int, ptr

    cout << left << setw(20) << "Vector c = a";
    Vector c = a;       // compiler generates the copy constructor
    c.print();          // calls copy constructors for each class-type member
                        // but plain assignment for non-class types e.g. int, ptr

    cout << left << setw(20) << "Vector d{a}";
    Vector d{a};        // compiler generates the copy constructor
    d.print();          // calls copy constructors for each class-type member
                        // but plain assignment for non-class types e.g. int, ptr

    cout << endl << left << setw(20) << "Change a: ";
    a.fill(11);         // fill a with 11 12 13 14 15 16 17 18 19 20
    a.print();
    cout << left << setw(20) << "b.data is a.data: ";
    b.print();
    cout << left << setw(20) << "c.data is a.data: ";
    c.print();
    cout << left << setw(20) << "d.data is a.data: ";
    d.print();
}
