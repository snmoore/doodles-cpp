#include <iostream>

using namespace std;

class Dog {
    // private by default
    int age, weight;
    string colour;

public:
    Dog();
    Dog(int, int);
    Dog(int, int, string);
    ~Dog();
    void bark() { cout << "WOOF!" << endl; }
    void bark(string noise) { cout << noise << endl; }
    int getAge() { return age; }
    int getWeight() { return weight; }
    string getColour() { return colour; }
};

Dog::Dog() {
    age = 1;
    weight = 2;
    colour = "black";
}

Dog::Dog(int age, int weight) {
    this->age = age;
    this->weight = weight;
    colour = "white";
}

Dog::Dog(int age, int weight, string colour) {
    this->age = age;
    this->weight = weight;
    this->colour = colour;
}

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

    Dog rex;
    cout << "Rex is a " << rex.getAge();
    cout << " year old " << rex.getColour();
    cout << " dog who weighs " << rex.getWeight();
    cout << " lbs.";
    rex.bark("GRRR!");

    Dog sammy(2, 6);
    cout << "Sammy is a " << sammy.getAge();
    cout << " year old " << sammy.getColour();
    cout << " dog who weighs " << sammy.getWeight();
    cout << " lbs.";
    sammy.bark("BOWOW!");

    return 0;
}
