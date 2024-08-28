#include <iostream>
#include <vector>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

using namespace std;

class SnakeLadder {
private:
    vector<int> board;
    int player1Position, player2Position;
    int currentPlayer;

public:
    SnakeLadder() : board(101, 0), player1Position(0), player2Position(0), currentPlayer(1) {
        // Snakes
        board[16] = 6;
        board[47] = 26;
        board[49] = 11;
        board[56] = 53;
        board[62] = 19;
        board[64] = 60;
        board[87] = 24;
        board[93] = 73;
        board[95] = 75;
        board[98] = 78;

        // Ladders
        board[1] = 38;
        board[4] = 14;
        board[9] = 31;
        board[21] = 42;
        board[28] = 84;
        board[36] = 44;
        board[51] = 67;
        board[71] = 91;
        board[80] = 96;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    bool isValidMove(int position, int dice) {
        return position + dice <= 100;
    }

    bool checkWin(int position) {
        return position == 100;
    }

    void makeMove(int dice) {
        int& position = (currentPlayer == 1) ? player1Position : player2Position;

        cout << "Player " << currentPlayer << " rolled a " << dice << endl;

        if (isValidMove(position, dice)) {
            position += dice;

            // Check for snakes or ladders
            if (board[position] != 0) {
                position = board[position];
            }

            cout << "Player " << currentPlayer << " is now at " << position << endl;

            if (checkWin(position)) {
                cout << "Player " << currentPlayer << " wins!" << endl;
                exit(0); // Exit the game if a player wins
            }
        } else {
            cout << "Player " << currentPlayer << " cannot move." << endl;
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    SnakeLadder game;

    while (true) {
        int dice = rand() % 6 + 1;
        game.makeMove(dice);
        game.switchPlayer();
    }

    return 0;
}
