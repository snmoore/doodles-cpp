#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string info = "The Ballad of Reading Gaol\n";
    info.append("Oscar Wilde, 1898\n");

    ofstream writer("poem.txt", ios::app);
    if(!writer) {
        cout << "Error opening file for output" << endl;
        return -1;
    }

    writer << info << endl;
    writer.close();

    return 0;
}



