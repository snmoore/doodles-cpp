#include <iostream>

using namespace std;

class Dog {
    // private by default
    int age, weight;
    string colour;

public:
    void bark() { cout << "WOOF!" << endl; }
    void setValues(int, int, string);
    int getAge() { return age; }
    int getWeight() { return weight; }
    string getColour() { return colour; }
};

void Dog::setValues(int age, int weight, string colour) {
    this->age = age;
    this->weight = weight;
    this->colour = colour;
}

int main() {
    Dog fido;
    fido.setValues(3, 15, "brown");
    cout << "Fido is a " << fido.getColour() << " dog" << endl;
    cout << "Fido is " << fido.getAge() << " years old" << endl;
    cout << "Fido weighs " << fido.getWeight() << " lbs" << endl;
    fido.bark();

    Dog pooch;
    pooch.setValues(4, 18, "grey");
    cout << "Pooch is a " << pooch.getAge();
    cout << " year old " << pooch.getColour();
    cout << " dog who weighs " << pooch.getWeight();
    cout << " lbs.";
    pooch.bark();

    return 0;
}
