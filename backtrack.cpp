#include <iostream>
#include <set>
#include <vector>
using namespace std;

/* =========================Helper declarations and functions ====================================*/

/* =================================Print All Permutations of a String============================*/
// http://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/

void stringPermutations (string& str, int l, int r) {
    // O(N!) time  (N is str length)
    if (l == r) { cout << str << ", "; return; }

    for (int i = l; i <= r; i++)
    {
        char tmp  = str[l]; str[l] = str[i]; str[i] = tmp;  //swap l with i
        stringPermutations(str, l+1, r);
        char tmp2 = str[l]; str[l] = str[i]; str[i] = tmp2; //unswap l with i
    }
}

/* ===========================String Permutations without Repeats=================================*/
void stringPermutationsNoRepeats (string& str, int l, int r) {
    // O(N!) time (N is str length), O(N-1 + N-2 + ... + 1) space = O(N^2) space
    // Another solution is to store all generated permutations in a set, but it needs O(N!) space !!
    if (l == r) { cout << str << ", "; return; }

    set<char> startingWith;
    for (int i =l; i <= r; i++)
    {
        // Check if we haven't visited a solution where the element str[i] has been in the
        // l position after swapping

        if ( startingWith.find(str[i]) == startingWith.end() )
        {
            char tmp  = str[l]; str[l] = str[i]; str[i] = tmp;
            stringPermutationsNoRepeats (str, l+1, r);
            char tmp2 = str[l]; str[l] = str[i]; str[i] = tmp2;
            startingWith.insert(str[i]);
        }
    }
}

/* =====================================All Subsets of a Set======================================*/
// http://qa.geeksforgeeks.org/3390/print-all-possible-subsets
// http://qa.geeksforgeeks.org/3478/this-problem-extension-print-all-possible-subsets-problem

void allSubsets ( vector<int>& array, vector<int>& current, int i,
                  vector<vector<int> >& all) {
    // O(2^N) time where N is array.size(). O(2^N) space because we keep them in 'all'

    if (i < 0) {
        all.push_back(current);
    } else {
        // Don't include element i
        allSubsets (array, current, i-1, all);

        // Include it
        current.insert(current.begin(), array[i]);
        allSubsets (array, current, i-1, all);
        current.erase(current.begin());
    }
}

void allSubsetsIterative (vector<int>& array, vector<vector<int> >& all) {
    // O(2^N) time where N is array.size(). O(2^N) space because we keep them in 'all'
    int n = array.size();
    int power2N = 1 << n;
    for (int i = 0; i < power2N; i++)
    {
        vector<int> tmp; int index = 0;
        for (int b = i; b > 0; b = b >> 1) {
            if (b & 1) tmp.insert(tmp.end(), array[index]);
            index++;
        }
        all.insert(all.end(), tmp);
    }
}

/* ================================Rat in a Maze==================================================*/
// http://www.geeksforgeeks.org/backttracking-set-2-rat-in-a-maze/

#define N 4
bool ratMaze (int maze[N][N], int x, int y, int sol[N][N]) {
    // O(2^(N^2)) time complexity (b^n , where b is branching factor(in this case 2).)
    if ((x == N-1) && (y == N-1)) return true;

    sol[x][y] = 1;
    if ( (x+1 < N) && maze[x+1][y] && ratMaze(maze, x+1, y, sol) ) return true;
    if ( (y+1 < N) && maze[x][y+1] && ratMaze(maze, x, y+1, sol) ) return true;
    sol[x][y] = 0;
    return false;
}
// This can be solved in linear time using BFS (looking for the shortest path from some source to
// the destination)

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void stringPermutations_example() {
    string example="HELLO";
    cout << "String Permutations are:\t\t [";
    stringPermutations(example, 0, 3);
    cout << "]" << endl;

}
void stringPermutationsNoRepeats_example() {
    string example="HELLO";
    cout << "String Permutations with no repeats are: [";
    stringPermutationsNoRepeats(example, 0, 3);
    cout << "]" << endl;
}
void allSubsets_example() {
    vector<int> v = {1,2,3};
    vector<int> current;
    vector<vector<int> > all;

    allSubsets(v, current, 2, all);
    cout << "All subsets are: ";
    for (auto& s: all) {
        cout << "[";
        for (auto& e : s) {
            cout << e << ", ";

        } cout << "] ";
    }
    cout << endl;

    all = vector<vector<int> > ();
    allSubsetsIterative(v, all);
    cout << "All subsets are: ";
    for (auto& s: all) {
        cout << "[";
        for (auto& e : s) {
            cout << e << ", ";

        } cout << "] ";
    }
    cout << endl;
}
void ratMaze_example() {
    int maze[N][N] = { {1, 0, 0, 0},
                       {1, 1, 1, 1},
                       {0, 1, 0, 0},
                       {1, 1, 1, 1} };
    int sol[N][N]  = { {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0} };
    cout << "Rat Maze solution: ";
    if (ratMaze(maze, 0, 0, sol)) {
        cout << endl;
        for (int i = 0; i < N; i++) {
            cout << "\t";
            for (int j = 0; j < N; j++) {
                cout << sol[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution found" << endl;
    }
}
/* ===============================================================================================*/
int main() {
    stringPermutations_example();
    stringPermutationsNoRepeats_example();
    allSubsets_example();
    ratMaze_example();
}

/* =======================================TODO====================================================*/
// BACKTRACKING: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#Backtracking