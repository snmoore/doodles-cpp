// Special member functions:
//      default constructor         T()
//      copy constructor            T(const T& rhs)
//      copy assignment operator    T& operator=(const T& rhs)
//      move constructor            T(T&& rhs)
//      move assignment operator    T& operator=(T&& rhs)
//      destructor                  ~T
//
//  These are used in the following circumstances:
//      default constructor         T a
//                                  T a {}
//                                  T a = {}
//                                  T a = T()
//                                  T* a = new T
//
//      copy constructor            T b(a)
//                                  T b = a
//                                  T b{a}
//
//      copy assignment operator    b = a
//
//      move constructor            T b(std::move(a))
//                                  T b = std::move(a)
//                                  T b{std::move(a)}
//
//      move assignment operator    b = std::move(a)
//                                  return a
//
//      destructor                  object goes out of scope
//                                  delete a

#include <iomanip>      // For setw
#include <iostream>     // For cout etc
#include <utility>      // For move

using namespace std;

class Vector {
public:
    Vector();                               // default constructor
    Vector(const Vector& rhs);              // copy constructor
    Vector& operator=(const Vector& rhs);   // copy assignment operator: clean up target and copy
    Vector(Vector&& rhs);                   // move constructor
    Vector& operator=(Vector&& rhs);        // move assignment operator: clean up target and move
    ~Vector();                              // destructor

    void fill(int first);                   // fill the vector with values
    void print() const;                     // print the vector

private:
    int size;
    int* data;
};

// Default constructor
Vector::Vector() : size(10), data(new int[size]) {
    cout << "Default constructor was called, ";
    print();
}

// Copy constructor
Vector::Vector(const Vector& rhs) :size(rhs.size), data(new int[rhs.size]) {
    // Copy the elements
    for(int i = 0; i < size; i++) {
        data[i] = rhs.data[i];
    }

    cout << "Copy constructor was called, ";
    print();
}

// Copy assignment operator: clean up target and copy
Vector& Vector::operator=(const Vector& rhs) {
    // Release the old resources
    delete[] data;

    // Allocate new resources
    size = rhs.size;
    data = new int[size];

    // Copy the elements
    for(int i = 0; i < size; i++) {
        data[i] = rhs.data[i];
    }

    cout << "Copy assignment operator was called, ";
    print();

    // Enable chains of assignments (see Effective C++, 2nd ed., item 15)
    return *this;
}

// Move constructor
Vector::Vector(Vector&& rhs)
    // Steal the elements from rhs
    :size(rhs.size), data(rhs.data)
{
    // rhs now has no elements
    rhs.size = 0;
    rhs.data = nullptr;

    cout << "Move constructor was called, ";
    print();
}

// Move assignment operator: clean up target and move
Vector& Vector::operator=(Vector&& rhs) {
    // Release the old resources
    delete[] data;

    // Steal the elements from rhs
    size = rhs.size;
    data = rhs.data;

    // rhs now has no elements
    rhs.size = 0;
    rhs.data = nullptr;

    cout << "Move assignment operator was called, ";
    print();

    // Enable chains of assignments (see Effective C++, 2nd ed., item 15)
    return *this;
}

// Destructor
Vector::~Vector() {
    delete[] data;
    cout << "Destructor was called" << endl;
}

// Fill the vector with values
void Vector::fill(int first) {
    for(int i = 0; i < size; i++) {
        data[i] = first + i;
    }
}

// Print the vector
void Vector::print() const {
    cout << "size = " << size << ", data = ";
    for(int i = 0; i < size; i++) {
        cout << setw(2) << data[i] << " ";
    }
    cout << endl;
}

int main() {
    // Default constructor
    cout << endl << "Default constructor:" << endl;

    cout << left << setw(25) << "Vector a";
    Vector a;               // calls the default constructor

    cout << left << setw(25) << "Vector b {}";
    Vector b {};            // calls the default constructor
                            // will *not* call a constructor that takes a
                            // std::initializer_list if one is present

    cout << left << setw(25) << "Vector c = {}";
    Vector c = {};          // calls the default constructor
                            // will *not* call a constructor that takes a
                            // std::initializer_list if one is present

    cout << left << setw(25) << "Vector d = Vector()";
    Vector d = Vector();    // calls the default constructor

    cout << left << setw(25) << "Vector* e = new Vector";
    Vector* e = new Vector; // calls the default constructor


    // Fill in some data values
    cout << endl << "Fill a: ";
    a.fill(1);              // fill a with 1 2 3 4 5 6 7 8 9 10
    a.print();

    cout << "Fill b: ";
    b.fill(11);             // fill b with 11 12 13 14 15 16 17 18 19 20
    b.print();

    cout << "Fill c: ";
    c.fill(21);             // fill c with 21 22 23 24 25 26 27 28 29 30
    c.print();

    cout << "Fill d: ";
    d.fill(31);             // fill d with 31 32 33 34 35 36 37 38 39 40
    d.print();

    cout << "Fill e: ";
    e->fill(41);             // fill e with 41 42 43 44 45 46 47 48 49 50
    e->print();


    // Copy constructor
    cout << endl << "Copy constructor:" << endl;

    cout << left << setw(20) << "Vector f(a)";
    Vector f(a);            // calls the copy constructor

    cout << left << setw(20) << "Vector g = b";
    Vector g = b;           // calls the copy constructor

    cout << left << setw(20) << "Vector h{c}";
    Vector h{c};            // calls the copy constructor
                            // will call (by preference) a constructor that takes a
                            // std::initializer_list if one is present


    // Copy assignment operator
    cout << endl << "Copy assignment operator:" << endl;

    cout << left << setw(20) << "h = d";
    h = d;                  // calls the copy assignment operator


    // Move constructor
    cout << endl << "Move constructor:" << endl;

    cout << left << setw(20) << "Vector i(move(a))";
    Vector i(move(a));      // calls the move constructor

    cout << left << setw(20) << "Vector j = move(b)";
    Vector j = move(b);     // calls the move constructor

    cout << left << setw(20) << "Vector k{move(c)}";
    Vector k{move(c)};      // calls the move constructor

    // Check the moved objects
    cout << endl << "Moved a: ";
    a.print();
    cout << "Moved b: ";
    b.print();
    cout << "Moved c: ";
    c.print();


    // Move assignment operator
    cout << endl << "Move assignment operator:" << endl;

    cout << left << setw(20) << "k = move(d)";
    k = move(d);        // calls the move assignment operator

    // Check the moved objects
    cout << endl << "Moved d: ";
    d.print();
    cout << endl;
}
