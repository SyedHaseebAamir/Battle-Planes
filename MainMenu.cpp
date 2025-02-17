#include "MainMenu.h"
#include "GameInfoGUI.h"
#include <iostream>

MainMenu::MainMenu() : window(sf::VideoMode(850, 600), "Battle Planes"), selectedOption(0) {
    // Load fonturce\rep
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Failed to load font.\n";
    }

    // Title text
    titleText.setFont(font);
    titleText.setString("Battle Planes");
    titleText.setCharacterSize(86);
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(250, 50);

    // Menu options
    std::vector<std::string> options = { "1. Play (Player vs Bot)", "2. Play (Player vs Player)",
                                        "3. Game Info", "4. Exit" };
    float yOffset = 200;
    for (const auto& option : options) {
        sf::Text menuItem;
        menuItem.setFont(font);
        menuItem.setString(option);
        menuItem.setCharacterSize(30);
        menuItem.setFillColor(sf::Color::Blue);
        menuItem.setPosition(200, yOffset);
        yOffset += 50;
        menuOptions.push_back(menuItem);
    }
}

void MainMenu::drawMenu() {
    // Load background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lenovo/Downloads/aircraft-battlefield-jets-battlefield-3-wallpaper-preview.jpg")) {
        std::cerr << "Error loading background image!" << std::endl;
        return;
    }

    // Create sprite for background
    sf::Sprite background(backgroundTexture);

    // Get window size
    sf::Vector2u windowSize = window.getSize();

    // Scale the background image to fit the window while preserving aspect ratio
    sf::FloatRect bounds = background.getLocalBounds();
    float scaleX = float(windowSize.x) / bounds.width;
    float scaleY = float(windowSize.y) / bounds.height;

    // To maintain the aspect ratio
    float scale = std::max(scaleX, scaleY); // Choose the largest scale factor

    background.setScale(scale, scale);  // Scale the background

    // Clear the window with background color
    window.clear();

    // Draw the background
    window.draw(background);

    // Draw title
    window.draw(titleText);

    // Draw menu options
    for (auto& option : menuOptions) {
        window.draw(option);
    }

    // Display everything
    window.display();
}


void MainMenu::handleMouseClick(sf::Vector2i mousePos) {
    for (size_t i = 0; i < menuOptions.size(); i++) {
        sf::FloatRect bounds = menuOptions[i].getGlobalBounds();
        if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            selectedOption = static_cast<int>(i) + 1;  // Assign selected option
            break;
        }
    }
}

int MainMenu::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                handleMouseClick(mousePos);
            }
        }

        if (selectedOption != 0) {
            window.close();  // Close the main menu window
            return selectedOption;  // Return the selected option
        }

        drawMenu();  // Redraw the menu
    }

    return 0;  // Return 0 if the window is closed without a selection
}