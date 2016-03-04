// Convert a string to an integer
//
// See http://pubs.opengroup.org/onlinepubs/009695399/functions/atoi.html

#include <cctype>       // For isdigit
#include <cstddef>      // For NULL
#include <cstdlib>      // For atoi
#include <iostream>     // For std::cout etc
#include <strstream>    // For std::istrstream
#include <string>       // For std::string

#define NELEMENTS(array) ((sizeof(array))/(sizeof(array[0])))

// A C implementation of atoi
int atoi_c(const char *str) {
    // Handle invalid input
    if((str == NULL) || (*str == '\0')) {
        return 0;
    }

    // Handle sign digit, if present
    int sign {1};
    if(*str == '+') {
        str++;
    }
    else if(*str == '-') {
        sign = -1;
        str++;
    }

    // Determine the value
    int value {0};
    while(isdigit(*str)) {
        value *= 10;
        value += *str - '0';
        str++;
    }

    return sign * value;
}

// A C++ implementation of atoi
int atoi_cpp(const char *str) {
    // std::istrstream will segfault on a null pointer
    if(str == nullptr) {
        return 0;
    }

    // Extract the value via a string stream
    std::istrstream input(str);
    int value {0};
    input >> value;
    return value;
}

// Test a given atoi implementation
void test(int (*function)(const char *str), std::string name) {
    const char* tests[] = {
            "-1",
            "0",
            "+1",
            "1",
            "12345",
            "2147483647", // INT_MAX
            "123abc",
            "abc",
            "",
            nullptr,
    };

    for(size_t i = 0; i < NELEMENTS(tests); i++) {
        // Brief description of the test
        if(tests[i] != nullptr) {
            std::cout << name << "(\"" << tests[i] << "\"): ";
        }
        else {
            std::cout << name << "(null): ";

            // Standard C library function atoi will segfault on a null pointer
            if(name == "atoi") {
                std::cout << "skipped" << std::endl;
                continue;
            }
        }

        // Test the function
        try {
            std::cout << function(tests[i]);
        }
        catch(std::exception& e) {
            std::cout << e.what();
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    // Test the standard library version of atoi
    test(atoi, "atoi");

    // Test the C implementation of atoi
    test(atoi_c, "atoi_c");

    // Test the C++ implementation of atoi
    test(atoi_cpp, "atoi_cpp");
}
