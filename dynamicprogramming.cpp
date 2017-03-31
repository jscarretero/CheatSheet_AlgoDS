#include <iostream>
#include <vector>
using namespace std;

/* =========================Helper declarations and functions ====================================*/
// IMPORTANT:
// Not all backtracking algorithms can be transformed into DP problem.
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
    cout << numPathsMatrix(14,15) << endl;;
    cout << numPathsMatrix_dyn(14,15) << endl;
}

/* ===============================================================================================*/
int main() {
    numWays_example();
    catalan_example();
    numPathsMatrix_example();
}

/* =======================================TODO====================================================*/
// DYNAMIC PROGRAMMING: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#DynamicProgramming
// GREEDY: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#GreedyAlgorithms
// DIVIDE AND CONQUER NOT STUDIED YET
// QUIZS: http://geeksquiz.com/algorithms/