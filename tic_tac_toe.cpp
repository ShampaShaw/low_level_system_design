#include <iostream>
#include <vector>
#include <limits>  // To handle invalid input clearing

using namespace std;

class TicTacToe {
private:
    vector<vector<char> > board;
    char currentPlayer;

public:
    TicTacToe() : board(3, vector<char>(3, ' ')), currentPlayer('X') {}

    void displayBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) {
                    cout << " | ";
                }
            }
            cout << endl;
            if (i < 2) {
                cout << "--|---|--" << endl;
            }
        }
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    bool isValidMove(int row, int col) {
        return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ';
    }

    void makeMove(int row, int col) {
        if (isValidMove(row, col)) {
            board[row][col] = currentPlayer;
            displayBoard();  // Display board after every valid move
        } else {
            cout << "Invalid move! Try again." << endl;
        }
    }

    bool checkWin() {
        for (int i = 0; i < 3; i++) {
            if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
                (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) {
                return true;
            }
        }

        if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
            (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
            return true;
        }

        return false;
    }

    bool checkDraw() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    void playGame() {
        int row, col;
        displayBoard();  // Show the initial empty board

        while (true) {
            cout << "Player " << currentPlayer << "'s turn. Enter row and column (0, 1, or 2): ";
            cin >> row >> col;

            // Check for valid input
            if (cin.fail()) {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                cout << "Invalid input. Please enter numbers between 0 and 2 for both row and column.\n";
                continue;
            }

            makeMove(row, col);

            if (checkWin()) {
                cout << "Player " << currentPlayer << " wins!" << endl;
                break;
            } else if (checkDraw()) {
                cout << "It's a draw!" << endl;
                break;
            }

            switchPlayer();
        }
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}
