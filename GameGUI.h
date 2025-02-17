#pragma once
#ifndef GAMEGUI_H
#define GAMEGUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>

class GameGUI {
private:
    sf::RenderWindow window;  // Main SFML window
    sf::Font font;            // Font for rendering text
    const int cellSize = 40;  // Grid cell size (slightly larger)
    const int gridSize = 10;  // Grid dimensions (10x10)

    std::vector<std::vector<char>> playerGrid;  // Player's grid
    std::vector<std::vector<char>> botGrid;     // Bot's grid

    bool playerTurn;         // Tracks if it's the player's turn
    bool gameOver;           // Tracks if the game has ended
    int attempts;            // Number of attempts made by the player
    int playerWins;          // Count of player wins
    int botWins;             // Count of bot wins

    sf::RectangleShape exitButton;  // Exit button for GUI

    void drawGrid(const std::vector<std::vector<char>>& grid, int xOffset, int yOffset, bool hidePlanes);
    void handleGridClick(const sf::Vector2i& mousePos);
    void botTurn();
    bool allPlanesDestroyed(const std::vector<std::vector<char>>& grid);
    void placePlayerPlanes();
    void placeBotPlanes();
    void displayGameInfo(const std::string& turnMessage);
    void resetGame();

    void showMessage(const std::string& message);
    void drawScoreBox();
	void drawExitButton();

    void showEndMenu();

public:
    GameGUI();
    void runPlayerVsBotMode();  // Main function for Player vs Bot mode
};

#endif // GAMEGUI_H
