#pragma once
#ifndef GAME_H
#define GAME_H

#include "GameBoard.h"

class Game {
private:
    GameBoard playerBoard;  // Player's board
    GameBoard botBoard;     // Bot's board
    int maxPlanes;          // Number of planes

    void playerPlacePlanes();
    void botPlacePlanes();
    void gameLoop();

public:
    Game();
    void playVsBot();       // Play vs Bot mode
    void displayGameInfo(); // Display game information
};

#endif // GAME_H
