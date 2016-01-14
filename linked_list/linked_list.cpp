// A singly linked list

#include <iostream>

using namespace std;

class List {
public:
    ~List();                        // destructor - free all elements
    bool empty() const;             // is the list empty?
    int head() const;               // peek at the element at the head of the list
    void insert(const int data);    // insert a new element at the head of the list
    void print() const;             // print a representation of the list
    void remove();                  // remove the element at the head of the list
    void reverse();                 // reverse the list
    int size() const;               // number of elements in the list
    int tail() const;               // peek at the element at the tail of the list

private:
    struct Node {
        int data;
        Node* next;

        Node(int data) : data(data), next(nullptr) { }
    };

    Node* root = { nullptr };       // the head of the list
    int elements = { 0 };           // keep track of the number of elements
};

// destructor - free all elements
List::~List() {
    Node* next = {nullptr};
    for(Node* node = root; node != nullptr; node = next) {
        next = node->next;
        cout << "Deleting node: " << node->data << endl;
        delete node;
        elements--;
    }
}

// Is the stack empty?
bool List::empty() const {
    return elements == 0;
}

// peek at the element at the head of the list
int List::head() const {
    if(root == nullptr) {
        throw runtime_error("Invalid operation: the list is empty");
    }
    return root->data;
}

// Insert a new element at the head of the list
void List::insert(const int data) {
    Node* node = new Node(data);    // create a new node; see delete in remove()
    node->next = root;              // new node points at the old head
    root = node;                    // new node becomes the head
    elements++;                     // keep track of the number of elements
}

// Print a representation of the list
void List::print() const {
    cout << "Empty: " << boolalpha << empty() << endl;
    cout << "Size: " << size() << endl;
    if(size() > 0) {
        cout << "Head: " << head() << endl;
        cout << "Tail: " << tail() << endl;
    }
    cout << "Contents: ";
    for(Node* node = root; node != nullptr; node = node->next) {
        cout << node->data << " ";
    }
    cout << endl;
}

// Remove the element at the head of the list
void List::remove() {
    if(root == nullptr) {
        throw runtime_error("Invalid operation: the list is empty");
    }

    Node* node = root;          // head is about to be removed
    root = node->next;          // next element becomes the head
    delete node;                // free the removed element; see new in insert()
    elements--;                 // keep track of the number of elements
}

// Reverse the list
void List::reverse() {
    if(root == nullptr) {
        throw runtime_error("Invalid operation: the list is empty");
    }

    // 1: prev = null, curr = root, next = curr->next
    // 2: curr points back to prev
    // 3: prev = curr, curr = next
    // 4  root = prev
    Node* prev = nullptr;
    Node* curr = root;
    Node* next = {};
    while(curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    root = prev;
}

// Number of elements in the list
int List::size() const {
    return elements;
}

// Peek at the element at the tail of the list
int List::tail() const {
    if(root == nullptr) {
        throw runtime_error("Invalid operation: the list is empty");
    }

    Node* node = root;
    while(node->next != nullptr) {
        node = node->next;
    }
    return node->data;
}

int main() {
    // Create a list
    List* list = new List;
    cout << "Create a list:" << endl;
    list->print();

    // Insert some items into the list
    for(int i = 0; i < 10; i++) {
        list->insert(i);
    }
    cout << endl << "Insert some items into the list:" << endl;
    list->print();

    // Reverse the list
    cout << endl << "Reverse the list:" << endl;
    list->reverse();
    list->print();

    // Remove some items from the list
    for(int i = 0; i < 5; i++) {
        list->remove();
    }
    cout << endl << "Remove some items from the list:" << endl;
    list->print();

    // Destroy the list
    cout << endl << "Destroy the list:" << endl;
    delete list;
}
