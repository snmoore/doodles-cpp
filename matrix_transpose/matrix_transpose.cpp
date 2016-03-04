// Transpose a matrix with dimensions m x n to dimensions n x m

#include <exception>    // For std::invalid_argument etc
#include <iomanip>      // For std:setw
#include <iostream>     // For std::cout etc

// Transpose a matrix
int* transpose(int* matrix, unsigned int rows, unsigned int cols) {
    if(!matrix || !rows || !cols) {
        throw(std::invalid_argument("transpose: bad arguments"));
    }

    int* transposed = new int[rows*cols];
    for(unsigned int m = 0; m < rows; m++) {
        for(unsigned int n = 0; n < cols; n++) {
            transposed[n*rows +m] = matrix[m*cols + n];
        }
    }
    return transposed;
}

// Print a matrix
void print(int* matrix, unsigned int rows, unsigned int cols) {
    if(!matrix || !rows || !cols) {
        throw(std::invalid_argument("print: bad arguments"));
    }

    for(unsigned int m = 0; m < rows; m++) {
        for(unsigned int n = 0; n < cols; n++) {
            std::cout << std::setw(4) << matrix[m*cols +n];
        }
        std::cout << std::endl;
    }
}

// Test transposing a matrix
void test(int* matrix, unsigned int rows, unsigned int cols) {
    try {
        int* transposed = transpose(matrix, rows, cols);

        std::cout << "Matrix:" << std::endl;
        print(matrix, rows, cols);
        std::cout << std::endl;

        std::cout << "Transposed:" << std::endl;
        print(transposed, cols, rows);
        std::cout << std::endl;

        delete[] transposed;
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

int main() {
    int a[2][4] = {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 }
    };

    int b[4][2] = {
        { 1, 2 },
        { 3, 4 },
        { 5, 6 },
        { 7, 8 }
    };

    int c[3][3] = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    // Test transposing valid matrices
    test(reinterpret_cast<int*>(a), 2, 4);
    test(reinterpret_cast<int*>(b), 4, 2);
    test(reinterpret_cast<int*>(c), 3, 3);

    // Test transposing invalid matrices
    test(nullptr, 2, 4);
    test(reinterpret_cast<int*>(a), 0, 4);
    test(reinterpret_cast<int*>(a), 2, 0);
}
