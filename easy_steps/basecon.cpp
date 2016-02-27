#include <iostream>

using namespace std;

class Parent {
public:
    Parent() { cout << "Default Parent constructor called." << endl; }
    Parent(int a) { cout << "Overloaded Parent constructor called." << endl; }
};

class Daughter : public Parent {
public:
    Daughter() { cout << "Derived Daughter constructor called." << endl; }
};

class Son : public Parent {
public:
    // Calls the overloaded parent constructor first
    Son(int a) : Parent(a) { cout << "Derived Son overloaded constructor called." << endl; }

    // Calls the default parent constructor first
    // Son(int a) { cout << "Derived Son overloaded constructor called." << endl; }
};


int main() {
    Daughter emma;
    Son andrew(0);

    return 0;
}
