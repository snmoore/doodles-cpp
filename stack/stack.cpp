// A stack implemented using a linked list

#include <iostream>

using namespace std;

class Stack {
private:
    struct Node {
        int data;
        Node* next;

        Node(int data) : data(data), next(nullptr) {}
    };

    Node* root = { nullptr };       // the top of the stack
    int elements = { 0 };           // keep track of the number of elements

public:
    ~Stack();                       // destructor - free all elements
    bool empty() const;             // is the stack empty?
    void pop();                     // pop an element off the top of the stack
    void push(int data);            // push an element onto the top of the stack
    void print() const;             // print a representation of the stack
    int size() const;               // number of elements in the stack
    int top() const;                // peek at the element at the top of the stack
};

// Destructor - free all elements
Stack::~Stack() {
    Node* next;
    for(Node* node = root; node != nullptr; node = next) {
        next = node->next;
        cout << "Deleting node: " << node->data << endl;
        delete node;
    }
}

// Is the stack empty?
bool Stack::empty() const {
    return elements == 0;
}

// Pop an element off the top of the stack
void Stack::pop() {
    if(root == nullptr) {
        throw runtime_error("Invalid operation: the stack is empty");
    }

    Node* node = root;              // keep track of the popped element
    root = node->next;              // pop - lower node becomes the top
    delete node;                    // free the popped element; see new in push()
    elements--;                     // keep track of the number of elements
}

// Push an element onto the top of the stack
void Stack::push(int data) {
    Node* node = new Node(data);    // create a new node; see delete in pop()
    node->next = root;              // new node points at the old top
    root = node;                    // new node becomes the top
    elements++;                     // keep track of the number of elements
}

// Print a representation of the stack
void Stack::print() const {
    cout << "Empty: " << boolalpha << empty() << endl;
    cout << "Size: " << size() << endl;
    if(size() > 0) {
        cout << "Top: " << top() << endl;
    }
    cout << "Contents: ";
    for(Node* node = root; node != nullptr; node = node->next) {
        cout << node->data << " ";
    }
    cout << endl;
}

// Number of elements in the stack
int Stack::size() const {
    return elements;
}

// Peek at the element at the top of the stack
int Stack::top() const {
    if(root == nullptr) {
        throw runtime_error("Invalid operation: the stack is empty");
    }

    return root->data;
}

int main() {
    // Create a stack
    Stack* stack = new Stack;
    cout << "Create a stack:" << endl;
    stack->print();

    // Push some items onto the stack
    for(int i = 0; i < 10; i++) {
        stack->push(i);
    }
    cout << endl << "Push some items onto the stack:" << endl;
    stack->print();

    // Pop some items off the stack
    for(int i = 0; i < 5; i++) {
        stack->pop();
    }
    cout << endl << "Pop some items off the stack:" << endl;
    stack->print();

    // Destroy the stack
    cout << endl << "Destroy the stack:" << endl;
    delete stack;
}
