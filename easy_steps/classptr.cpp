#include <iostream>

using namespace std;

class Base {
public:
    void Identify(uintptr_t addr) const {
        cout << "Base class called by 0x" << hex << addr << endl;
    }
};

class SubA : public Base { };
class SubB : public Base { };

int main() {
    Base* ptrA = new SubA;
    Base* ptrB = new SubB;

    ptrA->Identify((uintptr_t)&ptrA);
    ptrB->Identify((uintptr_t)&ptrB);

    return 0;
}
