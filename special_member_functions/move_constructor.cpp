// Compiler generated move constructor:
//      move constructor            T(T&& rhs)
//
//  This is used in the following circumstances:
//      move constructor            T b(std::move(a))
//                                  T b = std::move(a)
//                                  T b{std::move(a)}
//  This is only generated if:
//      no copy constructor, copy assignment operator, move assignment operator
//      and destructor are explicitly declared
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
    // Objects to copy
    cout << endl << "Object to copy:" << endl;

    cout << left << setw(20) << "Vector a";
    Vector a;           // compiler generates the default constructor
    a.print();

    cout << left << setw(20) << "Vector b";
    Vector b;           // compiler generates the default constructor
    b.print();

    cout << left << setw(20) << "Vector c";
    Vector c;           // compiler generates the default constructor
    b.print();

    cout << left << setw(20) << endl << "Fill a: ";
    a.fill(1);          // fill a with 1 2 3 4 5 6 7 8 9 10
    a.print();

    cout << left << setw(20) << endl << "Fill b: ";
    b.fill(11);          // fill b with 11 12 13 14 15 16 17 18 19 20
    b.print();

    cout << left << setw(20) << endl << "Fill c: ";
    c.fill(11);          // fill a with 11 12 13 14 15 16 17 18 19 20
    c.print();

    // Move constructor
    cout << endl << "Move constructor:" << endl;

    cout << left << setw(20) << "Vector d(move(a))";
    Vector d(move(a));  // compiler generates the move constructor
    d.print();          // this does not clear a.data or a.size in this case

    cout << left << setw(20) << "Vector e = move(b)";
    Vector e = move(b); // compiler generates the move constructor
    e.print();          // this does not clear a.data or a.size in this case

    cout << left << setw(20) << "Vector f{move(c)}";
    Vector f{move(c)};  // compiler generates the move constructor
    f.print();          // this does not clear a.data or a.size in this case

    // Check the moved objects
    cout << endl << "Moved a: ";
    a.print();
    cout << "Moved b: ";
    b.print();
    cout << "Moved c: ";
    c.print();
}
