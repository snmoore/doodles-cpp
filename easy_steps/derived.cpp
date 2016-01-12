#include <iostream>

using namespace std;

class Polygon {
protected:
    int width, height;

public:
    void setValues(int w, int h) { width = w; height = h; }
};

class Rectangle : public Polygon {
public:
    int area() { return width * height; }
};

class Triangle : public Polygon {
public:
    int area() { return (width / 2) * height; }
};


int main() {
    Rectangle rect;
    rect.setValues(4, 5);
    cout << "Rectangle area: " << rect.area() << endl;

    Triangle tri;
    tri.setValues(4, 5);
    cout << "Triangle area: " << tri.area() << endl;

    return 0;
}
