#include <iostream>
#include <queue>
#include <climits>
#include <vector>
using namespace std;

#define N 3
int drow[] = {0, 1, 0, -1};
int dcol[] = {1, 0, -1, 0};

struct Node {
    Node *parent;
    int mat[N][N];
    int g, h;
    int x, y;
};

// Create a new node with a swapped blank tile
Node *newnode(int mat[N][N], int g, int x, int y, int nx, int ny, Node *parent) {
    Node *node = new Node;
    node->parent = parent;

    // Copy matrix
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            node->mat[i][j] = mat[i][j];

    // Swap blank (0) with target position
    swap(node->mat[x][y], node->mat[nx][ny]);

    node->g = g;
    node->h = INT_MAX;
    node->x = nx;
    node->y = ny;

    return node;
}

// Heuristic: Hamming distance (number of misplaced tiles)
int heuristic(int start[N][N], int goal[N][N]) {
    int cnt = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (start[i][j] != 0 && start[i][j] != goal[i][j])
                cnt++;
    return cnt;
}

void printMatrix(Node *node) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << node->mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "g=" << node->g << " h=" << node->h << " f=" << node->g + node->h << endl << endl;
}

void print(Node *root) {
    if (root == NULL)
        return;
    print(root->parent);
    printMatrix(root);
}

bool isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Comparator for priority_queue (min-heap based on f = g + h)
struct comp {
    bool operator()(const Node *lhs, const Node *rhs) const {
        return (lhs->g + lhs->h) > (rhs->g + rhs->h);
    }
};

void solve(int start[N][N], int goal[N][N], int x, int y) {
    Node *root = newnode(start, 0, x, y, x, y, NULL);
    root->h = heuristic(root->mat, goal);

    priority_queue<Node *, vector<Node *>, comp> pq;
    pq.push(root);

    while (!pq.empty()) {
        Node *m = pq.top();
        pq.pop();

        // Goal state reached
        if (m->h == 0) {
            print(m);
            return;
        }

        int dx = m->x;
        int dy = m->y;

        for (int i = 0; i < 4; i++) {
            int dr = dx + drow[i];
            int dc = dy + dcol[i];

            if (isSafe(dr, dc)) {
                Node *node = newnode(m->mat, m->g + 1, m->x, m->y, dr, dc, m);
                node->h = heuristic(node->mat, goal);
                pq.push(node);
            }
        }
    }
}

int main() {
    int start[N][N], goal[N][N];
    int x = -1, y = -1;

    cout << "Enter start matrix (use 0 for blank tile):" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            cin >> start[i][j];
            if (start[i][j] == 0) {
                x = i;
                y = j;
            }
        }

    cout << "Enter goal matrix:" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> goal[i][j];

    solve(start, goal, x, y);
    return 0;
}
