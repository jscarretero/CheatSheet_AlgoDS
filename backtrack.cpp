#include <iostream>
#include <set>
#include <vector>
#include <list>
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
// the destination). This backtracking solution visits a cell or a path multiple times, whereas
// a BFS solution does not

/* ================================N Queens Problem===============================================*/
// http://www.geeksforgeeks.org/backtracking-set-3-n-queen-problem/
// A queen can move horizontally, vertically and diagonally

bool isSafe(int board[N][N], int row, int col) {
    // We need to check only left side for attacking queens
    int i, j;

    for (i = 0; i < col; i++)
        if (board[row][i]) return false;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return false;

    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j]) return false;
    return true;
}

bool nQueens (int board[N][N], int col) {
    // O(N! * N) time (number of permutations)
    if (col >= N) return true;

    for (int i = 0; i < N; i++) {
        if ( isSafe (board, i, col)) {
            board[i][col] = 1;
            if (nQueens(board, col+1)) return true;
            board[i][col] = 0;
        }
    }
    return false;
}

void printNQueensSolution(int board[N][N]) {
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << "\t";
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool allNQueens (int board[N][N], int col) {
    if (col == N) {
        printNQueensSolution(board); //change
        return true;
    }
    bool some = false; //changed
    for (int i = 0; i < N; i++) {
        if ( isSafe (board, i, col)) {
            board[i][col] = 1;
            some = allNQueens(board, col+1) || some;  //change
            board[i][col] = 0;
        }
    }
    return some; //changed
}

// If there's only so many possible states for the backtracking to explore, that's all it can
// explore. If you ensure your algorithm only visits each possible state once (and with a constant
// bound on time per state), then the number of possible states to explore is now an upper bound on
// the time complexity - irrespective of whether your algorithm uses backtracking

/* =====================All Valid Combinations of n-pairs of Parenthesis==========================*/
// From 'Cracking the Coding Interview'
// No repeats allowed!!

void validParenthesis (string& current_sol, vector<string>& solutions, int leftRem, int rightRem,
                       int pos) {
    // O(2^N) time
    if (leftRem > rightRem || leftRem < 0) return;
    if (!leftRem && !rightRem) { solutions.push_back(current_sol); return; }

    if (leftRem > 0) {
        current_sol[pos] = '(';
        validParenthesis(current_sol, solutions, leftRem-1, rightRem, pos+1);
    }

    if (rightRem > leftRem)  {
        current_sol[pos] = ')';
        validParenthesis(current_sol, solutions, leftRem, rightRem-1, pos+1);
    }
}

/* ==============================m- Graph Coloring================================================*/
// http://www.geeksforgeeks.org/backttracking-set-5-m-coloring-problem/

#define V 4

void printColoring (int colors[V]) {
    cout << "\t";
    for (int i = 0; i < V; i++) {
        cout << colors[i] << " ";
    }
    cout << endl;
}

bool canColor(bool graph[V][V], int vrtx, int c, int colors[V]) {
    for (int i = 0; i < vrtx; i++) {
        if (graph[vrtx][i] && colors[i] == c) return false;
    }
    return true;
}

bool graphColoring (bool graph[V][V], int vrtx, int m, int colors[V]) {
    // O(m^V) time
    if (vrtx == V) {
        printColoring(colors);
        return true;
    }
    bool some = false;
    for (int c = 0; c < m; c++) {
        if ( canColor(graph, vrtx, c, colors) ) {
            colors[vrtx] = c;
            some = graphColoring(graph, vrtx+1, m, colors) || some;
            colors[vrtx] = -1;
        }
    }
    return some;
}

/* ==============================All Hamiltonian Cycles===========================================*/
// http://www.geeksforgeeks.org/backtracking-set-7-hamiltonian-cycle/
// We start at vertex 0, it does no matter where we start, because all cycles must traverse all
// vertices
void printHamiltonian (list<int>& solution) {
    cout << "\t";
    for (auto& e: solution) {
        cout << e << ", ";
    }
    cout << endl;
}

bool canJumpTo (bool graph[V][V], int src, int to, vector<int>& visited) {
    if (!graph[src][to]) return false;
    if (visited[to])     return false;
    return true;
}

bool allHamiltonian (bool graph[V][V], int current, list<int>& current_sol, vector<int>& visited) {
    // Time O(V!)
    if (current_sol.size() == V) {
        int first = current_sol.front();
        int last  = current_sol.back();
        if (graph[last][first]) {
            printHamiltonian(current_sol);
            return true;
        } else return false;
    }

    bool some = false;
    for (int i = 0; i < V; i++) {
        if (canJumpTo(graph, current, i, visited)) {
            current_sol.push_back(i);
            visited[i] = true;
            some = allHamiltonian(graph, i, current_sol, visited) || some;
            visited[i] = false;
            current_sol.pop_back();
        }
    }
    return some;
}

/* ==========================Minimum sheets to bin-pack a set of rectangles=======================*/
// https://stackoverflow.com/questions/21078959/an-approach-to-implement-rectangular-bin-packing
// http://codeincomplete.com/posts/bin-packing/

struct NodeS {
    bool used;
    int  elemId;
    int  x;
    int  y;
    int  w;
    int  h;
    NodeS* down;
    NodeS* right;
};

struct Elem {
    int w;
    int h;
    int elemId;
};

NodeS* createNodeS (int x, int y, int w, int h) {
    NodeS* root = new NodeS;
    root->used   = false;
    root->elemId = -1;
    root->x      = x;
    root->y      = y;
    root->w      = w;
    root->h      = h;
    root->down   = NULL;
    root->right  = NULL;
    return root;
}

NodeS* findNodeS (NodeS* root, int elemId, int w, int h) {
    if (!root) {
        return NULL;
    }
    
    if (root->used) {
        NodeS* res = NULL;
        res = findNodeS(root->down, elemId, w, h);
        if (!res) {
            res = findNodeS(root->right, elemId, w, h);
        }
        return res;        
    } 
    
    if ((root->w >= w) && (root->h >=h)) {
        return root;
    }
    
    return NULL;
}

NodeS* splitNodeS (NodeS* root, int elemId, int w, int h) {
    //assert(!root->used);
    root->used   = true;
    root->elemId = elemId;
    root->right  = createNodeS(root->x + w, root->y, root->w - w, root->h);
    root->down   = createNodeS(root->x, root->y + h, root->w, root->h - h);
    return root;
}

void printTreeMap (NodeS* root) {
    if (!root) return;
    if (root->used) {
        cout << "\t" << root->elemId << " (" << root->x << "," << root->y << ")" << endl;
    }
    printTreeMap(root->down);
    printTreeMap(root->right);
}

vector<NodeS*> pack (vector<Elem>& elems, int w, int h) {
    vector<NodeS*> allSheets;
    NodeS* sheet = NULL;
    int numSheets = 0;
       
    for (int i = 0; i < elems.size(); i++) {
        NodeS* n = findNodeS(sheet, elems[i].elemId, elems[i].w, elems[i].h);
        if (!n) {
            numSheets++;
            if (sheet) allSheets.push_back(sheet);
            sheet = createNodeS(0, 0, w, h);
            n     = sheet;
        }
        NodeS* m = splitNodeS (n, elems[i].elemId, elems[i].w, elems[i].h);
    }   
    if (sheet) allSheets.push_back(sheet);
    return allSheets;
}

NodeS* deleteTreeS (NodeS* root) {
    if (root) {
        if (root->down)  deleteTreeS(root->down);
        if (root->right) deleteTreeS(root->right);
        delete root;
    }
}

void bestPack (vector<Elem>& elems, int w, int h, int l, int r, int& minSheets, 
               vector<NodeS*>& best) {
    // Backtrack to generate all elems permutations
    if (l == r) {
        vector<NodeS*> res = pack(elems, w, h);
        if (res.size() < minSheets) {
            minSheets = res.size();
            for (int i = 0; i < best.size(); i++) { deleteTreeS(best[i]); }
            best = res;
        } else {
            for (int i = 0; i < best.size(); i++) { deleteTreeS(res[i]); }
        }
    }    

    for (int i = l; i <= r; i++) {
        Elem tmp = elems[l]; elems[l] = elems[i]; elems[i] = tmp;  //swap
        bestPack(elems, w, h, l+1, r, minSheets, best);
             tmp = elems[l]; elems[l] = elems[i]; elems[i] = tmp;  //unswap
    }          
}

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
void nQueens_example() {
    int board[N][N] = { {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0}
    };
    cout << "N-Queens solutions are : ";
    allNQueens(board, 0);
}
void validParenthesis_example() {
    int num = 3;
    vector<string> solutions;
    string current_sol;
    for (int i = 0; i < num*2; i++)
        current_sol = current_sol + "-";

    validParenthesis(current_sol, solutions, num, num, 0);
    cout << "Valid parenthesis strings for n=3 are : [";
    for (auto& s: solutions) {
        cout << s << ", ";
    } cout << "]" << endl;

}
void graphColoring_example() {
    bool graph[V][V] = {{0, 1, 1, 1},
                        {1, 0, 1, 0},
                        {1, 1, 0, 1},
                        {1, 0, 1, 0},
                       };
    int colors[V];
    for (int i = 0; i < V; i++) colors[i] = -1;

    cout << "Graph 3-colorings are: " << endl;
    bool res = graphColoring(graph, 0, 3, colors);
    if (!res) cout << "\tNone" << endl;
}
void allHamiltonian_example() {
    bool graph[V][V] = {{0, 1, 1, 1},
                        {1, 0, 1, 1},
                        {1, 1, 0, 1},
                        {1, 1, 1, 0}
                       };
    list<int> curr_sol;
    vector<int> visited(4, false);
    curr_sol.push_back(0);
    visited[0] = true;
    cout << "All Hamiltonian cycles are: " << endl;
    bool found = allHamiltonian(graph, 0, curr_sol, visited);
    if (!found) cout << "None" << endl;
}
void bestPack_example() {
    vector<Elem> elems;
    elems.push_back({1,4,0});
    elems.push_back({1,2,1});
    elems.push_back({1,1,2});
    
    int minSheets = elems.size() + 1;
    vector<NodeS*> best;
    int w = 10;
    int h = 10;
    
    bestPack(elems, w, h, 0, elems.size() - 1, minSheets, best);
    //assert(minSheets == best.size());
    cout << "Best 2D bin-pack rectangle needs " << minSheets << " sheets. ";
    cout << "Best 2D bin-packing solution is: " << endl;
    for (int i = 0; i < best.size(); i++) {
        cout << "\t--- Sheet " << i << " ---" << endl; 
        printTreeMap(best[i]);
        cout << endl;
    }   
}

/* ===============================================================================================*/
int main() {
    stringPermutations_example();
    stringPermutationsNoRepeats_example();
    allSubsets_example();
    ratMaze_example();
    nQueens_example();
    validParenthesis_example();
    graphColoring_example();
    allHamiltonian_example();
    bestPack_example();
}

/* =======================================TODO====================================================*/
// BACKTRACKING: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#Backtracking
