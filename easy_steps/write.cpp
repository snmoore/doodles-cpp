#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string poem = "I never saw a man who looked\n";
    poem.append("With such a wistful eye\n");
    poem.append("Upon that little tent of blue\n");
    poem.append("Which prisoners call the sky\n");

    ofstream writer("poem.txt");
    if(!writer) {
        cout << "Error opening file for output" << endl;
        return -1;
    }

    writer << poem << endl;
    writer.close();

    return 0;
}



