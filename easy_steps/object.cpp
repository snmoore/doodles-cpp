#include <iostream>

using namespace std;

class Dog {
    // private by default
    int age, weight;
    string colour;

public:
    void bark() { cout << "WOOF!" << endl; }
    void setAge(int years) { age = years; }
    void setWeight(int pounds) { weight = pounds; }
    void setColour(string clr) { colour = clr; }
    int getAge() { return age; }
    int getWeight() { return weight; }
    string getColour() { return colour; }
};


int main() {
    Dog fido;

    fido.setAge(3);
    fido.setWeight(15);
    fido.setColour("brown");

    cout << "Fido is a " << fido.getColour() << " dog" << endl;
    cout << "Fido is " << fido.getAge() << " years old" << endl;
    cout << "Fido weighs " << fido.getWeight() << " lbs" << endl;

    fido.bark();

    return 0;
}
