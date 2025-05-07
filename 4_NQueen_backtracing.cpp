#include <iostream>
#include <vector>

using namespace std;

void printBoard(vector<vector<int>> &board)
{
    int n = board.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << (board[i][j] == 1 ? "Q " : "- ");
        }
        cout << endl;
    }
}

bool isSafe(vector<vector<int>> &board, int row, int col)
{
    int n = board.size();

    // Check column
    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 1)
            return false;
    }

    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
            return false;
    }

    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; i--, j++)
    {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

void placeQueen(vector<vector<int>> &board, int row, int &solutionCount)
{

    int n = board.size();

    // All Queens placed - solution found
    if (row == n)
    {
        solutionCount++;
        cout << "Solution " << solutionCount << ":\n";
        printBoard(board);
        cout << endl;
        return;
    }


    for (int col = 0; col < n; col++)
    {
        // If Cell is safe to place
        if (isSafe(board, row, col))
        {
            // Place Queen
            board[row][col] = 1;

            // Place next queens
            placeQueen(board, row + 1, solutionCount);

            // Backtracking - if no safe place found for a queen - remove current queen
            board[row][col] = 0; 
        }
    }
}



int main()
{

    int n;
    cout << "Total Queens: ";
    cin >> n;

    cout << endl;

    // Initialize board
    vector<vector<int>> board(n, vector<int>(n, 0));

    // Possible no. of solutions
    int solutionCount = 0;
//row=0 because of q1 is placed there first 
    placeQueen(board, 0, solutionCount);

    // If no solution exist
    if (solutionCount == 0)
    {
        cout << "No solution exists!" << endl;
    }
    
    return 0;
}