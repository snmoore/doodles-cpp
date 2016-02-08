// Compiler generated default constructor:
//      default constructor         T()
//
//  This is used in the following circumstances:
//      default constructor         T a
//                                  T a {}
//                                  T a = {}
//
//  This is only generated if:
//      no other constructor is explicitly declared
//
//  This performs the following actions:
//      call the destructors of all the object's class-type members

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

    void print() const;                     // print the vector

private:
    int size;
    int* data;
};

// Print the vector
void Vector::print() const {
    cout << "size = " << size << ", data = " << data << endl;
}

int main() {
    // Default constructor
    cout << endl << "Default constructor:" << endl;

    cout << left << setw(20) << "Vector a";
    Vector a;           // compiler generates the default constructor
    a.print();

    cout << left << setw(20) << "Vector b {}";
    Vector b {};        // compiler generates the default constructor
    b.print();          // will *not* call a constructor that takes a
                        // std::initializer_list if one is present

    cout << left << setw(20) << "Vector c = {}";
    Vector c = {};      // compiler generates the default constructor
    c.print();          // will *not* call a constructor that takes a
                        // std::initializer_list if one is present
}