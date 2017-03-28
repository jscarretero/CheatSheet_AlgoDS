#include <iostream>
#include <vector>
#include <set>
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
}

/* =======================================TODO====================================================*/
// GRAPHS: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#GraphAlgorithms
