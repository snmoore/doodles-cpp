// A stack using the STL
//
// Note that stack does not expose an iterator (e.g. to print each element) -
// better to use a deque or alternative in that case (iterating over a stack
// is not a use case)

#include <iostream>     // For cout etc.
#include <stack>        // For stack

using namespace std;

// Print a representation of the stack
template <typename T>
void print(const stack<T>& st) {
    cout << "Empty: " << boolalpha << st.empty() << endl;
    cout << "Size: " << st.size() << endl;
    if(st.size() > 0) {
        cout << "Top: " << st.top() << endl;
    }
}

int main() {
    // Create a stack of integers (uses deque<int> as its internal container)
    stack<int>* istack = new stack<int>;
    cout << "Create a stack of integers:" << endl;
    print(*istack);

    // Push some integers onto the stack
    cout << endl << "Push some integers onto the stack: ";
    for(int i = 0; i < 10; i++) {
        istack->push(i);
        cout << istack->top() << " ";
    }
    cout << endl;
    print(*istack);

    // Pop some integers off the stack
    cout << endl << "Pop some integers off the stack: ";
    for(int i = 0; i < 5; i++) {
        cout << istack->top() << " ";
        istack->pop();
    }
    cout << endl;
    print(*istack);

    // Destroy the stack of integers
    cout << endl << "Destroy the stack of integers:" << endl;
    delete istack;

    //------------------------

    // Create a stack of chars (uses deque<char> as its internal container)
    stack<char>* cstack = new stack<char>;
    cout << endl << "Create a stack of chars:" << endl;
    print(*cstack);

    // Push some chars onto the stack
    cout << endl << "Push some chars onto the stack: ";
    for(int i = 0; i < 10; i++) {
        cstack->push(('a' + i));
        cout << cstack->top() << " ";
    }
    cout << endl;
    print(*cstack);

    // Pop some chars off the stack
    cout << endl << "Pop some chars off the stack: ";
    for(int i = 0; i < 5; i++) {
        cout << cstack->top() << " ";
        cstack->pop();
    }
    cout << endl;
    print(*cstack);

    // Destroy the stack of chars
    cout << endl << "Destroy the stack of chars:" << endl;
    delete cstack;
}
