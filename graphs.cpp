#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <algorithm>
#include <climits>    //INT_MIN, INT_MAX
using namespace std;

/* =========================Helper declarations and functions ====================================*/
class Graph {
    private:
        int numV;
        set<int>* adj;
    public:
        Graph(unsigned int numV);
        ~Graph();
        void addEdge(int s, int d);
        const set<int>& adjacent(int s);
        int numVertices();
};

Graph::Graph (unsigned int numV) {
    this->numV = numV;
    adj = new set<int>[numV];
}
Graph::~Graph() {
    delete[] adj;
}
void Graph::addEdge(int s, int d) {
    if (s >= numV || d >= numV || s < 0 || d < 0) return;
    adj[s].insert(d);
}
const set<int>& Graph::adjacent (int s) {
    return adj[s];
}
int Graph::numVertices() {
    return numV;
}
void process (int v) {
    cout << v << ", ";
}

/* =====================================Breadth-First Search======================================*/
// http://www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/
// http://www.geeksforgeeks.org/applications-of-breadth-first-traversal/

void BFS_util (Graph& g, int s, vector<bool>& visited) {
    // Time: O(V + E), space O(V)
    // vector<bool> visited (g.numVertices(), false);
    list<int> toVisit;

    visited[s] = true;
    toVisit.push_back(s);
    while ( !toVisit.empty() ) {
        int v = toVisit.front() ; toVisit.pop_front();
        process(v);
        for (auto& a : g.adjacent(v)) {
            if (!visited[a]) {
                visited[a] = true;
                toVisit.push_back(a);
            }
        }
    }
}

// Note that the above code traverses only the vertices reachable from a given source vertex. All
// the vertices may not be reachable from a given vertex (example Disconnected graph). To print all
// the vertices, we can modify the BFS function to:
void BFS (Graph& g, int s, bool all=false) {
    vector<bool> visited (g.numVertices(), false);

    BFS_util(g, s, visited);

    if (all) {
        for (int i = 0; i < g.numVertices(); i++) {
            if (!visited[i])
                BFS_util(g, i, visited);
        }
    }
}

/* =====================================Depth-First Search========================================*/
// http://www.geeksforgeeks.org/depth-first-traversal-for-a-graph/
// http://www.geeksforgeeks.org/applications-of-depth-first-search/
void DFS_util (Graph& g, int s, vector<bool>& visited) {
    // Time: O(V + E), space O(V)

    visited[s] = true;
    process(s);
    for ( auto& a: g.adjacent(s) ) {
        if (!visited[a]) {
            DFS_util(g, a, visited);
        }
    }
}

void DFS (Graph& g, int s, bool all=false) {
    vector<bool> visited (g.numVertices(), false);

    DFS_util(g, s, visited);

    if (all) {
        for (int i = 0; i < g.numVertices(); i++) {
            if (!visited[i])
                DFS_util(g, i, visited);
        }
    }
}

/* =============================Topological Sort==================================================*/
// http://www.geeksforgeeks.org/topological-sorting/

// REMEMBER: ACYCLIC AND DIRECTED Graph. Otherwise topological sorting makes NO sense
// Linear ordering of vertices such that for every directed edge uv, vertex u comes before v in the
// ordering.
// It is a modification of DFS, node is processed after visiting recursively all adjacent vertices
void TopologicalSort_Util (Graph& g, int s, vector<bool>& visited, stack<int>& result) {
    // TIME: O(V + E), space O(V)

    visited[s] = true;
    // process(s);         // Difference wrt DFS
    for ( auto& a: g.adjacent(s) ) {
        if (!visited[a]) {
            TopologicalSort_Util(g, a, visited, result);
        }
    }
    result.push(s);        // Difference wrt DFS
}

void TopologicalSort (Graph& g) {
    vector<bool> visited (g.numVertices(), false);
    stack<int> result;

    for (int i = 0; i < g.numVertices(); i++) {
        if (!visited[i])
            TopologicalSort_Util(g, i, visited, result);
    }

    for (stack<int> dump = result; !dump.empty(); dump.pop()) {
        process(dump.top());
    }
}

/* ============================Bipartite Undirected Acyclic Graph?================================*/
// http://www.geeksforgeeks.org/bipartite-graph/

// IDEA: Modification of BFS, equivalent to 2-coloring
bool isBipartite_Util (Graph& g, int s, vector<bool>& visited, vector<int>& colors) {
    // O (V + E) time, O(V) space

    list<int> toVisit;

    visited[s] = true;
    colors[s]  = 0;
    toVisit.push_back(s);

    while (!toVisit.empty()) {
        int v = toVisit.front(); toVisit.pop_front();
        for (auto& a : g.adjacent(v)) {
            if (!visited[a]) {
                visited[a] = true;
                colors[a] = 1 - colors[v];
                toVisit.push_back(a);
            } else if (a != v) {
                if (colors[a] == colors[v]) return false;
            }
        }
    }
    return true;
}

bool isBipartite (Graph& g) {
    vector<bool> visited (g.numVertices(), false);
    vector<int> colors(g.numVertices(), -1);

    for (int i = 0; i < g.numVertices(); i++) {
        if (!visited[i]) {
            if (!isBipartite_Util(g, i, visited, colors)) return false;
        }
    }
    return true;
}

/* =============================Node Reachability in Directed Graph===============================*/
//http://www.geeksforgeeks.org/find-if-there-is-a-path-between-two-vertices-in-a-given-graph/

// With Breadth First, we always reach a vertex from given source using minimum number of edges !
// Not with DFS

bool isPath (Graph& g, int s, int d, vector<int>& discoverer) {
    // BFS-version
    // O (V + E) time, O(V) space, similar to BFS
    vector<bool> visited (g.numVertices(), false);
    list<int> toVisit;

    visited[s] = true;
    toVisit.push_back(s);

    while (!toVisit.empty()) {
        int v = toVisit.front(); toVisit.pop_front();
        if (v == d) return true;
        for (auto& a : g.adjacent(v)) {
            if (!visited[a]) {
                discoverer[a] = v;
                visited[a] = true;
                toVisit.push_back(a);
            }
        }
    }
    return false;
}

bool pathAmong_util (Graph& g, int s, int d, vector<bool>& visited, list<int>& res) {
    // DFS version
    // O (V + E) time, O(V) space, similar to DFS
    visited[s] = true;
    res.push_back(s);

    if (s == d) return true;

    for ( auto& a: g.adjacent(s) ) {
        if (!visited[a]) {
            bool found = pathAmong_util(g, a, d, visited, res);
            if (found) return true;
        }
    }
    res.pop_back();
    return false;
}

bool pathAmong (Graph&g, int s, int d, list<int>& result) {
    vector<bool> visited (g.numVertices(), false);
    return pathAmong_util(g, s, d, visited, result);
}

/* ============================Is Cyclic a Directed Graph?========================================*/
// http://www.geeksforgeeks.org/detect-cycle-in-a-graph/
// http://www.geeksforgeeks.org/detect-cycle-undirected-graph/
// http://stackoverflow.com/questions/2869647/why-dfs-and-not-bfs-for-finding-cycle-in-graphs

// IDEA:
// DFS over BFS because: (i) easier to implement, (ii) Once DFS finds a cycle, the stack contain the
// nodes forming the cycle. The same is not true for BFS.

// IMPORTANT: For DIRECTED graphs! For undirected see belows

bool isCyclic_util (Graph& g, int s, vector<bool>& visited, vector<bool>& inProcess) {
    visited[s]   = true;
    inProcess[s] = true;
    for (auto& a : g.adjacent(s)) {
        if (inProcess[a]) return true;
        if (!visited[a]) {
            bool is = isCyclic_util(g, a, visited, inProcess);
            if (is) return true;
        }
    }
    inProcess[s] = false;
    return false;
}

bool isCyclic (Graph& g, vector<bool>& cycle) {
    vector<bool> visited (g.numVertices(), false);

    bool found = false;
    for (int i = 0; i < g.numVertices(); i++) {
        if (isCyclic_util(g, i, visited, cycle)) found = true;
    }
    return found;
}

/* ====================================Is Tree? (Undirected Graph)================================*/
//http://geeksquiz.com/check-given-graph-tree/

bool isCyclicUndirected_util (Graph& g, int s, vector<bool>& visited, int parent) {
    // O(V + E) time, O(V) space
    visited[s] = true;
    for (auto& a: g.adjacent(s)) {
        if (!visited[a]) {
            bool is = isCyclicUndirected_util(g, a, visited, s);
            if (is) return true;
        } else if (parent != a) return true;
    }
    return false;
}

// IDEA: Check there is no cycle and all vertex are connected
bool isTree (Graph& g) {
    // O(V + E) time, O(V) space
    vector<bool> visited (g.numVertices(), false);

    if (isCyclicUndirected_util(g, 0, visited, -1)) {return false; }

    for (int i = 0; i < g.numVertices(); i++)
        if (!visited[i]) {return false; }
    return true;
}

/* ============================Number of Connected Components in Undirected Graph=================*/
// http://quiz.geeksforgeeks.org/connected-components-in-an-undirected-graph/  (modification)
void numConnectedComponents_util (Graph& g, int s, vector<bool>& visited, set<int>& result) {
    // O(V + E) time, O(V) space, modification of DFS
    visited[s] = true;
    result.insert(s);
    for (auto& a: g.adjacent(s)) {
        if (!visited[a]) {
            numConnectedComponents_util(g, a, visited, result);
        }
    }
}

int numConnectedComponents (Graph& g, vector<set<int> >& result) {
    vector<bool> visited(g.numVertices(), false);

    for (int i = 0; i < g.numVertices(); i++) {
        if (!visited[i]) {
            set<int> component;
            numConnectedComponents_util(g, i, visited, component);
            result.push_back(component);
        }
    }
    return result.size();
}

#define VRT 9

/* ==================PRIM ALGORITHM (Minimum Spanning Tree WEIGHTED UNDIRECTED graph)=============*/
// http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
// http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-mst-for-adjacency-list-representation/

// Implementation using matrix representation for simplicity. GREEDY ALGORITHM
//  O(V^2) time for graph matrix implementation
//  O(E+V)*O(LogV) = O(E log V) time for graph adjacency implementation
//  O(V) extra space in both cases

// NOTE: Also, in case of unweighted graphs, any spanning tree is Minimum Spanning Tree and we can
//       use either Depth or Breadth first traversal for finding a spanning tree

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < VRT; v++)
    if (mstSet[v] == false && key[v] < min)
        min = key[v], min_index = v;

    return min_index;
}

void printMST(int parent[], int n, int graph[VRT][VRT]) {
    cout << "\tEdge   Weight\n";
    for (int i = 1; i < VRT; i++)
        cout << "\t" << parent[i] << " - " << i << "    " << graph[i][parent[i]] << endl;
}

void primMST (int graph[VRT][VRT]) {
    int parent[VRT];     // Array to store constructed MST
    int key[VRT];        // Key values to pick minimum weight edge in cut (SHOULD BE A MIN-HEAP)
    bool mstSet[VRT];    // To represent set of vertices not yet included in MST (false==not incl)
                          // (SHOULD BE A SET)

    for (int i = 0; i < VRT; i++) {
        key[i] = INT_MAX, mstSet[i] = false;
    }

    // Always include first 1st vertex in MST.
    key[0]    =  0;  // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1;  // First node is always root of MST

    for (int count = 0; count < VRT-1; count++) {
        int u     = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < VRT; v++) {
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v]) {
                parent[v]  = u, key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, VRT, graph);
}

/* ===============DIJKSTRA ALGORITHM (Shortest Path Among a Node and All Others)==================*/
// http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
// http://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-\
//        representation/

// O(V^2) if matrix representation. If graph represented using adjacency list,  O(E log V) using
// binary heap. O(V) space

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < VRT; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
void printDIJKSTRA(int dist[], int n) {
    cout << "\tVertex   Distance from Source" << endl;
    for (int i = 0; i < VRT; i++)
        cout << "\t" << i << "\t\t " << dist[i] << endl;
}

void dijkstraSP(int graph[VRT][VRT], int src) {
    int dist[VRT];  // Output array.  dist[i] holds the shortest distance from src to i.
                    // Incrementally updated

    bool sptSet[VRT]; // sptSet[i] will true if vertex i is included in shortest
                      // path tree or shortest distance from src to i is finalized

    for (int i = 0; i < VRT; i++) {
        dist[i] = INT_MAX, sptSet[i] = false;
    }

    dist[src] = 0; // So that it is first picked

    // Find current shortest path for all vertices
    for (int count = 0; count < VRT-1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u     = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v= 0; v<VRT; v++) { //Update dist value of the adjacent vertices of u

            // Update dist[v] only if isn't in sptSet and total weight of path from src to v
            // through u is smaller than current value of dist[v]
            if (!sptSet[v]  && graph[u][v] && dist[u] != INT_MAX &&  dist[u]+graph[u][v] < dist[v] )
                dist[v] = dist[u] + graph[u][v];
        }
    }

    printDIJKSTRA(dist, VRT);
}

/* ================================Sliding Puzzle=================================================*/
// http://www.geeksforgeeks.org/branch-bound-set-3-8-puzzle-problem/  (modification)
// Solved using BFS (minimum path guaranteed). N=9 Search space is N! (O(N!) time, O(N!) space too
//
// Memory and time are limiting, this is why other AI algorithms like A*, or IDA* are often used.
// The idea is to have a cost function that given the current cost to reach a given state and an
// (under)estimation of the  cost to reach the final solution, it prioritizes and first visits those
// states with less cost.
// Here I show a simple BFS implementation, that guarantees the set of minimum movements to reach a
// final state.

class State {
    private:
        string  status;
        short   zeroPos;  // to avoid 0 searches in status
        char    prevMove;
        char    n;

    private:
        int idx (int row, int col)                 { return (col + row * (int) n); }
        void fromIdx (int idx, int& row, int& col) { row = idx / (int) n; col = idx % (int) n; }

        bool canApply (char move) {
            if (move == 'r') { return ((zeroPos % n) != 0);   }
            if (move == 'l') { return ((zeroPos % n) != n-1); }
            if (move == 'u') { return ((zeroPos / n) != n-1);   }
            if (move == 'd') { return ((zeroPos / n) != 0); }
        }

        void apply (char move) {
            if (canApply(move)) { // a bit redundant if condition
                int row, col, movingPos;
                fromIdx(zeroPos, row, col);
                if (move == 'r') movingPos = idx(row, col-1);
                if (move == 'l') movingPos = idx(row, col+1);
                if (move == 'u') movingPos = idx(row+1, col);
                if (move == 'd') movingPos = idx(row-1, col);

                status[zeroPos] = status[movingPos]; status[movingPos] = '0';
                zeroPos  = movingPos; prevMove = move;
            }
        }

    public:
        State (string initial) : status(initial), prevMove('\0') {
            zeroPos  = initial.find("0");
            n        = sqrt(status.size());
        }

        //~State(); //not needed

        void reverse() {
            if      (prevMove == 'l') apply('r');
            else if (prevMove == 'r') apply('l');
            else if (prevMove == 'u') apply('d');
            else if (prevMove == 'd') apply('u');
        }

        list<State> moves() {
            list<State> result;
            if (canApply('u'))  { State up    = *this;  up.apply('u');    result.push_back(up);    }
            if (canApply('d'))  { State down  = *this;  down.apply('d');  result.push_back(down);  }
            if (canApply('r'))  { State right = *this;  right.apply('r'); result.push_back(right); }
            if (canApply('l'))  { State left  = *this;  left.apply('l');  result.push_back(left);  }
            return result;
        }

        char getPrevMove() { return prevMove; }
        string getStatus() { return status; }

        // http://stackoverflow.com/questions/4421706/operator-overloading
        // Needed for set / map
        friend bool operator<  (const State& l, const State& r) { return l.status < r.status; }
        friend bool operator>= (const State& l, const State& r) { return !(l < r); }
        friend bool operator>  (const State& l, const State& r) { return   r < l; }
        friend bool operator<= (const State& l, const State& r) { return !(r < l); }
        friend bool operator== (const State& l, const State& r) { return l.status == r.status; }
        friend bool operator!= (const State& l, const State& r) { return !(l == r); }
        // TODO: Unordered_map and unordered_set need operator==, operator!= and hash operator
};

bool reconstructMoves(State& current, State& initial, set<State>& visited, string& result) {
    if (current == initial) {
        result = "";
        return true;
    }

    string tmp = "";
    State reversed = current;
    reversed.reverse();

    if (visited.find(reversed) != visited.end()) {
        reversed = *visited.find(reversed); // to be able to get original move
        if (reconstructMoves (reversed, initial, visited, tmp)) {
            result = tmp + string(1,current.getPrevMove());
            return true;
        } else {
            result = "";
            return false;
        }
    } else {
        result = "";
        return false;
    }
}

string slidingPuzzle(string start, string end)
{
    list<State> toVisit;
    set<State>  visited;
    State       initialState(start);
    State       finalState(end);


    toVisit.push_back(start);
    visited.insert(start);

    while (!toVisit.empty()) {

        State current = toVisit.front(); toVisit.pop_front();
        if (current == finalState) {
            string result = ""; reconstructMoves(current, initialState, visited, result);
            return result;
        }
        list<State> potentialMoves = current.moves();
        for (auto& s : potentialMoves) {
            if (visited.find(s) == visited.end()) {
                visited.insert(s);
                toVisit.push_back(s);
            }
        }
    }
    return "NO";
}

/* ==============================2 Water-Jug Puzzle=================================================*/
// Solved using BFS (minimum path guaranteed). N & M liters, O(N*M) time(search space), O(N*M) space
// Generalizing to N jugs, this is exponential
// http://pages.cs.wisc.edu/~bsettles/cs540/lectures/03_search.pdf
// http://www.geeksforgeeks.org/two-water-jug-puzzle/
// https://kartikkukreja.wordpress.com/2013/10/11/water-jug-problem/
// http://aass.oru.se/~mbl/AI/lectures.2011/AI-2.pdf

class Jugs {
    private:
        vector<int>   status;
        vector<int>   maxCap;
        pair<int,int> prevMove;  //src, dst  (if dst == -1 then it is floor)
                                 //          (if src == -1 then it is river)

        bool pour (int src, int dst) {
            bool can = false;

            if (src == -1 && status[dst] < maxCap[dst]) { // Fill a jug from river
                status[dst] = maxCap[dst];
                can         = true;
            } else {
                if (dst == -1 && status[src] > 0) {  // Empty a jug to floor
                    status[src] = 0;
                    can         = true;
                } else  if (status[src] > 0 && status[dst] < maxCap[dst]) {
                    // Move water from a jug to another (stop when dst gets full or src empty)
                    // Water cannot be spilled
                    int tmp = status[src];
                    status[src] = max(0, status[src]-(maxCap[dst] - status[dst]) );
                    status[dst] = min(maxCap[dst], status[dst] + tmp );
                    can = true;
                }
            }
            if (can) prevMove = pair<int,int>(src, dst);
            return can;
        }

    public:
        Jugs(vector<int> initialState, vector<int> maxCapacities) : status(initialState) {
            prevMove = pair<int,int>(-1,-1);
            maxCap   = maxCapacities;
            // TODO: check same size and initialStates are consistent wrt maxCapacities
        }

        list<Jugs> moves() {
            list<Jugs> result;
            for (int s = -1; s < (int) status.size(); s++) {
                for ( int d = -1; d < (int) status.size(); d++ ) {
                    if (s != d) {
                        Jugs tmp = *this;
                        if (tmp.pour(s, d)) { result.push_back(tmp); }
                    }
                }
            }
            return result;
        }

        void print () {
            cout << "[ ";
            for (auto&e : status) {
                cout << e << ", ";
            } cout << " ] ";
            cout << "Move: " << prevMove.first << " to " << prevMove.second << endl;
        }

        //void reverse();
        vector<int>   getStatus()   {return status;   }
        pair<int,int> getPrevMove() {return prevMove; }
        bool isFinal (int obj)      {for(auto& e:status) {if (e==obj) return true;} return false;}

        // Needed for set / map  (< ... operators for vector is to check lexicographically contents)
        friend bool operator<  (const Jugs& l, const Jugs& r) { return l.status < r.status; }
        friend bool operator>= (const Jugs& l, const Jugs& r) { return !(l < r); }
        friend bool operator>  (const Jugs& l, const Jugs& r) { return   r < l; }
        friend bool operator<= (const Jugs& l, const Jugs& r) { return !(r < l); }
        friend bool operator== (const Jugs& l, const Jugs& r) { return l.status == r.status; }
        friend bool operator!= (const Jugs& l, const Jugs& r) { return !(l == r); }
        // TODO: Unordered_map and unordered_set need operator==, operator!= and hash operator
};

stack<pair<int,int> > reconstructMovesWater (Jugs& final, Jugs& initial, map<Jugs,Jugs>& visited) {
    Jugs& current = final;
    stack<pair<int,int> > result;

    while (current != initial) {
        result.push(current.getPrevMove());
        if (visited.find(current) != visited.end()) {
            //operator[] needs the default constructor for types, Jugs has particular constructor...
            current = visited.find(current)->second;
        } else {
            pair<int,int> tmp(-2,-2);
            result = stack<pair<int,int> >(); result.push(tmp);
            return result;
        }
    }
    return result;
}

stack<pair<int,int> > waterJugs (vector<int> initial, vector<int> maxCapacities, int finalValue) {
    list<Jugs>      toVisit;
    map<Jugs, Jugs> visited; // map from dst jug status to src jug status

    Jugs initialState(initial, maxCapacities);
    toVisit.push_back(initialState);
    //operator[] needs the default constructor for types, Jugs has particular constructor...
    visited.insert(std::make_pair(initialState,initialState));

    while (!toVisit.empty()) {
        Jugs j = toVisit.front(); toVisit.pop_front();
        if (j.isFinal(finalValue)) {
            return reconstructMovesWater (j, initialState, visited);
        }
        list<Jugs> potentialMoves = j.moves();
        for (auto &a : potentialMoves) {
            if (visited.find(a) == visited.end()) {
                visited.insert(std::make_pair(a,j));
                toVisit.push_back(a);
            }
        }
    }
    pair<int,int> tmp(-2,-2);
    stack<pair<int,int> > result; result.push(tmp);
    return result;
}

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void BFS_example() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    cout << "Breadth First Traversal (starting from vertex 2) is: ";  BFS(g, 2);
    cout << endl;
    cout << "Exhaustive Breadth First Traversal is: "; BFS(g, 0, true);
    cout << endl;
}
void DFS_example() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    cout << "Depth First Traversal (starting from vertex 0) is: "; DFS(g, 0);
    cout << endl;
    cout << "Exhaustive Depth First Traversal is: "; DFS(g, 0, true);
    cout << endl;
}
void TopologicalSort_example() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    cout << "Topological Sort is: "; TopologicalSort(g);
    cout << endl;
}
void isBipartite_example() {
    Graph g(4);
    /*
    int G[4][4] = {{0, 1, 0, 1},
                   {1, 0, 1, 0},
                   {0, 1, 0, 1},
                   {1, 0, 1, 0}
                  };
    */
    g.addEdge(0,1);
    g.addEdge(0,3);
    g.addEdge(1,0);
    g.addEdge(3,0);
    g.addEdge(1,2);
    g.addEdge(2,1);
    g.addEdge(2,3);
    g.addEdge(3,2);
    cout << "Graph is bipartite? is: " << isBipartite(g) << endl;
}
void isPath_example() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 4);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.addEdge(4, 2);

    vector<int> result(g.numVertices(), -1);
    stack<int>  inverse;
    cout << "Is node 3 is reachable from 0 ?: " << isPath(g, 0, 3, result) << " with path : ";

    int i = 3;
    while (result[i] != -1) { inverse.push(i); i = result[i]; }   inverse.push(0);
    for (stack<int> dump = inverse; !dump.empty(); dump.pop()) cout << dump.top() << ", ";
    cout << " (BFS version) "<< endl;

    cout << "Node 1 is reachable from 3 is: " << isPath(g, 3, 1, result) << endl;

    list<int> path;
    bool found= pathAmong(g, 0, 3, path); // Note it does not produce minimum path !
    cout << "Path between 0 and 3 is (DFS-version): ";
    for (auto& e: path) {
        cout << e << ", ";
    }   cout << endl;
}
void isCyclic_example() {
    Graph g(8);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    //g.addEdge(3, 0);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 4);

    vector<bool> incycle(g.numVertices(), false);
    cout << "Graph is cyclic ? : " << isCyclic(g, incycle) << " with vertices : ";
    for (int i = 0; i < g.numVertices(); i++) {
        if (incycle[i]) cout << i << ", ";
    }   cout << endl;
}
void isTree_example() {
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(2, 0);
    g.addEdge(0, 3);
    g.addEdge(3, 0);
    g.addEdge(3, 4);
    g.addEdge(4, 3);
    cout << "Graph is tree is: " << isTree(g) << endl;
}
void numConnectedComponents_example() {
    Graph g(7);
    g.addEdge(1, 0);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(2, 0);
    g.addEdge(0, 3);
    g.addEdge(3, 0);
    g.addEdge(3, 4);
    g.addEdge(4, 3);

    g.addEdge(5, 6);
    g.addEdge(6, 5);

    vector<set<int> > result;
    int num = numConnectedComponents (g, result);
    cout << "Number of connected components is : " << num << endl;
}
void primMST_example() {
    int graph[VRT][VRT] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                           {4, 0, 8, 0, 0, 0, 0, 11, 0},
                           {0, 8, 0, 7, 0, 4, 0, 0, 2},
                           {0, 0, 7, 0, 9, 14, 0, 0, 0},
                           {0, 0, 0, 9, 0, 10, 0, 0, 0},
                           {0, 0, 4, 0, 10, 0, 2, 0, 0},
                           {0, 0, 0, 14, 0, 2, 0, 1, 6},
                           {8, 11, 0, 0, 0, 0, 1, 0, 7},
                           {0, 0, 2, 0, 0, 0, 6, 7, 0}
                          };

    cout << "PRIM MST for graph is: " << endl;
    primMST(graph);
}
void dijkstraSP_example() {
    int graph[VRT][VRT] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                           {4, 0, 8, 0, 0, 0, 0, 11, 0},
                           {0, 8, 0, 7, 0, 4, 0, 0, 2},
                           {0, 0, 7, 0, 9, 14, 0, 0, 0},
                           {0, 0, 0, 9, 0, 10, 0, 0, 0},
                           {0, 0, 4, 0, 10, 0, 2, 0, 0},
                           {0, 0, 0, 14, 0, 2, 0, 1, 6},
                           {8, 11, 0, 0, 0, 0, 1, 0, 7},
                           {0, 0, 2, 0, 0, 0, 6, 7, 0}
                          };

    cout << "DIJKSTRA SHORTEST PATHS from 0 to all nodes have weights: " << endl;
    dijkstraSP(graph, 0);
}
void slidingPuzzle_example() {
    string result = slidingPuzzle("123560784", "123586074");
    cout << "Sliding puzzle moves are: " << result << endl;
}
void waterJugs_example() {
    vector<int> initialCapacities = {0,0};
    vector<int> maxCap = {3, 4};
    stack<pair<int,int> > result = waterJugs (initialCapacities, maxCap, 2);
    cout << "Water Jug problem solution is: ";
    for (stack<pair<int,int> > dump = result; !dump.empty(); dump.pop()) {
        cout << "(" << dump.top().first << " to " << dump.top().second << ") ";
    }
    cout << endl;
}
/* ===============================================================================================*/
int main() {
    BFS_example();
    DFS_example();
    TopologicalSort_example();
    isBipartite_example();
    isPath_example();
    isCyclic_example();
    isTree_example();
    numConnectedComponents_example();
    primMST_example();
    dijkstraSP_example();
    slidingPuzzle_example();
    waterJugs_example();
}

/* =======================================TODO====================================================*/
// GRAPHS: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#GraphAlgorithms
