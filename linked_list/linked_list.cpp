// A singly linked list

#include <iostream>

using namespace std;

// Comparison function for sorting
int compare_function(const int a, const int b) {
    return a - b;   // -ve if a < b, +ve if a > b, 0 if a == b
}

class List {
private:
    struct Node {
        int data;
        Node* next;

        Node(int data) : data(data), next(nullptr) { }
    };

    Node* root = { nullptr };       // the head of the list
    int elements = { 0 };           // keep track of the number of elements

public:
    ~List();                        // destructor - free all elements

    typedef int (*compare_t)(const int a, const int b); // comparison function for sorting

    bool empty() const;             // is the list empty?
    int head() const;               // peek at the element at the head of the list
    void insert(const int data);                    // insert a new element at the head of the list
    void insert(const int data, Node* node);        // insert a new element after an existing element
    void insert(const int data, compare_t compare); // insert a new element in the list in sorted order
    void print() const;             // print a representation of the list
    void remove();                  // remove the element at the head of the list
    void reverse();                 // reverse the list
    int size() const;               // number of elements in the list
    int tail() const;               // peek at the element at the tail of the list
};

// Destructor - free all elements
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

// Peek at the element at the head of the list
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

// Insert a new element after an existing element
void List::insert(const int data, Node* node) {
    if(node == nullptr) {
        throw runtime_error("Bad node");
    }

    Node* after = new Node(data);   // create a new node; see delete in remove()
    after->next = node->next;       // new node inserts before next
    node->next = after;             // new node inserts after this node
    elements++;                     // keep track of the number of elements
}

// Insert a new element in the list in sorted order
void List::insert(const int data, compare_t compare) {
    // If the list is empty, insert at the head
    if(root == nullptr) {
        insert(data);
        return;
    }

    // If the data sorts before the head, insert at the head
    if(compare(data, head()) < 0) {
        insert(data);
        return;
    }

    // Search through the list to find the appropriate insertion point
    for(Node* node = root; node != nullptr; node = node->next) {
        // On the 1st iteration we know that data >= node->data, due to the
        // insert at head logic above

        // Do not insert duplicates
        if(compare(data, node->data) == 0) {
            throw runtime_error("Item already exists in the list");
        }

        // If we've reached the tail, append at the tail
        if(node->next == nullptr) {
            insert(data, node);
            return;
        }

        // If the data sorts before the next node, insert here
        if(compare(data, node->next->data) < 0) {
            insert(data, node);
            return;
        }
    }
#if 0 // Alternate loop form
        Node* curr = root;
        Node* next;
        while(curr != nullptr) {
            next = curr->next;

            // Do not insert duplicates
            if(compare(data, curr->data) == 0) {
                throw runtime_error("Item already exists in the list");
            }
            // If we've reach the tail, append at the tail
            else if(next == nullptr) {
                insert(data, curr);
                return;
            }
            // If the item sorts before next, insert between curr and next
            else if(compare(data, next->data) < 0) {
                insert(data, curr);
                return;
            }
            else {
                // Continue stepping through the list
                curr = next;
            }
        }
#endif

    // Should never reach here
    throw runtime_error("Sorted insertion failed");
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

    // Insert items in sorted order
    cout << endl << "Insert items in sorted order:" << endl;
    List* sorted = new List;
    list->insert(2, compare_function);      // empty list
    list->insert(4, compare_function);      // append to tail
    list->insert(3, compare_function);      // insert in middle
    list->insert(1, compare_function);      // insert at head
    try {
        list->insert(2, compare_function);  // duplicate
    }
    catch(runtime_error& e) {
        cout << e.what() << endl;
    }
    sorted->print();

    // Destroy the list
    cout << endl << "Destroy the list:" << endl;
    delete sorted;
}
