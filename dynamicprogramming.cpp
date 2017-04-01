#include <iostream>
#include <vector>
#include <map>
using namespace std;

/* =========================Helper declarations and functions ====================================*/
// IMPORTANT:
// Not all backtracking algorithms can be transformed into DP solutions.
// Think about if a state in the search space can be reached by multiple other states, if the search
// space can be encoded efficiently (also in space), and if you can find a solution for a given
// state based on the solutions of smaller states that have been already visited (you must identify
// which smallers states to access and how their solutions can be combined to generate a solution
// for the bigger state).
// In addition to finding optimal solutions to some problem, dynamic programming can also be used
// for counting the number of solutions
// https://en.wikipedia.org/wiki/Dynamic_programming

/* ==============================Number of ways to Cover a Distance===============================*/
// http://www.geeksforgeeks.org/count-number-of-ways-to-cover-a-distance/
int numWays (int dist) {
    // Backtracking: O(3^N)
    if (dist == 0) return 0;
    if (dist == 1) return 1;
    if (dist == 2) return 2;
    if (dist == 3) return 4;
    return numWays(dist - 1) + numWays(dist - 2) + numWays(dist-3);
}

int numWays_dyn (int dist) {
    // Dynamic programming: O(N) time, O(N) space
    int ways[dist + 1];
    ways[0] = 0; ways[1] = 1; ways[2] = 2; ways[3] = 4;
    for (int i = 4; i <= dist; i++) {
        ways[i] = ways[i-1] + ways[i-2] + ways[i-3];
    }
    return ways[dist];
}

/* =====================================Catalan Number============================================*/
// http://www.geeksforgeeks.org/program-nth-catalan-number/
// http://www.geeksforgeeks.org/applications-of-catalan-numbers/
// C(0) = 1;  C(n) = SUM(0 <= i <= n-1], C(n-i-1)*C(i))
// Number of expressions containing n pairs of parentheses which are correctly matched
// Number of possible Binary Search Trees with n keys
// ...
int catalan (int n) {
    // Backtracking: O(n^n) time
    if (n == 0) return 1;
    int res = 0;
    for (int i = 0; i <= n-1; i++) {
        res += catalan(n-i-1)*catalan(i);
    }
    return res;
}

int catalan_dyn (int n) {
    // Dynamic programming: O(N^2) time, O(N) space
    int catalan[n+1];
    catalan[0] = 1;
    for (int i = 1; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j <= i-1; j++) {
            catalan[i] += (catalan[i-j-1] * catalan[j]);
        }
    }
    return catalan[n];
}

/* =====================Number of Paths from Top-Left to Bottom-Right in nxm Matrix===============*/
// http://www.geeksforgeeks.org/count-possible-paths-top-left-bottom-right-nxm-matrix/
// From position (n,m) to (1,1) , which is equivalent from position (n-1,m-1) to (0,0) which is
// equivalent from position (0,0) to position(n-1,m-1)
int numPathsMatrix (int n, int m) {
    // Backtracking: O((n+m)!/(n!*m!)) solutions and time ¿?
    if ((m == 0) || (n==0)) return 1;
        return numPathsMatrix(n-1, m) + numPathsMatrix(n,m-1);
}

int numPathsMatrix_dyn (int n, int m) {
    // Dynamic programming: O(N*M) time, O(N*M) space
    int numPaths[n+1][m+1];
    for (int i = 0; i < n+1; i++) {
        for (int j = 0; j< m+1; j++) {
            if (!i || !j) numPaths[i][j] = 1;
            else {
                numPaths[i][j] = numPaths[i-1][j] + numPaths[i][j-1];
            }
        }
    }
    return numPaths[n][m];
}

/* ============================Efficient Fibonacci Numbers========================================*/
// http://www.geeksforgeeks.org/program-for-nth-fibonacci-number/

int fib (int n) {
    // Backtracking: T(N) = T(N-1) + T(N-2)--> O(2^N) time
    if (n <= 1) return n;
    else return fib(n-1)+fib(n-2);
}

int fib_dyn (int n) {
    // Dynamic programming: O(N) time, O(N) space
    int fib[n+1];
    for (int i = 0; i <= n; i++) {
        if (i <= 1) fib[i] = i;
        else        fib[i] = fib[i-1] + fib[i-2];
    }
    return fib[n];
}
int fib_dyn2 (int n) {
    // Dynamic programming: O(N) time, O(1) space
    if (n <= 1) return n;

    int f_1, f_2;
    f_2 = 0;
    f_1 = 1;
    for (int i = 2; i < n; i++) {
        int tmp = f_2;
        f_2 = f_1;
        f_1 = f_1 + tmp;
    }
    return f_1 + f_2;
}

// Dynamic programming with MEMORIZATION (top-down approach) plus divide and conquer scheme
//   IDEA:
//     If n is even then k = n/2:       F(n) = [2*F(k-1) + F(k)]*F(k)
//     If n is odd then k = (n + 1)/2 : F(n) = F(k)*F(k) + F(k-1)*F(k-1)
map<int,int> fib_memory;

int fib_mem_divideconquer (int n) {
    // Dynamic programming and divide an conquer: O(log N) time, O(N) space
    // T(N) = T(n/2) + 1 --> O(log N)  (T(N) = 2T(N/2) + 1 would be O(N))
    if (n <= 1) return n; // Base Case

    // Check if we have computed the result before and return it
    if (fib_memory.find(n) != fib_memory.end()) return fib_memory[n];

    int k, res;
    if (n%2 == 0) {
        k   = n/2;
        res = (2*fib_mem_divideconquer(k-1) + fib_mem_divideconquer(k)) * fib_mem_divideconquer(k);
    } else {
        k   = (n+1)/2;
        res = ( fib_mem_divideconquer(k)   * fib_mem_divideconquer(k) ) +
              ( fib_mem_divideconquer(k-1) * fib_mem_divideconquer(k-1) );
    }

    // Store the result in the memory
    fib_memory[n] = res;
    return res;
}

/* ========================Count number of binary strings without consecutive 1===================*/
// http://www.geeksforgeeks.org/count-number-binary-strings-without-consecutive-1s/
int countBinaryStrings (int n, int prev) {
    // Backtracking: O(2^N) time
    if (n == 0) return 0;
    if (n == 1 && prev != 1) return 2;
    if (n == 1 && prev == 1) return 1;

    if (prev == -1 || prev == 0) return countBinaryStrings(n-1, 0) + countBinaryStrings(n-1, 1);
    else if (prev == 1)          return countBinaryStrings(n-1, 0) ;
}
int countBinaryStrings_dyn (int n) {
    // Dynamic Programming: O(N) space, O(N) time
    int endZ[n+1];
    int endO[n+1];
    endZ[0] = 0; endO[0] = 0;
    endZ[1] = 1; endO[1] = 1;
    for (int i = 2; i <= n; i++) {
        endZ[i] = endZ[i-1] + endO[i-1];
        endO[i] = endZ[i-1];
    }
    return endZ[n] + endO[n];
}

/* =====================Maximum Size Square Sub-Matrix With all 1s================================*/
// http://www.geeksforgeeks.org/maximum-size-sub-matrix-with-all-1s-in-a-binary-matrix/
#define R 6
#define C 5
void maxSubMatrixOnes_dyn (int mat[R][C], int& r, int& c, int& s) { // r row, c col, s size
    // Dynamic Programming: O(R*C) time, O(R*C) space
    int maxSubMatrix[R+1][C+1];

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++)
        {
            if (!i || !j)
                maxSubMatrix[i][j] = mat[i][j];
            else {
                if (!mat[i][j])
                    maxSubMatrix[i][j] = 0;
                else
                    maxSubMatrix[i][j] = min(maxSubMatrix[i][j-1],
                                             min(maxSubMatrix[i-1][j], maxSubMatrix[i-1][j-1])) + 1;
            }

            if (maxSubMatrix[i][j] > s) { s = maxSubMatrix[i][j]; c = j; r = i;}
        }
    }
}

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void numWays_example() {
    int n = 10;
    cout << "Number of ways to cover distance 10 is: " << numWays(n) << endl;
    cout << "Number of ways to cover distance 10 is: " << numWays_dyn(n) << endl;
}
void catalan_example() {
    int n = 6;
    cout << "Catalan number for n=6 is: " << catalan(6)     << endl;
    cout << "Catalan number for n=6 is: " << catalan_dyn(6) << endl;
}
void numPathsMatrix_example() {
    cout << "Number of paths in a 9x10 matrix is: " << numPathsMatrix(9,10) << endl;;
    cout << "Number of paths in a 9x10 matrix is: " << numPathsMatrix_dyn(9,10) << endl;
}
void fib_example() {
    cout << "Fibonacci number for n=9 is: " << fib(9) << endl;
    cout << "Fibonacci number for n=9 is: " << fib_dyn(9) << endl;
    cout << "Fibonacci number for n=9 is: " << fib_dyn2(9) << endl;
    cout << "Fibonacci number for n=9 is: " << fib_mem_divideconquer(9) << endl;
}
void countBinaryStrings_example() {
    cout << "Binary Strings without Consecutive 1s for n=4 : " << countBinaryStrings_dyn(4) << endl;
    cout << "Binary Strings without Consecutive 1s for n=4 : " << countBinaryStrings(4,-1) << endl;
}
void maxSubMatrixOnes_example() {
    int M[R][C] =  {{0, 1, 1, 0, 1},
                    {1, 1, 0, 1, 0},
                    {0, 1, 1, 1, 0},
                    {1, 1, 1, 1, 0},
                    {1, 1, 1, 1, 1},
                    {0, 0, 0, 0, 0}};
    int max_size = 0;
    int r  = 0;
    int c  = 0;
    maxSubMatrixOnes_dyn(M, r, c, max_size);
    cout << "Maximum Square SubMatrix with all Ones has size: " << max_size << " ends at coords (";
    cout << r << "," << c << ") and is: " << endl;
    for (int i = 1; i <= max_size; i++) {
        cout << "\t";
        for (int j = 1; j <= max_size; j++) {
            cout << M[r-max_size+i][c-max_size+j] << ", ";
        }
        cout << endl;
    }

}
/* ===============================================================================================*/
int main() {
    numWays_example();
    catalan_example();
    numPathsMatrix_example();
    fib_example();
    countBinaryStrings_example();
    maxSubMatrixOnes_example();
}

/* =======================================TODO====================================================*/
// DYNAMIC PROGRAMMING: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#DynamicProgramming
// GREEDY: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#GreedyAlgorithms
// DIVIDE AND CONQUER NOT STUDIED YET
// https://math.dartmouth.edu/archive/m19w03/public_html/Section5-2.pdf
// https://www.nayuki.io/page/master-theorem-solver-javascript
// QUIZS: http://geeksquiz.com/algorithms/