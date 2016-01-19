// A singly-linked list using templates

#include <iostream>

using namespace std;

// Comparison function for sorting
template<typename T>
int compare_function(const T a, const T b) {
    return a - b;   // -ve if a < b, +ve if a > b, 0 if a == b
}

// Singly-linked list using templates
template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;

        Node(T data) : data(data), next(nullptr) { }
    };

    Node* root = { nullptr };       // the head of the list
    int elements = { 0 };           // keep track of the number of elements

public:
    ~List();                        // destructor - free all elements
    bool empty() const;             // is the list empty?
    T head() const;                 // peek at the element at the head of the list
    void insert(const T data);      // insert a new element at the head of the list
    void insert(const T data, Node* node);  // insert a new element after an existing element
    void insert(const T data, int (*compare)(const T a, const T b));    // insert a new element in the list in sorted order
    void print() const;             // print a representation of the list
    void remove();                  // remove the element at the head of the list
    void reverse();                 // reverse the list
    int size() const;               // number of elements in the list
    T tail() const;                 // peek at the element at the tail of the list
};

// Destructor - free all elements
template<typename T>
List<T>::~List() {
    Node* next = {nullptr};
    for(Node* node = root; node != nullptr; node = next) {
        next = node->next;
        cout << "Deleting node: " << node->data << endl;
        delete node;
        elements--;
    }
}

// Is the stack empty?
template<typename T>
bool List<T>::empty() const {
    return elements == 0;
}

// Peek at the element at the head of the list
template<typename T>
T List<T>::head() const {
    if(root == nullptr) {
        throw runtime_error("Invalid operation: the list is empty");
    }
    return root->data;
}

// Insert a new element at the head of the list
template<typename T>
void List<T>::insert(const T data) {
    Node* node = new Node(data);    // create a new node; see delete in remove()
    node->next = root;              // new node points at the old head
    root = node;                    // new node becomes the head
    elements++;                     // keep track of the number of elements
}

// Insert a new element after an existing element
template<typename T>
void List<T>::insert(const T data, Node* node) {
    if(node == nullptr) {
        throw runtime_error("Bad node");
    }

    Node* after = new Node(data);   // create a new node; see delete in remove()
    after->next = node->next;       // new node inserts before next
    node->next = after;             // new node inserts after this node
    elements++;                     // keep track of the number of elements
}

// Insert a new element in the list in sorted order
template<typename T>
//void List<T>::insert(const T data, compare_t compare) {
void List<T>::insert(const T data, int (*compare)(const T a, const T b)) {
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
template<typename T>
void List<T>::print() const {
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
template<typename T>
void List<T>::remove() {
    if(root == nullptr) {
        throw runtime_error("Invalid operation: the list is empty");
    }

    Node* node = root;          // head is about to be removed
    root = node->next;          // next element becomes the head
    delete node;                // free the removed element; see new in insert()
    elements--;                 // keep track of the number of elements
}

// Reverse the list
template<typename T>
void List<T>::reverse() {
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
template<typename T>
int List<T>::size() const {
    return elements;
}

// Peek at the element at the tail of the list
template<typename T>
T List<T>::tail() const {
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
    // Create a list of integers
    List<int>* ilist = new List<int>;
    cout << "Create a list of integers:" << endl;
    ilist->print();

    // Insert some integers into the list
    for(int i = 0; i < 10; i++) {
        ilist->insert(i);
    }
    cout << endl << "Insert some integers into the list:" << endl;
    ilist->print();

    // Reverse the list of integers
    cout << endl << "Reverse the list of integers:" << endl;
    ilist->reverse();
    ilist->print();

    // Remove some integers from the list
    for(int i = 0; i < 5; i++) {
        ilist->remove();
    }
    cout << endl << "Remove some integers from the list:" << endl;
    ilist->print();

    // Destroy the list of integers
    cout << endl << "Destroy the list of integers:" << endl;
    delete ilist;

    // Insert integers into a list in sorted order
    cout << endl << "Insert integers into a list in sorted order:" << endl;
    List<int>* isorted = new List<int>;
    isorted->insert(2, compare_function);      // empty list
    isorted->insert(4, compare_function);      // append to tail
    isorted->insert(3, compare_function);      // insert in middle
    isorted->insert(1, compare_function);      // insert at head
    try {
        isorted->insert(2, compare_function);  // duplicate
    }
    catch(runtime_error& e) {
        cout << e.what() << endl;
    }
    isorted->print();

    // Destroy the sorted list of integers
    cout << endl << "Destroy the sorted list of integers:" << endl;
    delete isorted;

    //----------------------

    // Create a list of chars
    List<char>* clist = new List<char>;
    cout << endl << "Create a list of chars:" << endl;
    clist->print();

    // Insert some chars into the list
    for(int i = 0; i < 10; i++) {
        clist->insert('a' + i);
    }
    cout << endl << "Insert some chars into the list:" << endl;
    clist->print();

    // Reverse the list of chars
    cout << endl << "Reverse the list of chars:" << endl;
    clist->reverse();
    clist->print();

    // Remove some chars from the list
    for(int i = 0; i < 5; i++) {
        clist->remove();
    }
    cout << endl << "Remove some chars from the list:" << endl;
    clist->print();

    // Destroy the list of integers
    cout << endl << "Destroy the list of chars:" << endl;
    delete clist;

    // Insert chars into a list in sorted order
    cout << endl << "Insert chars into a list in sorted order:" << endl;
    List<char>* csorted = new List<char>;
    csorted->insert('b', compare_function);     // empty list
    csorted->insert('d', compare_function);     // append to tail
    csorted->insert('c', compare_function);     // insert in middle
    csorted->insert('a', compare_function);     // insert at head
    try {
        csorted->insert('b', compare_function); // duplicate
    }
    catch(runtime_error& e) {
        cout << e.what() << endl;
    }
    csorted->print();

    // Destroy the sorted list of chars
    cout << endl << "Destroy the sorted list of chars:" << endl;
    delete csorted;
}
