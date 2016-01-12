#include <iostream>

using namespace std;

float computeArea(float diameter);
float computeArea(float width, float height);
float computeArea(char letter, float width, float height);

int main() {
    float num, area;

    cout << "Enter diameter in feet: ";
    cin >> num;

    area = computeArea(num);
    cout << "Circle area = " << area << "sq.ft." << endl;

    area = computeArea(num, num);
    cout << "Square area = " << area << "sq.ft." << endl;

    area = computeArea('T', num, num);
    cout << "Triangle area = " << area << "sq.ft." << endl;

    return 0;
}

float computeArea(float diameter) {
    float radius = diameter / 2;
    return 3.141593 * radius * radius;
}

float computeArea(float width, float height) {
    return width * height;
}

float computeArea(char letter, float width, float height) {
    return (width / 2) * height;
}
