#pragma once
#ifndef RANDOMGUESSGAMEGUI_H
#define RANDOMGUESSGAMEGUI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class RandomGuessGameGUI {
private:
    sf::RenderWindow window;
    sf::Font font;

    sf::RectangleShape backButton;
    sf::Text backText;

    sf::RectangleShape gridCell;
    std::vector<std::vector<char>> grid;

    sf::Text turnCounterText;
    sf::Text timerText;
    sf::Text feedbackText;

    int gridSize;
    int cellSize;
    int remainingTurns;
    int totalPlanes;
    int foundPlanes;

    sf::Clock gameClock;
    int timeLimit;  // Time limit in seconds

    void drawGrid();
    void drawUI();
    void handleCellClick(sf::Vector2i mousePos);
    void generateRandomPlanes();

public:
    RandomGuessGameGUI();
    void run();
};

#endif // RANDOMGUESSGAMEGUI_H
#pragma once
