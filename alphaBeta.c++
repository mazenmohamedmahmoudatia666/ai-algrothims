#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int EMPTY = 0;
const int PLAYER_X = 1;
const int PLAYER_O = 2;

// Function to print the game board
void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int cell : row) {
            switch (cell) {
                case EMPTY:
                    cout << "-";
                    break;
                case PLAYER_X:
                    cout << "X";
                    break;
                case PLAYER_O:
                    cout << "O";
                    break;
            }
            cout << " ";
        }
        cout << endl;
    }
}

// Function to check if the game is over
bool isGameOver(const vector<vector<int>>& board) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return true;
        }
    }
    // Check columns
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] != EMPTY && board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
            return true;
        }
    }
    // Check diagonals
    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return true;
    }
    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return true;
    }
    // Check for tie
    for (const auto& row : board) {
        for (int cell : row) {
            if (cell == EMPTY) {
                return false; // Game is not over yet
            }
        }
    }
    return true; // Game is over, no empty cells left
}

// Function to evaluate the game state
int evaluate(const vector<vector<int>>& board) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return (board[i][0] == PLAYER_X) ? 1 : -1; // Player X wins: 1, Player O wins: -1
        }
    }
    // Check columns
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] != EMPTY && board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
            return (board[0][j] == PLAYER_X) ? 1 : -1;
        }
    }
    // Check diagonals
    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return (board[0][0] == PLAYER_X) ? 1 : -1;
    }
    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return (board[0][2] == PLAYER_X) ? 1 : -1;
    }
    return 0; // Tie
}

// Alpha-Beta Pruning function
int alphabeta(vector<vector<int>>& board, int depth, int alpha, int beta, bool isMaximizing) {
    if (isGameOver(board) || depth == 0) {
        return evaluate(board);
    }

    if (isMaximizing) {
        int maxEval = numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    int eval = alphabeta(board, depth - 1, alpha, beta, false);
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    board[i][j] = EMPTY; // Undo the move
                    if (beta <= alpha) {
                        break; // Beta cut-off
                    }
                }
            }
        }
        return maxEval;
    } else {
        int minEval = numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    int eval = alphabeta(board, depth - 1, alpha, beta, true);
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    board[i][j] = EMPTY; // Undo the move
                    if (beta <= alpha) {
                        break; // Alpha cut-off
                    }
                }
            }
        }
        return minEval;
    }
}

// Function to find the best move using Alpha-Beta Pruning
void findBestMove(vector<vector<int>>& board) {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_X;
                int moveVal = alphabeta(board, 5, numeric_limits<int>::min(), numeric_limits<int>::max(), false); // Depth 5 for example
                board[i][j] = EMPTY; // Undo the move
                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestMove = {i, j};
                }
            }
        }
    }

    cout << "Best Move: " << bestMove.first << ", " << bestMove.second << endl;
}


    vector<vector<int>> board = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

    // Example: Player O has made the following moves
    board[0][0] = PLAYER_O;
    board[1][1] = PLAYER_O;

    cout << "Current Board:" << endl;
    printBoard(board);

    findBestMove(board);

    return 0;

