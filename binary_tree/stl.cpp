// A binary tree using the STL

#include <iostream>     // For cout etc
#include <set>          // For set

using namespace std;

// Print the contents of a tree
template<typename T>
void print(const set<T>& tree) {
    for(auto elem : tree) {
        cout << elem << " ";
    }
    cout << endl;
//    if(node != nullptr) {
//        print(node->right, level + 1);                      // recursively print the right sub-tree
//        cout << setw(3*level + 2) << node->data << endl;    // print this node
//        print(node->left,  level + 1);                      // recursively print the left sub-tree
//    }
}

// Test with integers
void integers() {
    // Create a new tree of integers
    cout << "Create a new tree of integers" << endl;
    set<int>* itree = new set<int>;

    // Insert some integers into the tree
    cout << endl << "Insert some integers into the tree: 9 4 5 15 6 12 17 2 1 7";
    itree->insert(9);
    itree->insert(4);
    itree->insert(15);
    itree->insert({ 6, 12, 17, 2, 1, 7 });
    cout << endl;
    print(*itree);

    // Attempt to insert a duplicate integer into the tree
    cout << endl << "Attempt to insert a duplicate integer into the tree: 17" << endl;
    auto status = itree->insert(17);
    if(status.second) {
        cout << "Incorrectly inserted duplicate" << endl;
    }
    else {
        cout << "Did not insert duplicate" << endl;
    }
    print(*itree);

    // Search for an existing integer in the tree
    cout << endl << "Search for an existing integer in the tree: " << endl;
    int value = 15;
    auto iter = itree->find(value);
    if(iter != itree->end()) {
        cout << "Found " << *iter << endl;
    }
    else {
        cout << "Failed to find " << value << endl;
    }

    // Search for an non-existent integer in the tree
    cout << endl << "Search for an non-existent integer in the tree: " << endl;
    value = 3;
    iter = itree->find(value);
    if(iter != itree->end()) {
        cout << "Found " << *iter << endl;
    }
    else {
        cout << "Failed to find " << value << endl;
    }

    // Remove some integers
    cout << endl << "Remove some integers: 17 6 2 9" << endl;
    itree->erase(17);
    itree->erase(6);
    itree->erase(2);
    itree->erase(9);
    print(*itree);

    // Destroy the tree of integers
    cout << endl << "Destroy the tree of integers" << endl;
    delete itree;
}

// Test with chars
void chars() {
    // Create a new tree of chars
    cout << endl << "Create a new tree of chars" << endl;
    set<char>* ctree = new set<char>;

    // Insert some chars into the tree
    cout << endl << "Insert some chars into the tree: j e p g m r c b h";
    ctree->insert('j');
    ctree->insert('e');
    ctree->insert('p');
    ctree->insert({ 'g', 'm', 'r', 'c', 'b', 'h' });
    cout << endl;
    print(*ctree);

    // Attempt to insert a duplicate char into the tree
    cout << endl << "Attempt to insert a duplicate char into the tree: r" << endl;
    auto status = ctree->insert('r');
    if(status.second) {
        cout << "Incorrectly inserted duplicate" << endl;
    }
    else {
        cout << "Did not insert duplicate" << endl;
    }
    print(*ctree);

    // Search for an existing char in the tree
    cout << endl << "Search for an existing char in the tree: " << endl;
    char value = 'p';
    auto iter = ctree->find(value);
    if(iter != ctree->end()) {
        cout << "Found " << *iter << endl;
    }
    else {
        cout << "Failed to find " << value << endl;
    }

    // Search for an non-existent char in the tree
    cout << endl << "Search for an non-existent char in the tree: " << endl;
    value = 'd';
    iter = ctree->find(value);
    if(iter != ctree->end()) {
        cout << "Found " << *iter << endl;
    }
    else {
        cout << "Failed to find " << value << endl;
    }

    // Remove some chars
    cout << endl << "Remove some chars: r g c j" << endl;
    ctree->erase('r');
    ctree->erase('g');
    ctree->erase('c');
    ctree->erase('j');
    print(*ctree);

    // Destroy the tree of chars
    cout << endl << "Destroy the tree of chars" << endl;
    delete ctree;
}

int main() {
    // Test with integers
    integers();

    // Test with chars
    chars();
}
