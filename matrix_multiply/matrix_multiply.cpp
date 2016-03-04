// Multiply two matrices with dimensions m x n and n x p
//
// The resulting matrix should have dimensions m x p

// !!! Investigate weird results when using new:
//
// Case 1: use calloc
//  int* multiplied = static_cast<int*>(calloc(arows * bcols, sizeof(int)));
//  free(multiplied);
//  - this works correctly
//
// Case 2: use new with initialization
//  int* multiplied = new int[arows * bcols];
//  delete[] multiplied;
//  - this works correctly
//
// Case 3: use new without initialization
//  int* multiplied = new int[arows * bcols];
//  delete[] multiplied;
//  - this works for a*b and b*a, but c*c gives bogus results in the last column
//  - and results differ if I reorder the code
//  - and it works correctly if I omit the delete

#include <exception>    // For std::invalid_argument and std::logic_error
#include <iomanip>      // For std::setw
#include <iostream>     // For std::cout etc

// Multiply two matrices
int* multiply(int* a, unsigned int arows, unsigned int acols,
              int* b, unsigned int brows, unsigned int bcols) {
    if(!a || !arows || !acols || !b || !brows || !bcols ) {
        throw(std::invalid_argument("multiply: bad arguments"));
    }

    // Inner dimensions must match
    if(acols != brows) {
        throw(std::invalid_argument("multiply: inner dimensions mismatch"));
    }

    // Multiply the two matrices
    int* multiplied = new int[arows * bcols]();
    for(unsigned int m = 0; m < arows; m++) {
        for(unsigned int p = 0; p < bcols; p++) {
            for(unsigned int n = 0; n < acols; n++) {
                multiplied[m*bcols + p] += a[m*acols + n] * b[n*bcols + p];
            }
        }
    }

    return multiplied;
}

// Print a matrix
void print(int* matrix, unsigned int rows, unsigned int cols) {
    if(!matrix || !rows || !cols) {
        throw(std::invalid_argument("print: bad arguments"));
    }

    for(unsigned int m = 0; m < rows; m++) {
        for(unsigned int n = 0; n < cols; n++) {
            std::cout << std::setw(4) << matrix[m*cols + n];
        }
        std::cout << std::endl;
    }
}

// Test multiplying two matrices
void test(int* a,  unsigned int arows,  unsigned int acols,
          int* b,  unsigned int brows,  unsigned int bcols,
          int* ab, unsigned int abrows, unsigned int abcols) {
    try {
        // Multiply the two matrices
        int* multiplied = multiply(a, arows, acols, b, brows, bcols);

        // Verify the result was correct
        for(unsigned int m = 0; m < abrows; m++) {
            for(unsigned int n = 0; n < abcols; n++) {
                if(multiplied[m*abcols + n] != ab[m*abcols + n]) {
                    throw(std::logic_error("incorrect multiplication"));
                }
            }
        }

        std::cout << "Matrix 1:" << std::endl;
        print(a, arows, acols);
        std::cout << std::endl;

        std::cout << "Matrix 2:" << std::endl;
        print(b, brows, bcols);
        std::cout << std::endl;

        std::cout << "Matrix 1 * Matrix 2:" << std::endl;
        print(multiplied, arows, bcols);
        std::cout << std::endl;

        delete[] multiplied;
    }
    catch(std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

int main() {
    // Matrices
    int a[2][3] = {
        { 1, 2, 3 },
        { 4, 5, 6 }
    };

    int b[3][2] = {
        { 1, 2 },
        { 3, 4 },
        { 5, 6 }
    };

    int c[2][2] = {
        { 1, 2 },
        { 3, 4 }
    };

    // Result of multiplying the above matrices
    int ab[2][2] = {
        { 22,  28 },
        { 49,  64 }
    };

    int ba[3][3] = {
        {  9, 12, 15 },
        { 19, 26, 33 },
        { 29, 40, 51 }
    };

    int cc[2][2] = {
        {  7, 10 },
        { 15, 22 }
    };

    // Test valid multiplication
    test(reinterpret_cast<int*>(a),  2, 3,  // a*b
         reinterpret_cast<int*>(b),  3, 2,
         reinterpret_cast<int*>(ab), 2, 2);

    test(reinterpret_cast<int*>(b),  3, 2,  // b*a
         reinterpret_cast<int*>(a),  2, 3,
         reinterpret_cast<int*>(ba), 3, 3);

    test(reinterpret_cast<int*>(c),  2, 2,  // c*c
         reinterpret_cast<int*>(c),  2, 2,
         reinterpret_cast<int*>(cc), 2, 2);

    // Test invalid matrix multiplication
    test(reinterpret_cast<int*>(a),  2, 3, // a*c - inner dimensions mismatch
         reinterpret_cast<int*>(c),  2, 2,
         reinterpret_cast<int*>(ab), 2, 2);

    // Test with bad arguments
    test(nullptr,                    2, 3, // bad matrix
         reinterpret_cast<int*>(b),  3, 2,
         reinterpret_cast<int*>(ab), 2, 2);

    test(reinterpret_cast<int*>(a),  2, 3,
         nullptr,                    3, 2, // bad matrix
         reinterpret_cast<int*>(ab), 2, 2);

    test(reinterpret_cast<int*>(a),  0, 3, // bad number of rows
         reinterpret_cast<int*>(b),  3, 2,
         reinterpret_cast<int*>(ab), 2, 2);

    test(reinterpret_cast<int*>(a),  2, 0, // bad number of columns
         reinterpret_cast<int*>(b),  3, 2,
         reinterpret_cast<int*>(ab), 2, 2);

    test(reinterpret_cast<int*>(a),  2, 3,
         reinterpret_cast<int*>(b),  0, 2, // bad number of rows
         reinterpret_cast<int*>(ab), 2, 2);

    test(reinterpret_cast<int*>(a),  2, 3,
         reinterpret_cast<int*>(b),  3, 0, // bad number of columns
         reinterpret_cast<int*>(ab), 2, 2);
}
