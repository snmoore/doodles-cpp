#include <iostream>
#include <string>
#include <stdexcept>
#include <typeinfo>
#include <fstream>

using namespace std;

int main() {
    string lang = "C++";
    int num = 1000000000;   // one billion

    try {
//        lang.replace(100, 1, "C");
//        lang.resize(3*num);
        ifstream reader("nonesuch.txt");
        if(!reader) {
            throw logic_error("File not found");
        }
    }
    catch(out_of_range &err) {
        cerr << "Range exception: " << err.what() << endl;
        cerr << "Exception type: " << typeid(err).name() << endl;
        cerr << "Program terminated." << endl;
        return -1;
    }
    catch(exception &err) {
        cerr << "Range exception: " << err.what() << endl;
        cerr << "Exception type: " << typeid(err).name() << endl;
    }

    cout << "Program continues..." << endl;
    return 0;
}



