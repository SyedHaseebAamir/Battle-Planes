#include "GameInfoGUI.h"
#include <iostream>

GameInfoGUI::GameInfoGUI() : window(sf::VideoMode(900, 600), "Game Info") {
    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Error: Failed to load font. Ensure 'arial.ttf' exists in the assets directory.");
    }

    // Initialize the Back button
    backButton.setSize(sf::Vector2f(100, 40));
    backButton.setFillColor(sf::Color(0, 128, 0));  // Green
    backButton.setPosition(20, 20);
}

void GameInfoGUI::drawBackButton() {
    window.draw(backButton);

    sf::Text backText;
    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(backButton.getPosition().x + 20, backButton.getPosition().y + 10);
    window.draw(backText);
}

void GameInfoGUI::displayGameInfo() {
    // Centered Game Info Text
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color(0, 255, 0));  // Glowing green

    std::string info = "Battle Planes is a turn-based strategy game.\n\n"
        "Rules:\n"
        "1. Each player places 3 planes on a 10x10 grid.\n"
        "2. Planes occupy 3 consecutive cells (horizontal/vertical).\n"
        "3. Players take turns attacking the opponent's grid.\n"
        "4. First to destroy all enemy planes wins!\n\n"
        "Features:\n"
        "- Player vs Bot mode\n"
        "- Random Guess mode\n"
        "- Matrix-themed futuristic GUI";

    infoText.setString(info);
    infoText.setPosition(50, 100);  // Center-aligned
    infoText.setLineSpacing(1.5f);  // Add spacing between lines
    window.draw(infoText);
}

void GameInfoGUI::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.close();  // Close Game Info and return to Main Menu
                }
            }
        }

        window.clear(sf::Color::Black);  // Matrix theme background
        drawBackButton();
        displayGameInfo();
        window.display();
    }
}
