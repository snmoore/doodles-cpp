#include <iostream>

using namespace std;

class Man {
public:
    void speak() { cout << "Man: Hello!" << endl; }
    void speak(string msg) { cout << "Man: " << msg << endl; }
};

class Hombre : public Man {
public:
    void speak(string msg) { cout << "Hombre: " << msg << endl; }
};

int main() {
    Man henry;
    henry.speak();
    henry.speak("It's a beautiful evening.");

    Hombre enrique;
    enrique.speak("Hola!");
    enrique.Man::speak("Es una tarde hermosa.");

    return 0;
}
