// Binary tree using templates
//
// This typically executes in log_2(N) time for insertion, deletion and sorting
// See https://en.wikipedia.org/wiki/Binary_tree

#include <iomanip>      // For setw
#include <iostream>     // For cout etc

using namespace std;

// Comparison function used to keep the tree ordered
template<typename T>
int compare_function(T a, T b) {
    return a - b;   // -ve if a < b, +ve if a > b, 0 if a == b
}

// Binary tree class using templates
template<typename T>
class Tree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node* root = {nullptr};

    void destroy(Node* node);                                                   // delete all nodes in a tree or sub-tree (recursive)
    bool find(T data, int (*compare)(T a, T b), Node* node);                    // find an item in a tree or sub-tree (recursive)
    void insert(T data, int (*compare)(T a, T b), Node** node);                 // insert a new node into a tree or sub-tree (recursive)
    void print(Node* node, int level) const;                                    // print the contents of a tree or sub-tree (recursive)
    void remove(T data, int (*compare)(T a, T b), Node* node, Node** plink);    // remove an item in the tree (recursive)

public:
    ~Tree();                                        // destructor - delete all nodes in the tree
    bool find(T data, int (*compare)(T a, T b));    // find an item in the tree
    void insert(T data, int (*compare)(T a, T b));  // insert a new node into the tree
    void print() const;                             // print the contents of the tree
    void remove(T data, int (*compare)(T a, T b));  // remove an item in the tree
};

// Destructor - delete all nodes in the tree
template<typename T>
Tree<T>::~Tree() {
    destroy(root);
}

// Delete all nodes in a tree or sub-tree (recursive)
template<typename T>
void Tree<T>::destroy(Node* node) {
    if(node != nullptr) {
        destroy(node->left);        // recursively destroy the left sub-tree
        destroy(node->right);       // recursively destroy the right sub-tree
        cout << "Deleting: " << node->data << endl;
        delete node;                // destroy this node
    }
}

// Find an item in the tree
template<typename T>
bool Tree<T>::find(T data, int (*compare)(T a, T b)) {
    return find(data, compare, root);
}

// Find an item in a tree or sub-tree (recursive)
template<typename T>
bool Tree<T>::find(T data, int (*compare)(T a, T b), Node* node) {
    if(node == nullptr) {
        return false;
    }
    else {
        if(compare(data, node->data) == 0) {
            print(node, 0);
            return true;                            // found it
        }
        else if(compare(data, node->data) < 0) {
            return find(data, compare, node->left); // search into the left sub-tree
        }
        else { // if(compare(data, node->data) < 0)
            return find(data, compare, node->right); // search into the right sub-tree
        }
    }
}

// Insert a new node into the tree
template<typename T>
void Tree<T>::insert(T data, int (*compare)(T a, T b)) {
    if(root == nullptr) {
        root = new Node(data);          // the tree is empty, so insert here
    }
    else {
        insert(data, compare, &root);    // insert into the existing tree
    }
}

// Insert a new node into a tree or sub-tree (recursive)
template<typename T>
void Tree<T>::insert(T data, int (*compare)(T a, T b), Node** node) {
    if(*node == nullptr) {
        *node = new Node(data);  // the sub-tree is empty, so insert here
    }
    else {
        if(compare(data, (*node)->data) == 0) {
            throw runtime_error("Invalid operation: key already exists in the tree");
        }
        else if(compare(data, (*node)->data) < 0) {
            insert(data, compare, &(*node)->left);  // insert into the left sub-tree
        }
        else  { // if(compare(data, (*node)->data) > 0)
            insert(data, compare, &(*node)->right); // insert into the right sub-tree
        }
    }
}

// Print the contents of the tree
template<typename T>
void Tree<T>::print() const {
    print(root, 0);
    cout << endl;
}

// Print the contents of a tree or sub-tree (recursive)
template<typename T>
void Tree<T>::print(Node* node, int level) const {
    if(node != nullptr) {
        print(node->right, level + 1);                      // recursively print the right sub-tree
        cout << setw(3*level + 2) << node->data << endl;    // print this node
        print(node->left,  level + 1);                      // recursively print the left sub-tree
    }
}

// Remove an item in the tree
template<typename T>
void Tree<T>::remove(T data, int (*compare)(T a, T b)) {
    remove(data, compare, root, &root);
}

// Remove an item in the tree (recursive)
//
// plink is the parent's link to the node i.e. parent->left or parent->right
template<typename T>
void Tree<T>::remove(T data, int (*compare)(T a, T b), Node* node, Node** plink) {
    if(node != nullptr) {
        // Find the node
        if(compare(data, node->data) == 0) {
            // Found the node to be removed
            cout << "Removing " << node->data << endl << endl;
            print(node, 0);
            cout << endl;

            if(node->right == nullptr) {
                if(node->left == nullptr) {
                    // Node has no children
                    *plink = nullptr;       // clear the parent's link to the node
                    delete node;            // delete the node
                }
                else {
                    // Node has left sub-tree only
                    *plink = node->left;    // replace the node with its left sub-tree
                    delete node;            // delete the node
                }
            }
            else {
                if(node->left == nullptr) {
                    // Node has right sub-tree only
                    *plink = node->right;   // replace the node with its right sub-tree
                    delete node;            // delete the node
                }
                else {
                    // Node has both left and right sub-tree

                    // Find the successor node, which is the left-most node in the right sub-tree
                    Node** psucc = &node->right;
                    while((*psucc)->left != nullptr) {
                        psucc = &(*psucc)->left;
                    }

                    // Break the link between the successor and its parent
                    Node* succ = *psucc;
                    *psucc = nullptr;

                    // Successor node acquires the removed node's left and right sub-trees
                    succ->left = node->left;
                    succ->right = node->right;

                    // Replace the node with the successor
                    *plink = succ;
                    delete node;
                }
            }
        }
        else if(compare(data, node->data) < 0) {
            // Search into the left sub-tree
            remove(data, compare, node->left, &node->left);
        }
        else { // if(compare(data, node->data) > 0)
            // Search into the right sub-tree
            remove(data, compare, node->right, &node->right);
        }
    }
}

// Test with integers
void integers() {
    // Create a new tree of integers
    cout << "Create a new tree of integers:" << endl;
    Tree<int>* itree = new Tree<int>;
    itree->print();

    // Insert some integers into the tree
    cout << "Insert some integers into the tree: ";
    int values[] = { 9, 4, 15, 6, 12, 17, 2, 1, 7 };
    for(auto v : values) {
        cout << v << " ";
        itree->insert(v, compare_function);
    }
    cout << endl;
    itree->print();

    // Attempt to insert a duplicate integer into the tree
    cout << "Attempt to insert a duplicate integer into the tree:" << endl;
    try {
        itree->insert(17, compare_function);
    }
    catch(runtime_error& e) {
        cout << e.what() << endl;
    }
    itree->print();

    // Search for an existing integer in the tree
    cout << "Search for an existing integer in the tree: " << endl;
    int value = 15;
    bool found = itree->find(value, compare_function);
    if(found) {
        cout << "Found " << value << endl;
    }
    else {
        cout << "Failed to find " << value << endl;
    }

    // Search for an non-existent integer in the tree
    cout << endl << "Search for an non-existent integer in the tree: " << endl;
    value = 3;
    found = itree->find(value, compare_function);
    if(found) {
        cout << "Found " << value << endl;
    }
    else {
        cout << "Failed to find " << value << endl;
    }

    // Remove a node that has no children
    cout << endl << "Remove a node that has no children: " << endl;
    itree->remove(17, compare_function);
    itree->print();

    // Remove a node that has a right sub-tree only
    cout << endl << "Remove a node that has a right sub-tree only: " << endl;
    itree->remove(6, compare_function);
    itree->print();

    // Remove a node that has a left sub-tree only
    cout << endl << "Remove a node that has a left sub-tree only: " << endl;
    itree->remove(2, compare_function);
    itree->print();
	
    // Remove a node that has both a left and a right sub-tree
    cout << endl << "Remove a node that has a left and a right sub-tree: " << endl;
    itree->remove(9, compare_function);
    itree->print();

    // Destroy the tree of integers
    cout << endl << "Destroy the tree of integers:" << endl;
    delete itree;
}

// Test with chars
void chars() {
    // Create a new tree of chars
    cout << endl << "Create a new tree of chars:" << endl;
    Tree<char>* ctree = new Tree<char>;
    ctree->print();

    // Insert some chars into the tree
    cout << "Insert some chars into the tree: ";
    char values[] = { 'j', 'e', 'p', 'g', 'm', 'r', 'c', 'b', 'h' };
    for(auto v : values) {
        cout << v << " ";
        ctree->insert(v, compare_function);
    }
    cout << endl;
    ctree->print();

    // Attempt to insert a duplicate char into the tree
    cout << "Attempt to insert a duplicate char into the tree:" << endl;
    try {
        ctree->insert('r', compare_function);
    }
    catch(runtime_error& e) {
        cout << e.what() << endl;
    }
    ctree->print();

    // Search for an existing char in the tree
    cout << "Search for an existing char in the tree: " << endl;
    char value = 'p';
    bool found = ctree->find(value, compare_function);
    if(found) {
        cout << "Found " << value << endl;
    }
    else {
        cout << "Failed to find " << value << endl;
    }

    // Search for an non-existent char in the tree
    cout << endl << "Search for an non-existent char in the tree: " << endl;
    value = 'd';
    found = ctree->find(value, compare_function);
    if(found) {
        cout << "Found " << value << endl;
    }
    else {
        cout << "Failed to find " << value << endl;
    }

    // Remove a node that has no children
    cout << endl << "Remove a node that has no children: " << endl;
    ctree->remove('r', compare_function);
    ctree->print();

    // Remove a node that has a right sub-tree only
    cout << endl << "Remove a node that has a right sub-tree only: " << endl;
    ctree->remove('g', compare_function);
    ctree->print();

    // Remove a node that has a left sub-tree only
    cout << endl << "Remove a node that has a left sub-tree only: " << endl;
    ctree->remove('c', compare_function);
    ctree->print();

    // Remove a node that has both a left and a right sub-tree
    cout << endl << "Remove a node that has a left and a right sub-tree: " << endl;
    ctree->remove('j', compare_function);
    ctree->print();

    // Destroy the tree of chars
    cout << endl << "Destroy the tree of chars:" << endl;
    delete ctree;
}

int main() {
    // Test with integers
    integers();

    // Test with chars
    chars();
}
