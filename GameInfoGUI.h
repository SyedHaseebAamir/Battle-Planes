#pragma once
#ifndef GAMEINFOGUI_H
#define GAMEINFOGUI_H

#include <SFML/Graphics.hpp>
#include <string>

class GameInfoGUI {
private:
    sf::RenderWindow window;  // SFML window for Game Info
    sf::Font font;            // Font for rendering text
    sf::RectangleShape backButton; // Back button to return to the main menu

    void drawBackButton();
    void displayGameInfo();

public:
    GameInfoGUI();
    void run();  // Function to display the Game Info screen
};

#endif // GAMEINFOGUI_H
