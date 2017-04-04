#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <climits>
using namespace std;

/* =========================Helper declarations and functions ====================================*/
struct Node {
    int data;
    Node* left;
    Node* right;
    int dp_sol;     // for the DP version
};

Node* newNode (int data) {
    Node* tmp              = new Node;
    tmp->data              = data;
    tmp->dp_sol            = 0;
    tmp->left = tmp->right = NULL;
    return tmp;
}

void deleteTree (Node* root) {
    if (!root) return;
    deleteTree(root->left); deleteTree(root->right);
    delete root;
}
bool dictionary(const string word) { // For Word-Break problem
    string dictionary[] = {"mobile","samsung","sam","sung","man","mango",
                           "icecream","and","go","i","like","ice","cream"};
    int size = sizeof(dictionary)/sizeof(dictionary[0]);
    for (int i = 0; i < size; i++)
        if (dictionary[i].compare(word) == 0)
            return true;
    return false;
}
/* ===============================================================================================*/
// IMPORTANT:
// Not all backtracking algorithms can be transformed into DP solutions.
// Think about if a state in the search space can be reached by multiple other states, if the search
// space can be encoded efficiently (also in space), and if you can find a solution for a given
// state based on the solutions of smaller states that have been already visited (you must identify
// which smallers states to access and how their solutions can be combined to generate a solution
// for the bigger state). Normally you'll have a recurrence equation.
// In addition to finding optimal solutions to some problem, dynamic programming can also be used
// for counting the number of solutions
//
// https://en.wikipedia.org/wiki/Dynamic_programming
// http://stackoverflow.com/questions/6164629/dynamic-programming-and-memoization-bottom-up-vs-top-\
//        down-approaches
//
// Reconstruct answer:
//         https://www.quora.com/How-do-I-reconstruct-the-actual-optimal-solution-obtained-using-\
//                 dynamic-programming
//         http://stackoverflow.com/questions/29447416/printing-the-path-traversed-in-a-dynamic-\
//                programming-solution
//         https://www.quora.com/How-do-I-print-dynamic-programming-solutions
//
// Reconstruct all answers:
//          https://www.quora.com/Is-there-a-way-to-print-out-all-solutions-to-the-0-1-Knapsack-\
//                  problem-using-dynamic-programming-in-O-nC-time
//

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

/* ==============================Egg Dropping Problem=============================================*/
// http://www.geeksforgeeks.org/dynamic-programming-set-11-egg-dropping-puzzle/
// http://datagenetics.com/blog/july22012/index.html
// https://www.reddit.com/r/programming/comments/wxmyc/the_two_egg_problem/

// A binary search solution will not work (optimally) for two eggs. Let’s imagine we did try a
// binary search and dropped our first egg from floor 50. If it broke, we’d be instantly reduced to
// a one egg problem, so then we would have to start with our last egg from floor 1 and keep going
// up one floor at a time until that breaks. As a worst case, it will take us 50 drops.
// We can do better … : What happens if we started off with our first egg going up by floors ten at
// a time? We can start dropping our egg from floor 10; if it survives we try floor 20, then floor
// 30...  The worst case would be if the solution was on floor 99, and this would take us nine more
// drops to determine. The worst case therefore, if we go by tens, is 19 drops.
//
// What we need is a strategy that tries to make solutions to all possible answers the same depth
// (same number of drops). The way to reduce the worst case is to attempt to make all cases take the
// same number of drops. If the solution lays somewhere in a floor low down, then we have
// extra-headroom when we need to step by singles, but, !!!! as we get higher up the building, we’ve
// already used drop chances to get there, so there we have less drops left when we have to switch
// to going floor-by-floor!!! . What we need is a solution that minimizes our maximum regret.
//
// n + (n-1) + (n-2) + (n-3) + (n-4) + ... + 1  >=  100  --> min { n(n+1)/2 >= 100 } --> n == 14
//
// For more than 2 eggs: We need to select our first egg such that, if it breaks, or does not break,
// it results in a problem, which recursively is now a two egg problem, that we already know how to
// solve to minimize maximum regret!
//
// If we drop an egg from floor n, one of two events happens:
//    1) The egg breaks, so now our problem is reduced to a tower of height n-1, and we now have
//       e-1 eggs.
//    2) The egg doesn't break and now we need to check k-n floors and we still have e eggs.
//
//   Remember we need to mimimize the number of drops in the worst case, so we take the higher (max)
//   of these two situations, and select the floor which yields the minimum number of drops.


int eggDrop (int e, int f) {
    // Backtracking : O (2^f)  ?¿ SUM(1 <= t <= f, (f choose t) ) = O(2^f)
    if (f <= 1) return f;
    if (e == 1) return f;

    int min_tries = f;
    for (int i = 1; i <= f; i++) {
        min_tries = min ( min_tries , 1 + max (eggDrop (e-1, i-1), // egg breaks
                                               eggDrop (e,   f-i)  // egg does not break
                                              )
                        );
    }
    return min_tries;
}

int eggDrop_dyn (int e, int f) {
    // Dynamic programming: O(E*F^2) time, O(E*F) space
    int minEggs[e+1][f+1];

    for (int i = 0; i <= e; i++) {
        for (int j = 0; j <= f; j++)
        {
            if (i <= 1 || j <= 1) minEggs[i][j] = j;
            else {
                int min_tries = f;
                for (int k = 1; k <= j; k++) { // Floor at which we start dropping egg
                    min_tries = min (min_tries, 1 + max ( minEggs[i-1][k-1],  // egg breaks
                                                          minEggs[i][j-k]     // egg does not break
                                                         )
                                     );
                }
                minEggs[i][j] = min_tries;
            }
        }
    }
    return minEggs[e][f];
}

map<pair<int,int>,int> egg_memory;

int eggDrop_mem (int e, int f) {
    // Dynamic programming with memoization approach (top-down DP)
    // Simpler Code and Direct Translation from backtracking version, but complexity is harder to
    // determine

    if (e <= 1 || f <= 1) return f;

    // Check if we have the solution already in the memory
    if (egg_memory.find (std::make_pair(e,f) ) != egg_memory.end() ) {
        return egg_memory[std::make_pair(e,f)];
    }

    int min_tries = f;
    for (int i = 1; i <= f; i++) {
        min_tries = min ( min_tries , 1 + max (eggDrop_mem (e-1, i-1), // egg breaks
                                               eggDrop_mem (e,   f-i)  // egg does not break
                                              )
                        );
    }

    // Store in memory and return
    egg_memory[std::make_pair(e,f)] = min_tries;
    return min_tries;
}

/* ====================================House Robber===============================================*/
// http://codercareer.blogspot.com.es/2013/02/no-44-maximal-stolen-values.html
// http://www.programcreek.com/2014/03/leetcode-house-robber-java/

int houseRobber (vector<int>& array, int h) {
    // Backtracking: number of strings without consecutive 1's  (O(2^H) time complexity)
    if (h <= 0)  return 0;
    if (h == 1) return array[0];
    return max (array[h-1] + houseRobber(array, h-2) , houseRobber(array, h-1));
}

map<int, int> house_memory;
int houseRobber_mem (vector<int>& array, int h) {
    // Dynamic programming with memoization: O(H) space and O(H) time complexity
    if (h <= 0)  {return 0;}
    if (h == 1)  {return array[0];}

    if (house_memory.find(h) != house_memory.end()) return house_memory[h];

    int robit = array[h-1] + houseRobber_mem(array, h-2);
    int skip  =            houseRobber_mem(array, h-1);
    int res   = max(robit, skip);

    house_memory[h] = res;
    return res;
}

int house_robber_dyn (vector<int> arr, int n, vector<int>& parent, vector<int>& robbed_res) {
    // Dynamic programming (bottom-up approach) : O(N) time and O(N) space

    vector<int> robbed(arr.size()+1); // will be assigned to robbed_res, so that I can show how to
                                      // reconstruct an answer based on robbed and not on parent
                                      // (to avoid extra space)
    robbed[0] = 0;
    parent[0] = 0;
    robbed[1] = arr[0];
    parent[1] = 1;

    for (int i = 2; i <= n; i++) {
        robbed[i] = max (robbed[i-1], arr[i-1] + robbed[i-2]);

        if (robbed[i-1] > (arr[i-1] + robbed[i-2])) {
            parent[i] = i-1;
        } else {
            parent[i] = i-2;
        }
    }

    robbed_res = robbed;
    return robbed[n];
}

void printSolution_houseRobber_dyn (vector<int> parent, int n) {
    // We could do an iterative version too, but it requires a stack anyway, so space and time
    // comlexities are O(N) . This recursive version uses the call stack to store data too
    if (n == 0) return;

    if (parent[n] != n)     printSolution_houseRobber_dyn(parent, parent[n]);
    if (n != parent[n] + 1) cout << n << ", ";
}

void printSolution2_houseRobber_dyn (vector<int> arr, vector<int>& robbed, int n) {
    if (n <= 0) return;

    // Get parent for n
    int parent;
    if (robbed[n-1] > (arr[n-1]) + robbed[n-2] ) parent = n-1;
    else                                         parent = n-2;

    if (parent != n)      printSolution2_houseRobber_dyn(arr, robbed, parent);
    if (n != parent + 1)  cout << n << ", ";
}

/* =============================Color Houses With Minimum Cost====================================*/
// http://karmaandcoding.blogspot.com.es/2012/02/house-coloring-with-red-blue-and-green.html
// http://stackoverflow.com/questions/15630743/is-house-coloring-with-three-colors-np

int colorHouses (vector<int>& r, vector<int>& g, vector<int>& b, int n, int prevColor = 'n') {
    // Backtracking solution: O(2^N) time complexity
    if (n == 0) return 0;

    if (prevColor == 'n') {
        return min (r[n-1] + colorHouses (r, g, b, n-1, 'r'),
               min (g[n-1] + colorHouses (r, g, b, n-1, 'g'),
                    b[n-1] + colorHouses (r, g, b, n-1, 'b')));
    } else if (prevColor == 'r') {
        return min ( g[n-1] + colorHouses(r, g, b, n-1, 'g'),
                     b[n-1] + colorHouses(r, g, b, n-1, 'b'));
    } else if (prevColor == 'g') {
        return min ( r[n-1] + colorHouses(r, g, b, n-1, 'r'),
                     b[n-1] + colorHouses(r, g, b, n-1, 'b'));
    } else {
        return min ( r[n-1] + colorHouses (r, g, b, n-1, 'r'),
                     g[n-1] + colorHouses (r, g, b, n-1, 'g'));
    }
}

int colorHouses_dyn (vector<int>& r,vector<int>& g, vector<int>& b) {
    // Dynamic programming: O(N) time, O(N) space
    int bestColor[3][r.size()];  //'0' is r, '1' is g, '2' is b

    bestColor[0][0] = bestColor[1][0] = bestColor[2][0] = 0;
    for (int i = 1; i <= r.size(); i++) {
        bestColor[0][i] = r[i-1] + min (bestColor[1][i-1], bestColor[2][i-1]);
        bestColor[1][i] = g[i-1] + min (bestColor[0][i-1], bestColor[2][i-1]);
        bestColor[2][i] = b[i-1] + min (bestColor[0][i-1], bestColor[1][i-1]);
    }
    int n = r.size(); // or b.size() or g.size();
    return min (bestColor[0][n], min(bestColor[1][n], bestColor[2][n]) );
}

/*============================Knapsack Problem====================================================*/
// http://www.geeksforgeeks.org/dynamic-programming-set-10-0-1-knapsack-problem/
// This is an NP-complete problem. The dynamic solution providedd below is PSEUDO-POLYNOMIAL, as its
// time complexity depends on target sack of weight W, that is not polynomial wrt length of the
// input.

int knapsack (int leftW, vector<int>& weights, vector<int>& vals, int n) {
    // Backtracking solution: O(total number of subsets) = O(2^n) time complexity
    if (n == 0) return 0;

    if (leftW < weights[n-1]) return (leftW, weights, vals, n-1);
    else
        return max (             knapsack(leftW, weights, vals, n-1),
                     vals[n-1] + knapsack(leftW - weights[n-1], weights, vals, n-1) );
}

int knapsack_dyn (int W, vector<int>& weights, vector<int>& vals) {
    // Dynamic programming: O(N*W) time, O(N*W) space  (pseudo-polynomial)
    int bestValue[weights.size() + 1][W + 1];

    for (int i = 0; i <= weights.size(); i++) {
        for (int j = 0; j <= W; j++) {
            if (!i)  bestValue[i][j] = 0;
            else {
                if (weights[i-1] <= j) {
                    bestValue[i][j] = max (vals[i-1] + bestValue[i-1][j-weights[i-1]] ,
                                                       bestValue[i-1][j]);
                }
                else
                    bestValue[i][j] = bestValue[i-1][j];
            }
        }
    }
    return bestValue[weights.size()][W];
}

/*=================================Subset Sum Problem=============================================*/
// http://www.geeksforgeeks.org/dynamic-programming-subset-sum-problem/
// Very similar to the Knapsack problem, as different subsets are generated

bool subsetSum (int leftS, vector<int> vals, int n) {
    // Backtracking solution: O(2^N) time
    if (!leftS) return true;
    if (!n)     return false;
    if (vals[n-1] > leftS) return subsetSum(leftS, vals, n-1);
    else                   return subsetSum(leftS,           vals, n-1) ||
                                  subsetSum(leftS-vals[n-1], vals, n-1);
}

bool subsetSum_dyn (int S, vector<int> vals) {
    // Dynamic programming solution: O(N*S) time and O(N*S) space
    bool subsetSum[vals.size()+1][S+1];

    for (int i = 0; i <= vals.size(); i++) {
        for (int j = 0; j <= S; j++) {
            if      (!i) subsetSum[i][j] = false;
            if      (!j) subsetSum[i][j] = true;
            if (i && j) {
                if (vals[i-1] > j)  subsetSum[i][j] = subsetSum[i-1][j];
                else                subsetSum[i][j] = subsetSum[i-1][j] ||
                                                      subsetSum[i-1][j-vals[i-1]];
            }
        }
    }
    return subsetSum[vals.size()][S];
}

/*==============================Largest Independent Set (Binary Trees)============================*/
// http://www.geeksforgeeks.org/largest-independent-set-problem/
// Similar to House Robbing Problem and Number of Binary Strings without consecutive 1s
// This code below is a modification, instead of returning the maximum size of allindependent sets,
// we compute the maximum sum of all independent sets. The original problem is equivalent to this.
// Change 'int including = root->data;' to 'int including = 1;'

int largestIndependentSet (Node* root) {
    // Backtracking solution: Worst Case is when tree is a list of Nodes.
    // Time complexity is equivalent to the number of strings without consecutive 1s. O(2^N)
    //
    if (!root) return 0;
    int excluding = largestIndependentSet (root->left) + largestIndependentSet(root->right);
    int including = root->data;
    if (root->left)  including += largestIndependentSet(root->left->left)  +
                                  largestIndependentSet(root->left->right);
    if (root->right) including += largestIndependentSet(root->right->left) +
                                  largestIndependentSet(root->right->right);
    return max (including, excluding);
}

int largestIndependentSet_dyn (Node* root) {
    // Dynamic programming (top-bottom approach, easier) : O(N) time complexity, O(N) space complex.
    if (!root) return 0;

    // Check if we have to solution already computed
    if (root->dp_sol) return root->dp_sol;

    int excluding = largestIndependentSet_dyn (root->left) + largestIndependentSet_dyn(root->right);
    int including = root->data;
    if (root->left)  including += largestIndependentSet_dyn(root->left->left)  +
                                  largestIndependentSet_dyn(root->left->right);
    if (root->right) including += largestIndependentSet_dyn(root->right->left) +
                                  largestIndependentSet_dyn(root->right->right);

    // Memorize result and return it
    root->dp_sol = max (excluding, including);
    return root->dp_sol;
}

/* ===============================Weighted Job Sheduling==========================================*/
// http://www.geeksforgeeks.org/weighted-job-scheduling/
struct Job {
    int start;
    int finish;
    int profit;
};

int closestNonOverlapping (vector<Job>& array, int p) {
    for (int i = p-1; i >= 0; i--) { if (array[p].start >= array[i].finish) return i; }
    return -1;
}

// We assume Job array is sorted by 'finish' time (increasingly)
int jobScheduling (vector<Job>& array, int n) {
    // Backtracking solution: O(2^n) time complexity
    if (n <= 0) return 0;

    int pos = closestNonOverlapping(array, n-1);

    // Explore solutions that include job at position n and those solutions that do not.
    // If we include it, then when backtracking we must start considering jobs from position 'pos'
    // (because all those jobs at positions > 'pos' overlap with the job at position 'n' [current])
    int include = array[n-1].profit + jobScheduling(array, pos+1);
    int exclude = jobScheduling(array, n-1);
    return max (include, exclude);
}

int jobScheduling_dyn (vector<Job>& array) {
    int maxProfit[array.size() + 1];

    for (int i = 0; i <= array.size(); i++) {
        if (!i) maxProfit[i] = 0;
        else {
            int pos     = closestNonOverlapping(array, i-1);
            int include = array[i-1].profit + maxProfit[pos+1];
            int exclude =                     maxProfit[i-1];
            maxProfit[i] = max (include, exclude);
        }
    }
    return maxProfit[array.size()];
}

/* ==================Shortest Path with exactly k edges (directed+weighted graph)=================*/
// http://www.geeksforgeeks.org/shortest-path-exactly-k-edges-directed-weighted-graph/
// http://www.geeksforgeeks.org/count-possible-paths-source-destination-exactly-k-edges/

#define V 4
int shortestKPath (int graph[V][V], int src, int dst, int k) {
    // Backtracking approach: O(V^k) time complexity
    if (k==0 && (src == dst))               return 0;
    if (k==1 && graph[src][dst] != INT_MAX) return graph[src][dst];
    if (k < 0)                              return INT_MAX;

    int shortest = INT_MAX;
    for (int i = 0; i < V; i++) {
        if (graph[src][i] != INT_MAX && i != src && i != dst) {
            int cost = shortestKPath(graph, i, dst, k-1);
            if (cost != INT_MAX) {
                shortest = min (shortest, graph[src][i] + cost);
            }
        }
    }
    return shortest;
}

int shortestKPath_dyn (int graph[V][V], int src, int dst, int k) {
    // Dynamic programming: O(V^3 * k) time complexity, O(V^2 * k) space
    int shortestPath[V][V][k+1];

    for (int s = 0; s <= k; s++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                shortestPath[i][j][s] = INT_MAX;
                if (s == 0 && i == j)                  shortestPath[i][j][s] = 0;
                if (s == 1 && graph[i][j] != INT_MAX)  shortestPath[i][j][s] = graph[i][j];
                if (s > 1) {
                    for (int z = 0; z < V; z++) {
                        if (i != z && z != j && graph[i][z] != INT_MAX &&
                               shortestPath[z][j][s-1] != INT_MAX)
                        {
                            shortestPath[i][j][s] = min (shortestPath[i][j][s],
                                                         shortestPath[z][j][s-1] + graph[i][z]);
                        }
                    }
                }
            }
        }
    }
    return shortestPath[src][dst][k];
}

/* =================================Is String Interleaved of Two Others===========================*/
// http://www.geeksforgeeks.org/check-whether-a-given-string-is-an-interleaving-of-two-other-given-\
//        strings-set-2/
bool isInterleaved (const char* str, const char* a, const char* b) {
    // Backtracking: O(2^(N+M)) time complexity

    if (*str == '\0' && *a == '\0' && *b == '\0')
        return true;
    if (*str == '\0')
        return false;

    return (  ((*str == *a) && isInterleaved(str+1, a+1, b))  ||
              ((*str == *b) && isInterleaved(str+1, a, b+1)) );
}

bool isInterleaved_dyn(const char* S, const char* A, const char* B) {
    // Dynamic programmin O(M*N) time&space complexity
    int M = strlen(A), N = strlen(B);

    bool IL[M+1][N+1];
    memset(IL, 0, sizeof(IL)); // Initialize all values as false.

    if ((M+N) != strlen(S))
       return false;

    for (int i = 0; i <= M; ++i) {
        for (int j = 0; j <= N; ++j) {
            if (i==0 && j==0)
                IL[i][j] = true;

            else if (i==0 && B[j-1]==S[j-1])
                IL[i][j] = IL[i][j-1];

            else if (j==0 && A[i-1]==S[i-1])
                IL[i][j] = IL[i-1][j];

            else if(A[i-1]==S[i+j-1] && B[j-1]!=S[i+j-1])
                IL[i][j] = IL[i-1][j];

            else if (A[i-1]!=S[i+j-1] && B[j-1]==S[i+j-1])
                IL[i][j] = IL[i][j-1];

            else if (A[i-1]==S[i+j-1] && B[j-1]==S[i+j-1])
                IL[i][j]=(IL[i-1][j] || IL[i][j-1]) ;
        }
    }
    return IL[M][N];
}

/* ==============================Break Sentence Into Words From Dictionary========================*/
// http://www.geeksforgeeks.org/dynamic-programming-set-32-word-break-problem/
// http://thenoisychannel.com/2011/08/08/retiring-a-great-interview-problem

string wordBreak(const string str) {
    // Backtracking: O((2^N)*x) time Complexity (*x comes because of dictionary cost)
    int len = str.size();

    if (len == 0)        return "";
    if (dictionary(str)) return str;

    for (int i = 1; i <= len; i++) {
        string substring = str.substr(0,i);
        if (dictionary(substring)) {
            string res = wordBreak(str.substr(i,len-1));
            if (res != "") {
                return substring + " "+ res;
            }
        }
    }
    return "";
}

map<string,string> wordbreak_mem;
string wordBreak_mem (const string str) {
    // Dynamic programming (top-bottom approach) : O(N^2*x) time complexity, O(N^2) space complexity
    int len = str.size();
    if (len == 0)        return "";
    if (dictionary(str)) return str;

    if (wordbreak_mem.find(str) != wordbreak_mem.end()) return wordbreak_mem[str];

    for (int i = 1; i <= len; i++) {
        string substring = str.substr(0,i);
        if (dictionary(substring)) {
            string breaks = wordBreak_mem(str.substr(i,len-1));
            if (breaks != "") {
                wordbreak_mem[str] = substring + " " + breaks;
                return wordbreak_mem[str];
            }
        }
    }
    return "";
}

/* ===============================Longest Common Substring========================================*/

/* =============================Longest Palindromic Substring=====================================*/

/* ===========================Longest Increasing Subsequence======================================*/
// http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/
// http://algorithms.tutorialhorizon.com/dynamic-programming-longest-increasing-subsequence/

// IMPORANT: We are looking for a set of a Sequence, not a Segment (not consecutive always)
int longestIS_dyn(vector<int> arr){
    // Dynamic programmin: O(N^2) time complexity, O(N) spaces
    int LIS[arr.size()+1];
    int global_max = 0;
    for (int i = 0; i < arr.size(); i++) {
        int maxim = -1;
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                maxim = max(maxim, 1+LIS[j]);
                global_max = max (global_max, maxim);
            }
        }
        if (maxim == -1) LIS[i] = 1;
        else LIS[i] = maxim;
    }
    return global_max;
}

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void numWays_example() {
    int n = 10;
    cout << "Number of ways to cover distance 10 is: " << numWays(n)     << endl;
    cout << "Number of ways to cover distance 10 is: " << numWays_dyn(n) << endl;
}
void catalan_example() {
    int n = 6;
    cout << "Catalan number for n=6 is: " << catalan(6)     << endl;
    cout << "Catalan number for n=6 is: " << catalan_dyn(6) << endl;
}
void numPathsMatrix_example() {
    cout << "Number of paths in a 9x10 matrix is: " << numPathsMatrix(9,10)     << endl;;
    cout << "Number of paths in a 9x10 matrix is: " << numPathsMatrix_dyn(9,10) << endl;
}
void fib_example() {
    cout << "Fibonacci number for n=9 is: " << fib(9)                   << endl;
    cout << "Fibonacci number for n=9 is: " << fib_dyn(9)               << endl;
    cout << "Fibonacci number for n=9 is: " << fib_dyn2(9)              << endl;
    cout << "Fibonacci number for n=9 is: " << fib_mem_divideconquer(9) << endl;
}
void countBinaryStrings_example() {
    cout << "Binary Strings without Consecutive 1s for n=4 : " << countBinaryStrings_dyn(4) << endl;
    cout << "Binary Strings without Consecutive 1s for n=4 : " << countBinaryStrings(4,-1)  << endl;
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
void eggDrop_example() {
    cout << "Worst-case tries for 2 eggs and 20 floors is : " << eggDrop(2, 20)     << endl;
    cout << "Worst-case tries for 2 eggs and 20 floors is : " << eggDrop_dyn(2, 20) << endl;
    cout << "Worst-case tries for 2 eggs and 20 floors is : " << eggDrop_mem(2, 20) << endl;
}
void houseRobber_example() {
    vector<int> arr    = {6, 1, 2, 7, 9, 15};
    vector<int> parent( arr.size() + 1 , -1);
    vector<int> robbed;
    cout << "Maximum value stolen in houses is: " << houseRobber(arr, 6)     << endl;
    cout << "Maximum value stolen in houses is: " << houseRobber_mem(arr, 6) << endl;

    cout << "Maximum value stolen in houses is: " << house_robber_dyn(arr, 6, parent,robbed) << " ";

    //cout << "with solution: [" ; printSolution_houseRobber_dyn(parent, 6); cout << "]" << endl;

    cout << "with solution: [" ;
    printSolution2_houseRobber_dyn(arr, robbed, 6);
    cout << "]" << endl;
}
void colorHouses_example() {
    vector<int> r= {7,3,8,6,1,2};
    vector<int> g = {5,6,7,2,4,3};
    vector<int> b = {10,1,4,9,7,6};
    cout << "Cheapest house coloring is : " << colorHouses(r, g, b, r.size()) << endl;
    cout << "Cheapest house coloring is : " << colorHouses_dyn(r, g, b) << endl;
}
void knapsack_example() {
    vector<int> val = {60, 100, 120};
    vector<int> wt  = {10, 20, 30};
    int W = 50;
    cout << "Best knapsack value is : " << knapsack(W, wt, val, val.size()) << endl;
    cout << "Best knapsack value is : " << knapsack_dyn(W, wt, val)         << endl;
}
void subsetSum_example() {
    vector<int> set = {2,3,4,5,6,7,8,9,10,11,12};
    int sum = 25;
    cout << "Is there a subset whose elements sum 25? : " <<subsetSum(sum, set, set.size()) <<endl;
    cout << "Is there a subset whose elements sum 25? : " <<subsetSum_dyn (sum, set)        <<endl;
}
void largestIndependentSet_example() {
     Node *root                = newNode(20);
     root->left                = newNode(8);
     root->left->left          = newNode(4);
     root->left->right         = newNode(12);
     root->left->right->left   = newNode(10);
     root->left->right->right  = newNode(14);
     root->right               = newNode(22);
     root->right->right        = newNode(25);

     cout << "Maximum value across independent sets is : " << largestIndependentSet(root)    <<endl;
     cout << "Maximum value across independent sets is : " << largestIndependentSet_dyn(root)<<endl;

     deleteTree(root);
}
bool jobSortFunc(Job a, Job b) {return a.finish < b.finish;}
void jobScheduling_example() {
    vector<Job> arr = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};

    std::sort(arr.begin(), arr.end(), jobSortFunc);
    // Function assumes sorted Job array by 'finish' time (using ugly c++11 lambda function syntax)
    //std::sort(arr.begin(), arr.end(), [] (Job a, Job b) {return a.finish < b.finish} );
    cout << "Maximum job scheduling profit is : " << jobScheduling(arr, arr.size()) << endl;
    cout << "Maximum job scheduling profit is : " << jobScheduling_dyn(arr)         << endl;
}
void shortestKPath_example() {
    int graph[V][V] = { {0, 10, 3, 2},
                        {INT_MAX, 0, INT_MAX, 7},
                        {INT_MAX, INT_MAX, 0, 6},
                        {INT_MAX, INT_MAX, INT_MAX, 0}
                       };
    int u = 0, v = 3, k = 2;
    cout << "Weight of shortest path is " << shortestKPath(graph,u,v,k)     << endl;
    cout << "Weight of shortest path is " << shortestKPath_dyn(graph,u,v,k) << endl;
}
void isInterleaved_example() {
    const char* interleaved = "XXZXXY";
    const char* a           = "XXY";
    const char* b           = "XXZ";

    cout << "Is an Interleaved Word? : " << isInterleaved(interleaved, a, b)     << endl;
    cout << "Is an Interleaved Word? : " << isInterleaved_dyn(interleaved, a, b) << endl;
}
void longestIS_example() {
    vector<int> arr = { 10, 22, 9, 33, 21, 50, 41, 60 };
    cout << "Longest Increasing Subsequence is: " << longestIS_dyn(arr) << endl;
}
void wordbreak_example() {
    cout << "String broken into words is: " << wordBreak_mem("ilikesamsung") << endl;
    cout << "String broken into words is: " << wordBreak("ilikesamsung")     << endl;
}

/* ===============================================================================================*/
int main() {
    numWays_example();
    catalan_example();
    numPathsMatrix_example();
    fib_example();
    countBinaryStrings_example();
    maxSubMatrixOnes_example();
    eggDrop_example();
    houseRobber_example();
    colorHouses_example();
    knapsack_example();
    subsetSum_example();
    largestIndependentSet_example();
    jobScheduling_example();
    shortestKPath_example();
    isInterleaved_example();
    longestIS_example();
    wordbreak_example();
}

/* =======================================TODO====================================================*/
// BINOMIAL COEFFICIENTS
//     https://en.wikipedia.org/wiki/Binomial_coefficient
//     https://en.wikipedia.org/wiki/Binomial_coefficient#Pascal.27s_triangle
//
//     ( n )
//     (   ) is (n choose k): ways to choose a subset of k elements (disregarding order) from a
//     ( k )                  set of n elements
//
//
//     (n choose k) = n! / (k! * (n-k)!)
//
//     (n choose k) = (n-1 choose k-1) + (n-1 choose k)
//     (n choose 0) = (n choose n) = 1
//
//     (n choose k) = n/k * (n-1 choose k-1)
//
//     SUM( 0 <= k <= n , (n choose k) ) = 2^n
//
//
//
// DYNAMIC PROGRAMMING: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#DynamicProgramming
// https://www.quora.com/What-are-the-top-10-most-popular-dynamic-programming-problems-among-\
//         interviewers
// GREEDY: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#GreedyAlgorithms
// DIVIDE AND CONQUER NOT STUDIED YET
// https://math.dartmouth.edu/archive/m19w03/public_html/Section5-2.pdf
// https://www.nayuki.io/page/master-theorem-solver-javascript
// QUIZS: http://geeksquiz.com/algorithms/