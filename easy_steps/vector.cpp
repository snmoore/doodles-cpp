#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec(3, 100);

    cout << "Vector size:     " << vec.size() << endl;
    cout << "Vector capacity: " << vec.capacity() << endl;
    cout << "Is empty?:       " << vec.empty() << endl;
    cout << "First element:   " << vec.front() << endl;
    cout << endl;

    vec.pop_back(); // remove the final element
    cout << "Vector size:     " << vec.size() << endl;
    cout << "Final element:   " << vec.back() << endl;
    cout << endl;

    vec.clear();    // remove all elements
    cout << "Vector size:     " << vec.size() << endl;
    cout << "Vector capacity: " << vec.capacity() << endl;
    cout << "Is empty?:       " << vec.empty() << endl;
    cout << endl;

    vec.push_back(200); // add an element
    cout << "Vector size:     " << vec.size() << endl;
    cout << "Vector capacity: " << vec.capacity() << endl;
    cout << "First element:   " << vec.front() << endl;
    cout << endl;

    vec[0] = 25; // change an element, without range checking
    cout << "vec[0]:          " << vec[0] << endl;
    cout << endl;

    vec.at(0) = 50; // change an element, with range checking
    cout << "vec.at(0):       " << vec.at(0) << endl;
    cout << endl;

    return 0;
}

