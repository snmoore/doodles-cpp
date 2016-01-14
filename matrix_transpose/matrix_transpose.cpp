// Transpose a matrix with dimensions m x n to dimensions n x m

#include <cstdlib>      // For calloc
#include <iostream>     // For cout etc

using namespace std;

int* transpose(int* matrix, const unsigned int rows, const unsigned int cols) {
    int* transposed = (int*)calloc(cols*rows, sizeof(int));
    if((transposed != nullptr) && (matrix != nullptr)) {
        for(unsigned int m = 0; m < rows; m++) {
            for(unsigned int n = 0; n < cols; n++) {
                transposed[n*rows + m] = matrix[m*cols + n];
            }
        }
    }
    return transposed;
}

void print(int* matrix, const unsigned int rows, const unsigned int cols) {
    if(matrix != nullptr) {
        for(unsigned int m = 0; m < rows; m++) {
            for(unsigned int n = 0; n < cols; n++) {
                cout << matrix[m*cols + n] << " ";
            }
            cout << endl;
        }
        cout << endl;
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

    // Transpose a to a'
    cout << "Matrix a:" << endl;
    print((int*)a, 2, 4);
    int* m = transpose((int*)a, 2, 4);
    cout << "Matrix a':" << endl;
    print((int*)m, 4, 2);
    free(m);

    // Transpose b to b'
    cout << "Matrix b:" << endl;
    print((int*)b, 4, 2);
    m = transpose((int*)b, 4, 2);
    cout << "Matrix b':" << endl;
    print((int*)m, 2, 4);
    free(m);

    // Transpose c to c'
    cout << "Matrix c:" << endl;
    print((int*)c, 3, 3);
    m = transpose((int*)c, 3, 3);
    cout << "Matrix c':" << endl;
    print((int*)m, 3, 3);
    free(m);
}
