// A linked list using the STL
//
// Note that list does not provide for a sorted insert
// - using a set would be a better choice to maintain sorted order

#include <iostream>     // For cout etc
#include <list>         // For list

using namespace std;

// Comparison function for sorting
template <typename T>
int compare_function(const T& a, const T& b) {
    return a - b;   // -ve if a < b, +ve if a > b, 0 if a == b
}

template <typename T>
using compare_t = int (*)(const T& a, const T& b);

// Insert a new element in a list in sorted order
template <typename T>
void sorted_insert(list<T>& ll, const T& item, compare_t<T> compare) {
    // If the list is empty, insert at the head
    if(ll.empty()) {
        ll.push_front(item);
        return;
    }

    // Search through the list to find the appropriate insertion point
    for(auto iter = ll.begin(); iter != ll.end(); iter++) {
        // Do not insert duplicates
        if(compare(item, *iter) == 0) {
            throw runtime_error("Item already exists in the list");
        }

        // If the new item sorts before the current node, insert before it
        if(compare(item, *iter) < 0) {
            ll.insert(iter, item);
            return;
        }
    }

    // Reached the tail, append here
    ll.push_back(item);
}

// Print a representation of the list
template <typename T>
void print(const list<T>& ll) {
    cout << "Empty: " << boolalpha << ll.empty() << endl;
    cout << "Size: " << ll.size() << endl;
    if(ll.size() > 0) {
        cout << "Front: " << ll.front() << endl;
        cout << "Back: " << ll.back() << endl;
    }
    cout << "Contents: ";
    for(auto& node : ll) {
        cout << node << " ";
    }
    cout << endl;
}

int main() {
    // Create a list of integers
    list<int>* ll = new list<int>;
    cout << "Create a list:" << endl;
    print(*ll);

    // Insert some items into the list
    cout << endl << "Insert some items into the list: ";
    for(int i = 0; i < 10; i++) {
        ll->push_front(i);
        cout << ll->front() << " ";
    }
    cout << endl;
    print(*ll);

    // Reverse the list
    cout << endl << "Reverse the list:" << endl;
    ll->reverse();
    print(*ll);

    // Remove some items from the list
    cout << endl << "Remove some items from the list: ";
    for(int i = 0; i < 5; i++) {
        cout << ll->front() << " ";
        ll->pop_front();
    }
    cout << endl;
    print(*ll);

    // Destroy the list
    cout << endl << "Destroy the list:" << endl;
    delete ll;

    // Insert items in sorted order
    cout << endl << "Insert items in sorted order: 2 4 3 1 2" << endl;
    list<int>* sorted = new list<int>;
    sorted_insert(*ll, 2, compare_function);      // empty list
    sorted_insert(*ll, 4, compare_function);      // append to tail
    sorted_insert(*ll, 3, compare_function);      // insert in middle
    sorted_insert(*ll, 1, compare_function);      // insert at head
    try {
        sorted_insert(*ll, 2, compare_function);  // duplicate
    }
    catch(runtime_error& e) {
        cout << e.what() << endl;
    }
    print(*sorted);

    // Destroy the list
    cout << endl << "Destroy the list:" << endl;
    delete sorted;
}
