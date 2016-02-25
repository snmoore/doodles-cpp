// Trivial threading example, using the STL

#include <chrono>       // For seconds
#include <future>       // For future, promise
#include <iostream>     // For cout
#include <random>       // For random numbers
#include <thread>       // For thread

using namespace std;

#define NUM_THREADS 10

// Need to lock and unlock around cout to avoid corrupt output
mutex mutx {};

// Generate a random sleep period, range 1..2000 milliseconds
long long RandomMilliseconds() {
    // Type of engine
    static default_random_engine generator {};

    // Type of distribution
    static uniform_int_distribution<int> distribution(1,2000);

    // Get and return the random number
    return distribution(generator);

    // Note: need to use static otherwise each invocation will create a new
    // random number generator and get just one result, hence returning the same
    // number each time
}

// The start routine for each thread
void ThreadFunc(int i, promise<int>& result) {
    // Identify this thread
    thread::id tid = this_thread::get_id();

    mutx.lock();
    cout << "thread(" << i << "): thread id = " << tid << endl;
    mutx.unlock();

    // Sleep for a while
    long long period = RandomMilliseconds();
    mutx.lock();
    cout << "thread(" << i << "): sleeping for " << period << "ms"<< endl;
    mutx.unlock();

    this_thread::sleep_for(chrono::milliseconds(period));

    mutx.lock();
    cout << "thread(" << i << "): woke up" << endl;
    mutx.unlock();

    // Return a result
    result.set_value(i);
}

int main() {
    // Create some threads, with promises to allow results to be returned
    promise<int> promises[NUM_THREADS] {};
    thread threads[NUM_THREADS] {};
    for(int i = 0; i < NUM_THREADS; i++) {
        mutx.lock();
        cout << "main():    creating thread " << i << endl;
        mutx.unlock();

        threads[i] = thread(ThreadFunc, i /* arg */, ref(promises[i]) /* result */);
    }

    // Wait for all threads to complete before exiting
    mutx.lock();
    cout << "main():    waiting for all threads to complete" << endl;
    mutx.unlock();
    for(int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    // Gather the results
    for(int i = 0; i < NUM_THREADS; i++) {
        future<int> fut = promises[i].get_future();
        int result = fut.get();
        mutx.lock();
        cout << "main():    thread " << i << " returned " << result << endl;
        mutx.unlock();
    }
}
