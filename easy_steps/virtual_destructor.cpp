#include <iostream>

using namespace std;

class Base {
public:
    Base() :age(60) {
        cout << "Base constructor, age = " << age << endl;
    }

    // Because derived and again use a base class pointer, only the base class
    // destructor will be called unless it is declared virtual
    //
    // When declared virtual the derived and again destructors will be called
    virtual ~Base() {
        cout << "Base destructor" << endl;
    }

protected:
    int age;
};

class Derived : public Base {
public:
    Derived() {
        age = 40;
        cout << "Derived constructor, age = " << age << endl;
    }

    ~Derived() {
        cout << "Derived destructor" << endl;
    }
};

class Again : public Derived {
public:
    Again() {
        age = 20;
        cout << "Again constructor, age = " << age << endl;
    }

    ~Again() {
        cout << "Again destructor" << endl;
    }
};

int main() {
    cout << "Base:" << endl;
    Base* base = new Base;
    delete base;

    cout << endl << "Derived:" << endl;
    Base* derived = new Derived;
    delete derived;

    cout << endl << "Again:" << endl;
    Base* again = new Again;
    delete again;
}
