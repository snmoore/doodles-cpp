// Multiply two matrices with dimensions m x n and n x p
//
// The resulting matrix should have dimensions m x p

#include <iostream>     // For cout etc
#include <iomanip>      // For setw

using namespace std;

int* multiply(int* a, unsigned int arows, unsigned int acols,
              int* b, unsigned int brows, unsigned int bcols) {
    // The inner dimensions must match in order to be multiplied
    if(acols != brows) {
        throw runtime_error("Inner dimensions mismatch");
    }

    // Allocate space for the resulting matrix
    int* c = (int*)calloc(arows*bcols, sizeof(int));
    if(c == nullptr) {
        throw runtime_error("calloc returned nullptr");
    }

    // Multiply the matrices
    for(unsigned int m = 0; m < arows; m++) {
        for(unsigned int p = 0; p < bcols; p++) {
            for(unsigned int n = 0; n < acols; n++) {
                // [m x p] =  [m x n] * [n x p]
                c[m*bcols + p] += a[m*acols + n] * b[n*bcols + p];
            }
        }
    }
    return c;
}

void print(int* matrix, unsigned int rows, unsigned int cols) {
    if(matrix != nullptr) {
        for(unsigned int m = 0; m < rows; m++) {
            for(unsigned int n = 0; n < cols; n++) {
                cout << setw(4) << matrix[m*cols + n] << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    int a[2][4] = {
        { -1,  2, -4, 8 },
        { -3, -5,  7, 9 }
    };

    int b[4][2] = {
        {  0,  1 },
        { -2,  3 },
        {  4, -5 },
        { -6, -7 }
    };

    int c[3][3] = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    cout << "Matrix a:" << endl;
    print((int*)a, 2, 4);

    cout << endl << "Matrix b:" << endl;
    print((int*)b, 4, 2);

    cout << "Matrix c:" << endl;
    print((int*)c, 3, 3);

    // Multiply a x b
    cout << endl << "Multiply a x b:" << endl;
    int* m = multiply((int*)a, 2, 4, (int*)b, 4, 2);
    print((int*)m, 2, 2);
    free(m);

    // Multiply a x c - should fail due to inner dimension mismatch
    cout << endl << "Multiply a x c:" << endl;
    try {
        m = multiply((int*)a, 2, 4, (int*)c, 3, 3);
    }
    catch(exception& e){
        cout << e.what() << endl;
    }

    // Multiply b x a
    cout << endl << "Multiply b x a:" << endl;
    m = multiply((int*)b, 4, 2, (int*)a, 2, 4);
    print((int*)m, 4, 4);
    free(m);

    // Multiply b x c - should fail due to inner dimension mismatch
    cout << endl << "Multiply b x c:" << endl;
    try {
        m = multiply((int*)b, 4, 2, (int*)c, 3, 3);
    }
    catch(exception& e){
        cout << e.what() << endl;
    }
}
