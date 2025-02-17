#include "RandomGuessGame.h"
#include <iostream>
#include <ctime>

RandomGuessGame::RandomGuessGame(int r, int c, int planes, int guesses)
    : rows(r), cols(c), remainingPlanes(planes), maxGuesses(guesses) {
    board = std::vector<std::vector<char>>(rows, std::vector<char>(cols, '.'));
}

void RandomGuessGame::generateRandomBoard() {
    srand(static_cast<unsigned>(time(0)));

    int placedPlanes = 0;
    while (placedPlanes < remainingPlanes) {
        int x = rand() % rows;
        int y = rand() % cols;

        if (board[x][y] == '.') {  // Place a plane only on empty cells
            board[x][y] = 'P';  // 'P' represents a plane
            placedPlanes++;
        }
    }
}

bool RandomGuessGame::isValidGuess(int x, int y) const {
    return (x >= 0 && x < rows && y >= 0 && y < cols && board[x][y] != 'H' && board[x][y] != 'M');
}

void RandomGuessGame::startGame() {
    generateRandomBoard();
    int guesses = 0;

    std::cout << "\n========== RANDOM BOARD GUESSING MODE ==========\n";
    std::cout << "You need to find " << remainingPlanes << " planes on the board.\n";
    std::cout << "You have " << maxGuesses << " guesses. Good luck!\n";

    while (guesses < maxGuesses && remainingPlanes > 0) {
        int x, y;
        std::cout << "\nEnter your guess (row and column): ";
        std::cin >> x >> y;

        if (!isValidGuess(x, y)) {
            std::cout << "Invalid guess. Try again.\n";
            continue;
        }

        guesses++;
        if (board[x][y] == 'P') {
            std::cout << "Hit! You found a plane!\n";
            board[x][y] = 'H';  // Mark as hit
            remainingPlanes--;
        }
        else {
            std::cout << "Miss! No plane at this position.\n";
            board[x][y] = 'M';  // Mark as miss
        }

        // Display the current board state
        std::cout << "\nCurrent Board State:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == 'P') {
                    std::cout << ". ";  // Hide planes
                }
                else {
                    std::cout << board[i][j] << " ";
                }
            }
            std::cout << "\n";
        }
    }

    if (remainingPlanes == 0) {
        std::cout << "\nCongratulations! You found all the planes!\n";
    }
    else {
        std::cout << "\nGame Over! You ran out of guesses.\n";
    }
}
