#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string line;
    int i;

    ifstream reader("poem.txt");
    if(!reader) {
        cout << "Error opening file for input" << endl;
        return -1;
    }

    for(i = 0; !reader.eof(); i++) {
        getline(reader, line);
        cout << line << endl;
    }

    reader.close();
    cout << "Iterations: " << i << endl;

    return 0;
}



