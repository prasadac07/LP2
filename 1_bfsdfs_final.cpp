#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V + 1); // 1-based indexing
    }

    void addEdge(int u, int v) {
        if (u < 1 || v < 1 || u > V || v > V) {
            cout << "Invalid edge!\n";
            return;
        }
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected
    }

    void printGraph() {
        cout << "Adjacency List:\n";
        for (int i = 1; i <= V; i++) {
            cout << i << ": ";
            for (int j : adj[i])
                cout << j << " ";
            cout << endl;
        }
    }

    // DFS Recursive
    void dfsRecursiveUtil(int start, vector<bool>& visited) {
        visited[start] = true;
        cout << start << " ";

        for (int neighbor : adj[start]) {
            if (!visited[neighbor]) {
                dfsRecursiveUtil(neighbor, visited);
            }
        }
    }

    void dfsRecursive(int start) {
        if (start < 1 || start > V) {
            cout << "Invalid start node!\n";
            return;
        }
        vector<bool> visited(V + 1, false);
        dfsRecursiveUtil(start, visited);
        cout << endl;
    }

    // DFS Iterative
    void dfsIterative(int start) {
        if (start < 1 || start > V) {
            cout << "Invalid start node!\n";
            return;
        }
        vector<bool> visited(V + 1, false);
        stack<int> st;
        st.push(start);

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!visited[node]) {
                cout << node << " ";
                visited[node] = true;

                // To match recursion order, reverse iteration
                for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
                    if (!visited[*it])
                        st.push(*it);
                }
            }
        }
        cout << endl;
    }

    // BFS Recursive
    void bfsRecursive(queue<int>& q, vector<bool>& visited) {
        if (q.empty()) return;

        int node = q.front(); q.pop();
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }

        bfsRecursive(q, visited);
    }

    void bfsRecursiveStart(int start) {
        if (start < 1 || start > V) {
            cout << "Invalid start node!\n";
            return;
        }
        vector<bool> visited(V + 1, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        bfsRecursive(q, visited);
        cout << endl;
    }

    // BFS Iterative
    void bfsIterative(int start) {
        if (start < 1 || start > V) {
            cout << "Invalid start node!\n";
            return;
        }
        vector<bool> visited(V + 1, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;
    Graph g(V);

    int choice;
    while (true) {
        cout << "\n--- Menu ---\n";
        cout << "1. Add Edge\n";
        cout << "2. Print Graph\n";
        cout << "3. DFS Recursive\n";
        cout << "4. BFS Recursive\n";
        cout << "5. DFS Iterative\n";
        cout << "6. BFS Iterative\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 7) break;

        int u, v, start;
        switch (choice) {
            case 1:
                cout << "Enter edges (u v). Enter -1 to stop:\n";
                while (true) {
                    cin >> u;
                    if (u == -1) break;
                    cin >> v;
                    if (v == -1) break;
                    g.addEdge(u, v);
                }
                break;

            case 2:
                g.printGraph();
                break;

            case 3:
                cout << "Enter start node for DFS Recursive: ";
                cin >> start;
                g.dfsRecursive(start);
                break;

            case 4:
                cout << "Enter start node for BFS Recursive: ";
                cin >> start;
                g.bfsRecursiveStart(start);
                break;

            case 5:
                cout << "Enter start node for DFS Iterative: ";
                cin >> start;
                g.dfsIterative(start);
                break;

            case 6:
                cout << "Enter start node for BFS Iterative: ";
                cin >> start;
                g.bfsIterative(start);
                break;

            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
