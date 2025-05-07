#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Edge {
public:
    int u, v, weight;
    Edge() {}
    Edge(int a, int b, int w) {
        u = a;
        v = b;
        weight = w;
    }
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

void kruskal(int V, vector<Edge>& edges) {
    vector<int> component(V);
    for (int i = 0; i < V; i++)
        component[i] = i;

    sort(edges.begin(), edges.end(), compare);

    int cost = 0;
    cout << "Edges in the MST:\n";

    for (Edge e : edges) {
        if (component[e.u] != component[e.v]) {
            // Adding 1 to convert 0-based index back to 1-based for display
            cout << e.u + 1 << " - " << e.v + 1 << " \t" << e.weight << endl;
            cost += e.weight;

            int oldComp = component[e.v];
            int newComp = component[e.u];

            for (int i = 0; i < V; i++) {
                if (component[i] == oldComp)
                    component[i] = newComp;
            }
        }
    }

    cout << "Total Cost = " << cost << endl;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges;

    cout << "Enter edges (u v weight):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(Edge(u - 1, v - 1, w)); // Subtract 1 for 0-based indexing
    }

    kruskal(V, edges);

    return 0;
}
