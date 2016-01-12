#include <iostream>

using namespace std;

class Shape {
public:
    virtual int getArea() = 0;
    virtual int getEdge() = 0;
    virtual void Draw() = 0;
};

class Rect : public Shape {
public:
    Rect(int h, int w) :height(h), width(w) { }
    ~Rect();

    int getArea() { return height * width; }
    int getEdge() { return 2 * (height + width); }

    void Draw() {
        for(int h = 0; h < height; h++) {
            for(int w = 0; w < width; w++) {
                cout << "x ";
            }
            cout << endl;
        }
    }

private:
    int height, width;
};

int main() {
    Shape* pQuad = new Rect(3, 7);
    Shape* pSquare = new Rect(5, 5);

    pQuad->Draw();
    cout << "Area is " << pQuad->getArea() << endl;
    cout << "Perimeter is " << pQuad->getEdge() << endl;

    pSquare->Draw();
    cout << "Area is " << pSquare->getArea() << endl;
    cout << "Perimeter is " << pSquare->getEdge() << endl;

    return 0;
}
