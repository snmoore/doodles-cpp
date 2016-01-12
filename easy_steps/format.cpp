#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    const int RANGE = 12;
    string table[RANGE];
    int i = 0, j = 0;

    ifstream reader("records.txt");
    if(!reader) {
        cout << "Error opening input file" << endl;
        return -1;
    }

    while(!reader.eof()) {
        if((i+1) % 4 == 0) {
           getline(reader, table[i++], '\n');
        }
        else {
           getline(reader, table[i++], '\t');
        }
    }

    reader.close();
    i = 0;

    while(i < RANGE) {
        cout << endl << "Record number: " << ++j << endl;
        cout << "Forename: " << table[i++] << endl;
        cout << "Surname: " << table[i++] << endl;
        cout << "Department: " << table[i++] << endl;
        cout << "Telephone: " << table[i++] << endl;
    }

    return 0;
}



