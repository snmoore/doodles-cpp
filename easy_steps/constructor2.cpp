#include <iostream>

using namespace std;

class Dog {
    // private by default
    int age, weight;
    string colour;

public:
    Dog(int age, int weight, string colour) :age(age), weight(weight), colour(colour) {}
//    Dog(int age, int weight, string colour);
    ~Dog();
    void bark() { cout << "WOOF!" << endl; }
    int getAge() { return age; }
    int getWeight() { return weight; }
    string getColour() { return colour; }
};

//Dog::Dog(int age, int weight, string colour) {
//    this->age = age;
//    this->weight = weight;
//    this->colour = colour;
//}

Dog::~Dog() {
    cout << "Object destroyed." << endl;
}

int main() {
    Dog fido(3, 15, "brown");
    cout << "Fido is a " << fido.getColour() << " dog" << endl;
    cout << "Fido is " << fido.getAge() << " years old" << endl;
    cout << "Fido weighs " << fido.getWeight() << " lbs" << endl;
    fido.bark();

    Dog pooch(4, 18, "grey");
    cout << "Pooch is a " << pooch.getAge();
    cout << " year old " << pooch.getColour();
    cout << " dog who weighs " << pooch.getWeight();
    cout << " lbs.";
    pooch.bark();

    return 0;
}
