#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <stack>
#include <algorithm>
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

//        bool isReachable(int s, int d);
//        bool isCyclic(int s, vector<bool>& visited, vector<bool>& inProcess);
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
// ordering
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
/* ===============================================================================================*/
int main() {
    BFS_example();
    DFS_example();
    TopologicalSort_example();
}

/* =======================================TODO====================================================*/
// GRAPHS: http://www.geeksforgeeks.org/fundamentals-of-algorithms/#GraphAlgorithms
