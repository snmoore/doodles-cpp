// A circular buffer (or ring buffer) using an array

#include <iomanip>          // For setw
#include <iostream>         // For cout etc

using namespace std;

class Circular {
public:
    Circular(int n);            // constructor - create a circular buffer to hold n elements
    ~Circular();                // destructor - destroy the circular buffer

    int available() const;      // the number of unused elements available in the buffer
    bool empty() const;         // is the buffer empty?
    void print() const;         // print a representation of a circular buffer
    char read();                // read one at a time from the head of the circular buffer
    int size() const;           // the number of used elements currently in the buffer
    void write(char c);         // write one at a time to the tail of the circular buffer

private:
    int head;
    int tail;
    int capacity;
    char* buffer;
};

// Constructor - create a circular buffer to hold n elements
Circular::Circular(int n) : head(0), tail(0), capacity(n), buffer(new char[n]) {
}

// Destructor - destroy the circular buffer
Circular::~Circular() {
    delete buffer;
}

// The number of unused elements available in the buffer
int Circular::available() const {
    return capacity - size();
}

// Is the buffer empty?
bool Circular::empty() const {
    return head == tail;
}

// Print a representation of a circular buffer
void Circular::print() const {
    cout << "Empty:     " << boolalpha << empty() << endl;
    cout << "Capacity:  " << capacity << endl;
    cout << "Available: " << available() << endl;
    cout << "Size:      " << size() << endl;
    cout << "Head:      " << head << endl;
    cout << "Tail:      " << tail << endl;

    cout << "Contents:" << endl;
    for(int i = 0; i < capacity; i++) {
        cout << setw(2) << i << " ";
    }
    cout << endl;
    for(int i = 0; i < capacity; i++) {
        cout << setw(2) << buffer[i] << " ";
    }
    cout << endl;
    cout << setw(3*head+2) << "H" << endl;
    cout << setw(3*tail+2) << "T" << endl;
}

// The number of used elements currently in the buffer
int Circular::size() const {
    // Without wrap-around i.e [..H...T..]
    if(head < tail) {
        return tail - head;
    }
    // With wrap-around i.e [..T...H..]
    else if(head > tail) {
        return capacity - (head - tail);
    }
    // Empty
    else {
        return 0;
    }
}

// Read one at a time from the head of the circular buffer
char Circular::read() {
    if(empty()) {
        throw runtime_error("Invalid operation: the buffer is empty");
    }

    char value = buffer[head];
    buffer[head] = ' '; // remove from the head
    head++;             // move the head rightwards
    head %= capacity;   // allow the head to wrap-around
    return value;
}

// Write one at a time to the tail of the circular buffer
void Circular::write(char c) {
    if(Circular::available() < 1) {
        throw runtime_error("Invalid operation: the buffer is full");
    }

    buffer[tail] = c;   // append at the tail
    tail++;             // move the tail rightwards
    tail %= capacity;   // allow the tail to wrap-around
}

int main() {
    // Create a circular buffer
    cout << "Create a circular buffer:" << endl;
    Circular* circular = new Circular(20);
    circular->print();

    // Read when the buffer is empty
    cout << "Read when the buffer is empty: " << endl;
    try {
        circular->read();
    }
    catch(exception& e) {
        cout << e.what() << endl;
    }
    circular->print();

    // Write one at a time to the tail
    cout << "Write one at a time to the tail: ";
    int i;
    for(i = 0; i < 10; i++) {
        char c = 'a' + i;
        circular->write(c);
        cout << c << " ";
    }
    cout << endl;
    circular->print();

    // Read one at a time from the head
    cout << "Read one at a time from the head: ";
    for(int j = 0; j < 5; j++) {
        char c = circular->read();
        cout << c << " ";
    }
    cout << endl;
    circular->print();

    // Write one at a time to the tail and wrap-around
    cout << "Write one at a time to the tail and wrap-around: ";
    for( ; i < 24; i++) {
        char c = 'a' + i;
        circular->write(c);
        cout << c << " ";
    }
    cout << endl;
    circular->print();

    // Read one at a time from the head and wrap-around
    cout << "Read one at a time from the head and wrap-around: ";
    for(int j = 0; j < 17; j++) {
        char c = circular->read();
        cout << c << " ";
    }
    cout << endl;
    circular->print();

    // Clean-up
    delete circular;
}
