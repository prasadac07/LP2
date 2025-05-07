#include <iostream>
#include <vector>

using namespace std;

void printBoard(vector<vector<int>> &board) {
    int n = board.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (board[i][j] == 1 ? "Q " : "- ");
        }
        cout << endl;
    }
}

void placeQueen(vector<vector<int>> &board, int row, int &solutionCount,vector<bool> &cols, vector<bool> &diag1, vector<bool> &diag2) {
    
    int n = board.size();

    if (row == n) {
        solutionCount++;
        cout << "Solution " << solutionCount << ":\n";
        printBoard(board);
        cout << endl;
        return;
    }

    for (int col = 0; col < n; col++) {
        
        if (!cols[col] && !diag1[row - col + n - 1] && !diag2[row + col]) {
            board[row][col] = 1;
            cols[col] = true;
            diag1[row - col + n - 1] = true;
            diag2[row + col] = true;

            placeQueen(board, row + 1, solutionCount, cols, diag1, diag2);

            board[row][col] = 0;
            cols[col] = false;
            diag1[row - col + n - 1] = false;
            diag2[row + col] = false;
        }
    }
}

void solve(int n) {
    vector<vector<int> > board(n, vector<int>(n, 0));
    
    vector<bool> cols(n, false);
    vector<bool> diag1(2 * n - 1, false);
    vector<bool> diag2(2 * n - 1, false);
    
    int solutionCount = 0;

   
    placeQueen(board, 0, solutionCount, cols, diag1, diag2);

    if (solutionCount == 0) {
        cout << "No solution exists!" << endl;
    }
}

int main() {
    int n;
    cout << "Total Queens: ";
    cin >> n;
    cout << endl;

    solve(n);

    return 0;
}