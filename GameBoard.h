#pragma once
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <iostream>

using namespace std;

class GameBoard {
private:
    vector<vector<char>> board;
    int rows, cols;

public:
    GameBoard(int r = 10, int c = 10);
    void resetBoard();
    bool placePlane(int x, int y, char orientation, int size);
    bool isHit(int x, int y);
    void displayBoard(bool hidePlanes = true);
    bool allPlanesDestroyed();
    bool isValidPosition(int x, int y);
};

#endif // GAMEBOARD_H
