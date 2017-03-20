#include <iostream>
#include <vector>
using namespace std;

#define N 4

/* =========================Helper declarations and functions ====================================*/
void printArray(int vec[]) {
    cout << "\t";
    for (int i = 0; i < N; i++) {
        cout << vec[i] << ", ";
    }
    cout << endl;
}

void printVector(vector<int>& vec) {
    cout << "\t";
    for (auto& e: vec) {
        cout << e << ", ";
    }
    cout << endl;
}

void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        cout << "\t";
        for (int j = 0; j < N; j++) {
            cout << mat[i][j] << ", ";
        }
        cout << endl;
    }
}

// Arrays in C are special: they are always passed as a pointer to the first element of the array

/* ==============================Rotate Image by 90 Degrees=======================================*/
// From 'Cracking the Coding Interview'

void rotate90Degrees (int matrix[N][N]) {
    for (int layer = 0; layer < N/2; layer++) {
        int first = layer;
        int last  = N - layer - 1;
        for (int i = first; i < last; i++)
        {
            int offset =  i - first;
            int top    = matrix[first][i];  // Save top

            matrix[first][i]           = matrix[last-offset][first]; // left->top
            matrix[last-offset][first] = matrix[last][last-offset];  // bottom->left
            matrix[last][last-offset]  = matrix[i][last];            // right->bottom
            matrix[i][last]            = top;                        // top (tmp) -> right
        }

    }
    // O(N^2) time
}

/* ========================Zero Columns and Rows for Positions with 0s============================*/
// From 'Cracking the Coding Interview'

void zeroColsRows (int matrix[N][N]) {
    bool* row = new bool[N](); //initialize to false
    bool* col = new bool[N](); //initialize to false

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix[i][j] == 0) row[i] = col[j] = true;

    //Nullify rows
    for (int i = 0; i < N; i++)
        if (row[i])
            for (int j = 0; j < N; j++)
                matrix[i][j] = 0;

    //Nullify cols
    for (int i = 0; i < N; i++)
        if (col[i])
            for (int j = 0; j < N; j++)
                matrix[j][i] = 0;
}

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void rotate90Degrees_example() {
    int matrix[N][N] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    rotate90Degrees(matrix);
    cout << "Rotated matrix is: " << endl;
    printMatrix(matrix);
}
void zeroColsRows_example() {
    int matrix[N][N] = {{1,2,0,4},{5,6,7,8},{9,10,11,12},{0,14,15,16}};
    zeroColsRows(matrix);
    cout << "Zeroed cols-rows is: " << endl;
    printMatrix(matrix);
}

/* ===============================================================================================*/
int main () {
    rotate90Degrees_example();
    zeroColsRows_example();
}

/* =======================================TODO====================================================*/