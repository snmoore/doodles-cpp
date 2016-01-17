// Binary tree
//
// This typically executes in log_2(N) time for insertion, deletion and sorting
// See https://en.wikipedia.org/wiki/Binary_tree

#include <iomanip>      // For setw
#include <iostream>     // For cout etc

using namespace std;

// Comparison function used to keep the tree ordered
typedef int (*compare_t)(int a, int b);
int compare_function(int a, int b) {
    return a - b;   // -ve if a < b, +ve if a > b, 0 if a == b
}

class Tree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node* root = {nullptr};

    void destroy(Node* node);                               // delete all nodes in a tree or sub-tree (recursive)
    bool find(int data, compare_t compare, Node* node);     // find an item in a tree or sub-tree (recursive)
    void insert(int data, compare_t compare, Node** node);  // insert a new node into a tree or sub-tree (recursive)
    void print(Node* node, int level) const;                // print the contents of a tree or sub-tree (recursive)
    void remove(int data, compare_t compare, Node* node, Node** plink);  // remove an item in the tree (recursive)

public:
    ~Tree();                                                // destructor - delete all nodes in the tree
    bool find(int data, compare_t compare);                 // find an item in the tree
    void insert(int data, compare_t compare);               // insert a new node into the tree
    void print() const;                                     // print the contents of the tree
    void remove(int data, compare_t compare);               // remove an item in the tree
};

// Destructor - delete all nodes in the tree
Tree::~Tree() {
    destroy(root);
}

// Delete all nodes in a tree or sub-tree (recursive)
void Tree::destroy(Node* node) {
    if(node != nullptr) {
        destroy(node->left);        // recursively destroy the left sub-tree
        destroy(node->right);       // recursively destroy the right sub-tree
        cout << "Deleting: " << node->data << endl;
        delete node;                // destroy this node
    }
}

// Find an item in the tree
bool Tree::find(int data, compare_t compare) {
    return find(data, compare, root);
}

// Find an item in a tree or sub-tree (recursive)
bool Tree::find(int data, compare_t compare, Node* node) {
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
void Tree::insert(int data, compare_t compare) {
    if(root == nullptr) {
        root = new Node(data);          // the tree is empty, so insert here
    }
    else {
        insert(data, compare, &root);    // insert into the existing tree
    }
}

// Insert a new node into a tree or sub-tree (recursive)
void Tree::insert(int data, compare_t compare, Node** node) {
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
void Tree::print() const {
    print(root, 0);
    cout << endl;
}

// Print the contents of a tree or sub-tree (recursive)
void Tree::print(Node* node, int level = 0) const {
    if(node != nullptr) {
        print(node->right, level + 1);                      // recursively print the right sub-tree
        cout << setw(3*level + 2) << node->data << endl;    // print this node
        print(node->left,  level + 1);                      // recursively print the left sub-tree
    }
}

// Remove an item in the tree
void Tree::remove(int data, compare_t compare) {
    remove(data, compare, root, nullptr);
}

// Remove an item in the tree (recursive)
//
// plink is the parent's link to the node i.e. parent->left or parent->right
void Tree::remove(int data, compare_t compare, Node* node, Node** plink) {
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
                    // TODO
                    // Successor is the left-most node in the right sub-tree
                    // Successor acquires the left and right sub-tree
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

int main() {
    // Create a new tree
    cout << "Create a new tree:" << endl;
    Tree* tree = new Tree;
    tree->print();

    // Insert some data
    cout << "Insert some data: ";
    int values[] = { 9, 4, 15, 6, 12, 17, 2, 1, 7 };
    for(auto v : values) {
        cout << v << " ";
        tree->insert(v, compare_function);
    }
    cout << endl;
    tree->print();

    // Attempt to insert a duplicate
    cout << "Attempt to insert a duplicate:";
    try {
        tree->insert(17, compare_function);
    }
    catch(runtime_error& e) {
        cout << e.what() << endl;
    }
    tree->print();

    // Search for an existing item
    cout << "Search for an existing item: " << endl;
    int value = 15;
    bool found = tree->find(value, compare_function);
    if(found) {
        cout << "Found " << value << endl;
    }
    else {
        cout << "Failed to find " << value << endl;
    }

    // Search for an non-existent item
    cout << endl << "Search for an non-existent item: " << endl;
    value = 3;
    found = tree->find(value, compare_function);
    if(found) {
        cout << "Found " << value << endl;
    }
    else {
        cout << "Failed to find " << value << endl;
    }

    // Remove a node that has no children
    cout << endl << "Remove a node that has no children: " << endl;
    tree->remove(17, compare_function);
    tree->print();

    // Remove a node that has a right sub-tree only
    cout << endl << "Remove a node that has a right sub-tree only: " << endl;
    tree->remove(6, compare_function);
    tree->print();

    // Remove a node that has a left sub-tree only
    cout << endl << "Remove a node that has a left sub-tree only: " << endl;
    tree->remove(2, compare_function);
    tree->print();

    // Clean-up
    cout << endl << "Delete all nodes in the tree:" << endl;
    delete tree;
}
