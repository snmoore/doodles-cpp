// A circular buffer (or ring buffer) using an array

#include <algorithm>    // For copy, fill
#include <iomanip>      // For setw
#include <iostream>     // For cout etc

using namespace std;

class Circular {
public:
    Circular(int n);                                        // constructor - create a circular buffer to hold n elements
    ~Circular();                                            // destructor - destroy the circular buffer

    unsigned int available() const;                         // the number of unused elements available in the buffer
    void clear();                                           // clear the buffer
    bool empty() const;                                     // is the buffer empty?
    void print() const;                                     // print a representation of a circular buffer
    char read();                                            // read one at a time from the head of the circular buffer
    void read(char* data, unsigned int nelements);          // read many at a time from the head of the circular buffer
    unsigned int size() const;                              // the number of used elements currently in the buffer
    void write(char c);                                     // write one at a time to the tail of the circular buffer
    void write(const char* data, unsigned int nelements);   // write many at a time to the tail of the circular buffer

private:
    unsigned int head;
    unsigned int tail;
    unsigned int capacity;
    char* buffer;
};

// Constructor - create a circular buffer to hold n elements
Circular::Circular(int n) : head(0), tail(0), capacity(n), buffer(new char[n]) {
    fill(buffer, buffer + capacity, ' ');
}

// Destructor - destroy the circular buffer
Circular::~Circular() {
    delete buffer;
}

// The number of unused elements available in the buffer
unsigned int Circular::available() const {
    return capacity - size();
}

// Clear the buffer
void Circular::clear() {
    fill(buffer, buffer + capacity, ' ');
    head = 0;
    tail = 0;
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
    for(unsigned int i = 0; i < capacity; i++) {
        cout << setw(2) << i << " ";
    }
    cout << endl;
    for(unsigned int i = 0; i < capacity; i++) {
        cout << setw(2) << buffer[i] << " ";
    }
    cout << endl;
    cout << setw(3*head+2) << "H" << endl;
    cout << setw(3*tail+2) << "T" << endl;
}

// The number of used elements currently in the buffer
unsigned int Circular::size() const {
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

// Read many at a time from the head of the circular buffer
void Circular::read(char* data, unsigned int nelements) {
    if((data == nullptr) || (nelements <= 0)) {
        throw runtime_error("Bad arguments");
    }
    if(size() < nelements) {
        throw runtime_error("Invalid operation: not enough data to read");
    }

    // Without wrap-around i.e. [..H..T..]
    if(head < tail) {
        copy(buffer + head, buffer + head + nelements, data);
        fill(buffer + head, buffer + head + nelements, ' ');
    }
    // Without wrap-around i.e. [..T..H..] and enough data to the right
    else if((capacity - head) > nelements) {
        copy(buffer + head, buffer + head + nelements, data);
        fill(buffer + head, buffer + head + nelements, ' ');
    }
    // With wrap-around i.e. [..T..H..]
    else {
        // Right side of the buffer
        unsigned int right = capacity - head;
        copy(buffer + head, buffer + head + right, data);
        fill(buffer + head, buffer + head + right, ' ');

        // Left side of the buffer
        unsigned int left = nelements - right;
        copy(buffer, buffer + left, data + right);
        fill(buffer, buffer + left, ' ');
    }

    // Move the head rightwards and allow it to wrap-around
    head += nelements;
    head %= capacity;
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

// Write many at a time to the tail of the circular buffer
void Circular::write(const char* data, unsigned int nelements) {
    if((data == nullptr) || (nelements == 0)) {
        throw runtime_error("Bad arguments");
    }
    if(available() < nelements) {
        throw runtime_error("Invalid operation: not enough space to write");
    }

    // Without wrap-around i.e. [..T..H..]
    if(head > tail) {
        copy(data, data + nelements, buffer + tail);
    }
    // Without wrap-around i.e. [..H..T..] and the data fits to the right
    else if((capacity - tail) > nelements) {
        copy(data, data + nelements, buffer + tail);
    }
    // With wrap-around i.e. [..H..T..]
    else {
        // Right side of the buffer
        int right = capacity - tail;
        copy(data, data + right, buffer + tail);

        // Left side of the buffer
        int left = nelements - right;
        copy(data + right, data + right + left, buffer);
    }

    // Move the tail rightwards and allow it to wrap-around
    tail += nelements;
    tail %= capacity;
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

    // Clear the circular buffer
    circular->clear();

    // Write many at a time to the tail
    cout << "Write many at a time to the tail: ";
    const char* data = "abcdefghijklmno";
    cout << data << endl;
    circular->write(data, strlen(data));
    circular->print();

    // Read many at a time from the head
    cout << "Read many at a time from the head: ";
    char buffer[11];
    circular->read(buffer, 10);
    buffer[10] = '\0';
    cout << buffer << endl;
    circular->print();

    // Write many at a time to the tail and wrap-around
    cout << "Write many at a time to the tail and wrap-around: ";
    const char* data2 = "pqrstuvxwyz";
    cout << data2 << endl;
    circular->write(data2, strlen(data2));
    circular->print();

    // Read many at a time from the head and wrap-around
    cout << "Read many at a time from the head and wrap-around: ";
    char buffer2[15];
    circular->read(buffer2, 14);
    buffer2[14] = '\0';
    cout << buffer2 << endl;
    circular->print();

    // Clean-up
    delete circular;
}
