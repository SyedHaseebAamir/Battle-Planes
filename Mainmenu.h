#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MainMenu {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text titleText;
    std::vector<sf::Text> menuOptions;
    int selectedOption;

    void drawMenu();
    void handleMouseClick(sf::Vector2i mousePos);

public:
    MainMenu();
    int run();  // Run the main menu and return the selected option
};

#endif // MAINMENU_H
