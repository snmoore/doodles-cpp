#include <iostream>
#include <string>

using namespace std;

int main() {
    string text = "9";
    string term("9 ");
    string info = "Toys";
    string colour;

    char hue[4] = { 'R', 'e', 'd', '\0' };
    colour = hue;

    info = " Balloons";

    text += term + colour + info;
    cout << text << endl;

    return 0;
}
