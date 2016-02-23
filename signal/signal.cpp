// Trivial signal handling

#include <csignal>
#include <iostream>     // For cout etc
#include <unistd.h>     // For sleep

using namespace std;

// Signal handler for SIGINT (external interrupt, usually initiated by the user)
// This terminates the application
void HandleSIGINT(int signum) {
    if(signum == SIGINT) {
        cout << endl << "Received SIGINT (" << signum << "), terminating!" << endl;

        // Any necessary cleanup goes here

        // Terminate
        exit(1);
    }
    else {
        cout << "Unexpected signal " << signum << endl;
    }
}

// Signal handler for SIGUSR1 (user-defined signal 1)
// This just sleeps for 1 second
void HandleSIGUSR1(int signum) {
    if(signum == SIGUSR1) {
        cout << "Received SIGUSR1 (" << signum << ")" << endl;

        cout << "Sleeping for 1 second..." << endl;
        sleep(1);
    }
    else {
        cout << "Unexpected signal " << signum << endl;
    }
}

int main() {
    // Install the signal handlers
    signal(SIGINT,  HandleSIGINT);
    signal(SIGUSR1, HandleSIGUSR1);

    // Loop forever, sleeping on SIGUSR1, terminating on SIGINT
    for(;;) {
        raise(SIGUSR1);
    }
}
