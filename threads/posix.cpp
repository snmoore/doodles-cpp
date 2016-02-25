// Trivial threading example, using POSIX

#include <cstring>      // For strerror
#include <iostream>     // For cout
#include <mutex>        // For mutex
#include <pthread.h>    // For pthread_create
#include <unistd.h>     // For sleep

using namespace std;

#define NUM_THREADS 10

// Need to lock and unlock around cout to avoid corrupt output
mutex mutx {};

// The start routine for each thread
void* ThreadFunc(void* arg) {
    long int i = reinterpret_cast<long int>(arg);
    pthread_t tid = pthread_self();

    mutx.lock();
    cout << "thread(" << i << "): thread id = " << tid << endl;
    mutx.unlock();

    return arg; // behaves the same as pthread_exit(arg)
}

int main() {
    // Create some threads
    pthread_t threads[NUM_THREADS] {};
    for(int i = 0; i < NUM_THREADS; i++) {
        mutx.lock();
        cout << "main():    creating thread " << i << endl;
        mutx.unlock();

        int result = pthread_create(&threads[i],
                                    NULL, /* default attrs */
                                    ThreadFunc,
                                    reinterpret_cast<void*>(i));
        if(result != 0) {
            cout << "Failed to create thread: " << strerror(errno) << endl;
            exit(result);
        }
    }

    // Wait for all threads to complete before exiting
    mutx.lock();
    cout << "main():    waiting for all threads to complete" << endl;
    mutx.unlock();
    for(int i = 0; i < NUM_THREADS; i++) {
        void* thread_result {};
        int result = pthread_join(threads[i], &thread_result);
        if(result != 0) {
            cout << "Failed to join thread: " << strerror(errno) << endl;
            exit(result);
        }

        long int thread_result_i = reinterpret_cast<long int>(thread_result);
        mutx.lock();
        cout << "main():    thread " << i << " returned " << thread_result_i << endl;
        mutx.unlock();
    }
}
