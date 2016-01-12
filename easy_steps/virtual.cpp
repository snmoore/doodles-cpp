#include <iostream>

using namespace std;

class Parent {
public:
    void Common() const {
        cout << "I am part of this family, ";
    }

    virtual void Identify() const {
        cout << "I am the parent" << endl;
    }
};

class Child : public Parent {
public:
    void Identify() const {
        cout << "I am the child" << endl;
    }
};

class Grandchild : public Child {
public:
    void Identify() const {
        cout << "I am the grandchild" << endl;
    }

    void Relate() const {
        cout << "Grandchild has parent and grandparent" << endl;
    }
};

int main() {
    Child son;
    Grandchild grandson;

    Parent* ptrChild = &son;
    Parent* ptrGrandchild = &grandson;

    ptrChild->Common();             // inherited
    ptrChild->Identify();           // overriding

    ptrGrandchild->Common();        // inherited
    ptrGrandchild->Identify();      // overriding

    ptrChild->Parent::Common();     // explicit
    ptrChild->Parent::Identify();   // explicit

    grandson.Relate();              // via instance

    return 0;
}
