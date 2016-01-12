#include <iostream>

using namespace std;

#if defined _WIN32
#define PLATFORM "Windows"
#elif defined __linux
#define PLATFORM "Linux"
#elif defined __APPLE__
#define PLATFORM "OS X"
#elif
#define PLATFORM "Unknown"
#endif

int main() {
    cout << PLATFORM << " System" << endl;

    if(PLATFORM == "OS X") {
        cout << "Performing OS X only tasks..." << endl;
    }

    return 0;
}
