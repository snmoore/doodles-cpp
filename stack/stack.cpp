// A stack implemented using a linked list

#include <exception>    // For std::runtime_error
#include <iostream>     // For std::cout etc
#include <string>       // For std::string

class Stack {
public:
    ~Stack();                                   // destructor (pop all elements)
    Stack() {}                                  // constructor
    Stack(const Stack& rhs);                    // copy constructor (copy all elements)
    Stack& operator=(const Stack& rhs);         // copy assignment operator (clean up the destination then copy all elements)
    Stack(Stack&& rhs);                         // move constructor (steal the elements)
    Stack& operator=(Stack&& rhs);              // move assignment operator (clean up the destination then steal the elements)

    void push(int data);                        // push an item onto the stack
    void pop();                                 // pop an item off the stack
    void reverse();                             // reverse the order of items in the stack

    bool empty() const;                         // is the stack empty?
    size_t size() const;                        // get the number of elements in the stack
    int top() const;                            // get the item at the top of the stack
    void print(const std::string& label) const; // print the contents of the stack

private:
    struct Node {
        int data;
        Node* next;

        Node(int data) : data(data), next(nullptr) {}
    };

    Node* root {nullptr};
    size_t nelements {0};
};

// Destructor (pop all elements)
Stack::~Stack() {
    while(size() > 0) {
        pop();
    }
}

// Copy constructor (copy all elements)
Stack::Stack(const Stack& rhs) {
    std::cout << "Copy constructor was called" << std::endl;

    // Copy each element
    Node* node = rhs.root;
    while(node != nullptr) {
        push(node->data);
        node = node->next;
    }

    // But the simple push above means the copy is inverted, so reverse it
    reverse();
}

// Copy assignment operator (clean up the destination then copy all elements)
Stack& Stack::operator=(const Stack& rhs) {
    std::cout << "Copy assignment operator was called" << std::endl;

    // Clean up the destination stack
    while(size() > 0) {
        pop();
    }

    // Copy each element
    Node* node = rhs.root;
    while(node != nullptr) {
        push(node->data);
        node = node->next;
    }

    // But the simple push above means the copy is inverted, so reverse it
    reverse();

    // Enable chains of assignments (see Effective C++, 2nd ed., item 15)
    return *this;
}

// Move constructor (steal the elements)
Stack::Stack(Stack&& rhs)
    // Steal the elements from rhs
    : root{rhs.root}, nelements(rhs.nelements) {

    std::cout << "Move constructor was called" << std::endl;

    // rhs now has no elements
    rhs.root = nullptr;
    rhs.nelements = 0;
}

// Move assignment operator (clean up the destination then steal the elements)
Stack& Stack::operator=(Stack&& rhs) {
    std::cout << "Move assignment operator was called" << std::endl;

    // Clean up the destination stack
    while(size() > 0) {
        pop();
    }

    // Steal the elements from rhs
    root = rhs.root;
    nelements = rhs.nelements;

    // rhs now has no elements
    rhs.root = nullptr;
    rhs.nelements = 0;

    // Enable chains of assignments (see Effective C++, 2nd ed., item 15)
    return *this;
}

// Push an item onto the stack
void Stack::push(int data) {
    Node* node = new Node(data);    // create a new node; see delete in pop
    node->next = root;              // new node becomes the new top
    root       = node;
    nelements++;                    // keep track of the number of elements
}

// Pop an item off the stack
void Stack::pop() {
    if(root == nullptr) {
        throw(std::runtime_error("pop: stack is empty"));
    }

    Node* node = root;              // keep track of the popped element
    root = node->next;              // next node become the new top
    delete node;                    // destroy the new node; see new in push
    nelements--;                    // keep track of the number of elements
}

// Reverse the order of items in the stack
void Stack::reverse() {
    Node* prev {nullptr};
    Node* curr {root};
    Node* next {nullptr};
    while(curr != nullptr) {
        next = curr->next;  // about to be overwritten
        curr->next = prev;  // reverse the nodes
        prev = curr;        // move on
        curr = next;
    }
    root = prev;            // root points at the new stop of the stack
}

// Is the stack empty?
bool Stack::empty() const {
    return nelements == 0;
}

// Get the number of elements in the stack
size_t Stack::size() const {
    return nelements;
}

// Get the item at the top of the stack
int Stack::top() const {
    if(root == nullptr) {
        throw(std::runtime_error("top: stack is empty"));
    }
    return root->data;
}

// Print the contents of the stack
void Stack::print(const std::string& label) const {
    std::cout << label << ": " << std::endl;
    std::cout << "\tSize:     " << size() << std::endl;
    std::cout << "\tEmpty:    " << std::boolalpha << empty() << std::endl;
    std::cout << "\tElements: ";
    Node* node = root;
    while(node != nullptr) {
        std::cout << node->data << " ";
        node = node->next;
    }
    std::cout << std::endl << std::endl;
}

int main() {
    // Create a new stack
    Stack* original = new Stack();
    original->print("Empty stack");

    // Push some items onto the stack
    for(int i = 0; i < 11; i++) {
        original->push(i);
    }
    original->print("Push some items onto the stack");

    // Get the item at the top of the stack
    std::cout << "Get the item at the top of the stack:" << std::endl;
    std::cout << "\t" << original->top() << std::endl << std::endl;

    // Pop some items from the stack
    for(int i = 0; i < 5; i++) {
        original->pop();
    }
    original->print("Pop some items from the stack");

    // Reverse the stack
    original->reverse();
    original->print("Reverse the stack");

    // Copy the stack
    Stack* copy1 = new Stack(*original);
    copy1->print("Copy the stack");

    // Destroy the source stack
    delete original;
    copy1->print("Copied stack after the source stack was deleted");

    // Copy the stack via assignment
    Stack* copy2 = new Stack;
    *copy2 = *copy1;
    copy2->print("Copy the stack via assignment");

    // Destroy the source stack
    delete copy1;
    copy2->print("Copied stack after the source stack was deleted");

    // Move the stack
    Stack* copy3 = new Stack(std::move(*copy2));
    delete copy2;
    copy2->print("Source stack after move");
    copy3->print("Destination stack after move");

    // Move the stack via assignment
    Stack* copy4 = new Stack;
    *copy4 = std::move(*copy3);
    delete copy3;
    copy3->print("Source stack after move assignment");
    copy4->print("Destination stack after move assignment");

    // Cleanup
    delete copy4;
}
