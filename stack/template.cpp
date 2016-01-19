// A stack implemented using a linked list and templates

#include <iostream>

using namespace std;

template<typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(T data) : data(data), next(nullptr) {}
    };

    Node* root = { nullptr };       // the top of the stack
    int elements = { 0 };           // keep track of the number of elements

public:
    ~Stack();                       // destructor - free all elements
    bool empty() const;             // is the stack empty?
    void pop();                     // pop an element off the top of the stack
    void push(T data);              // push an element onto the top of the stack
    void print() const;             // print a representation of the stack
    int size() const;               // number of elements in the stack
    T top() const;                  // peek at the element at the top of the stack
};

// Destructor - free all elements
template<typename T>
Stack<T>::~Stack() {
    Node* next;
    for(Node* node = root; node != nullptr; node = next) {
        next = node->next;
        cout << "Deleting node: " << node->data << endl;
        delete node;
    }
}

// Is the stack empty?
template<typename T>
bool Stack<T>::empty() const {
    return elements == 0;
}

// Pop an element off the top of the stack
template<typename T>
void Stack<T>::pop() {
    if(root == nullptr) {
        throw runtime_error("Invalid operation: the stack is empty");
    }

    Node* node = root;              // keep track of the popped element
    root = node->next;              // pop - lower node becomes the top
    delete node;                    // free the popped element; see new in push()
    elements--;                     // keep track of the number of elements
}

// Push an element onto the top of the stack
template<typename T>
void Stack<T>::push(T data) {
    Node* node = new Node(data);    // create a new node; see delete in pop()
    node->next = root;              // new node points at the old top
    root = node;                    // new node becomes the top
    elements++;                     // keep track of the number of elements
}

// Print a representation of the stack
template<typename T>
void Stack<T>::print() const {
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
template<typename T>
int Stack<T>::size() const {
    return elements;
}

// Peek at the element at the top of the stack
template<typename T>
T Stack<T>::top() const {
    if(root == nullptr) {
        throw runtime_error("Invalid operation: the stack is empty");
    }

    return root->data;
}

int main() {
    // Create a stack of integers
    Stack<int>* istack = new Stack<int>;
    cout << "Create a stack of integers:" << endl;
    istack->print();

    // Push some integers onto the stack
    for(int i = 0; i < 10; i++) {
        istack->push(i);
    }
    cout << endl << "Push some integers onto the stack:" << endl;
    istack->print();

    // Pop some integers off the stack
    for(int i = 0; i < 5; i++) {
        istack->pop();
    }
    cout << endl << "Pop some integers off the stack:" << endl;
    istack->print();

    // Destroy the stack of integers
    cout << endl << "Destroy the stack of integers:" << endl;
    delete istack;

    //------------------------

    // Create a stack of chars
    Stack<char>* cstack = new Stack<char>;
    cout << endl << "Create a stack of chars:" << endl;
    cstack->print();

    // Push some chars onto the stack
    for(int i = 0; i < 10; i++) {
        cstack->push(('a' + i));
    }
    cout << endl << "Push some chars onto the stack:" << endl;
    cstack->print();

    // Pop some chars off the stack
    for(int i = 0; i < 5; i++) {
        cstack->pop();
    }
    cout << endl << "Pop some chars off the stack:" << endl;
    cstack->print();

    // Destroy the stack of chars
    cout << endl << "Destroy the stack of chars:" << endl;
    delete cstack;
}
