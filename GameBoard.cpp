#include "GameBoard.h"

// Constructor to initialize the board
GameBoard::GameBoard(int r, int c) : rows(r), cols(c) {
    resetBoard();
}

// Reset the board to an empty state
void GameBoard::resetBoard() {
    board = vector<vector<char>>(rows, vector<char>(cols, '.'));
}

// Place a plane on the grid
bool GameBoard::placePlane(int x, int y, char orientation, int size) {
    if (!isValidPosition(x, y)) return false;

    if (orientation == 'H') { // Horizontal
        if (x + size > cols) return false;
        for (int i = 0; i < size; i++) {
            if (board[y][x + i] != '.') return false; // Overlap
        }
        for (int i = 0; i < size; i++) {
            board[y][x + i] = 'P'; // Place plane
        }
    }
    else if (orientation == 'V') { // Vertical
        if (y + size > rows) return false;
        for (int i = 0; i < size; i++) {
            if (board[y + i][x] != '.') return false; // Overlap
        }
        for (int i = 0; i < size; i++) {
            board[y + i][x] = 'P'; // Place plane
        }
    }
    else {
        return false; // Invalid orientation
    }

    return true;
}

// Check if a cell is a hit
bool GameBoard::isHit(int x, int y) {
    if (!isValidPosition(x, y)) return false;

    if (board[y][x] == 'P') {
        board[y][x] = 'H'; // Mark as hit
        return true;
    }
    else if (board[y][x] == '.') {
        board[y][x] = 'M'; // Mark as miss
    }
    return false;
}

// Display the board
void GameBoard::displayBoard(bool hidePlanes) {
    cout << "  ";
    for (int i = 0; i < cols; i++) {
        cout << i << " ";
    }
    cout << "\n";

    for (int i = 0; i < rows; i++) {
        cout << i << " ";
        for (int j = 0; j < cols; j++) {
            if (hidePlanes && board[i][j] == 'P') {
                cout << ". ";
            }
            else {
                cout << board[i][j] << " ";
            }
        }
        cout << "\n";
    }
}

// Check if all planes are destroyed
bool GameBoard::allPlanesDestroyed() {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == 'P') return false;
        }
    }
    return true;
}

// Check if a position is valid
bool GameBoard::isValidPosition(int x, int y) {
    return (x >= 0 && x < cols && y >= 0 && y < rows);
}
