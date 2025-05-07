#include <iostream>
#include <vector>
using namespace std;

// ---------- Common Utility Function ----------
bool isSafe(int v, vector<vector<int>>& graph, vector<int>& color, int c) {
    for (int i = 0; i < graph.size(); i++)
        if (graph[v][i] && color[i] == c)
            return false;
    return true;
}

// ---------- Backtracking ----------
bool backtrackingColoringUtil(vector<vector<int>>& graph, int m, vector<int>& color, int v, int& nodesExplored) {
    nodesExplored++; // Increment nodes explored whenever we try a color assignment
    
    if (v == graph.size()) return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;
            if (backtrackingColoringUtil(graph, m, color, v + 1, nodesExplored)) return true;
            color[v] = 0; // backtrack
        }
    }
    return false;
}

bool graphColoringBacktracking(vector<vector<int>>& graph, int m) {
    int V = graph.size();
    vector<int> color(V, 0);
    int nodesExplored = 0;

    if (!backtrackingColoringUtil(graph, m, color, 0, nodesExplored)) {
        cout << "No solution exists (Backtracking)." << endl;
        return false;
    }

    cout << "\nColor assignment using Backtracking:" << endl;
    for (int i = 0; i < V; i++)
        cout << "Vertex " << i << " ---> Color " << color[i] << endl;

    cout << "Nodes explored (Backtracking): " << nodesExplored << endl;
    return true;
}

// ---------- Main ----------
int main() {
    int V, m;
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));

    cout << "Enter the adjacency matrix (" << V << " x " << V << "):\n";
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            cin >> graph[i][j];

    cout << "Enter the number of colors: ";
    cin >> m;

    // Run the Backtracking method
    graphColoringBacktracking(graph, m);

    return 0;
}


/*
Enter the number of vertices: 4
Enter the adjacency matrix (4 x 4):
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
Enter the number of colors: 3

Enter the number of vertices: 4
Enter the adjacency matrix (4 x 4):
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0
Enter the number of colors: 3


*/