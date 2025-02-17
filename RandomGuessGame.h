#pragma once
#ifndef RANDOMGUESSGAME_H
#define RANDOMGUESSGAME_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

class RandomGuessGame {
private:
    std::vector<std::vector<char>> board;   // 2D grid for the game board
    int rows, cols;                         // Board dimensions
    int remainingPlanes;                    // Number of planes to find
    int maxGuesses;                         // Maximum number of guesses allowed

    void generateRandomBoard();
    bool isValidGuess(int x, int y) const;

public:
    RandomGuessGame(int r = 10, int c = 10, int planes = 3, int guesses = 20);

    void startGame();  // Start the random guessing game
};

#endif // RANDOMGUESSGAME_H
