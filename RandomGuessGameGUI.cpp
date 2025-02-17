#include "RandomGuessGameGUI.h"
#include "MainMenu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

RandomGuessGameGUI::RandomGuessGameGUI()
    : window(sf::VideoMode(600, 700), "Random Guess Mode"),
    gridSize(5), cellSize(100), remainingTurns(10), totalPlanes(3), foundPlanes(0), timeLimit(60) {
    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Error: Failed to load font.");
    }

    // Initialize grid
    grid = std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize, '.'));

    // Back button
    backButton.setSize(sf::Vector2f(100, 40));
    backButton.setFillColor(sf::Color::Red);
    backButton.setPosition(20, 20);

    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(backButton.getPosition().x + 20, backButton.getPosition().y + 10);

    // Generate random planes
    generateRandomPlanes();

    // Turn counter
    turnCounterText.setFont(font);
    turnCounterText.setCharacterSize(20);
    turnCounterText.setFillColor(sf::Color::White);
    turnCounterText.setPosition(20, 80);

    // Timer
    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(20, 110);

    // Feedback text
    feedbackText.setFont(font);
    feedbackText.setCharacterSize(20);
    feedbackText.setFillColor(sf::Color::White);
    feedbackText.setPosition(20, 140);
}

void RandomGuessGameGUI::generateRandomPlanes() {
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < totalPlanes; i++) {
        int row, col;
        char orientation;

        do {
            row = rand() % gridSize;
            col = rand() % gridSize;
            orientation = (rand() % 2 == 0) ? 'H' : 'V';
        } while ((orientation == 'H' && col + 2 >= gridSize) ||
            (orientation == 'V' && row + 2 >= gridSize) ||
            grid[row][col] == 'P');

        if (orientation == 'H') {
            for (int j = 0; j < 3; j++) {
                grid[row][col + j] = 'P';  // Place horizontally
            }
        }
        else {
            for (int j = 0; j < 3; j++) {
                grid[row + j][col] = 'P';  // Place vertically
            }
        }
    }
}

void RandomGuessGameGUI::drawGrid() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            sf::RectangleShape cell(sf::Vector2f(static_cast<float>(cellSize - 2), static_cast<float>(cellSize - 2)));
            cell.setPosition(100 + j * cellSize, 200 + i * cellSize);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);

            if (grid[i][j] == 'H') {
                cell.setFillColor(sf::Color::Red);  // Hit
            }
            else if (grid[i][j] == 'M') {
                cell.setFillColor(sf::Color::White);  // Miss
            }
            else {
                cell.setFillColor(sf::Color::Blue);  // Default
            }

            window.draw(cell);
        }
    }
}

void RandomGuessGameGUI::drawUI() {
    // Draw back button
    window.draw(backButton);
    window.draw(backText);

    // Update turn counter
    turnCounterText.setString("Turns Remaining: " + std::to_string(remainingTurns));
    window.draw(turnCounterText);

    // Update timer
    int elapsedTime = static_cast<int>(gameClock.getElapsedTime().asSeconds());
    timerText.setString("Time Remaining: " + std::to_string(timeLimit - elapsedTime) + "s");
    window.draw(timerText);

    // Draw feedback text
    window.draw(feedbackText);
}

void RandomGuessGameGUI::handleCellClick(sf::Vector2i mousePos) {
    int xOffset = 100;
    int yOffset = 200;

    // Check if click is inside the grid
    if (mousePos.x >= xOffset && mousePos.x < xOffset + gridSize * cellSize &&
        mousePos.y >= yOffset && mousePos.y < yOffset + gridSize * cellSize) {
        int col = (mousePos.x - xOffset) / cellSize;
        int row = (mousePos.y - yOffset) / cellSize;

        if (grid[row][col] == 'P') {
            grid[row][col] = 'H';  // Hit
            feedbackText.setString("Hit!");
            foundPlanes++;
        }
        else if (grid[row][col] == '.') {
            grid[row][col] = 'M';  // Miss
            feedbackText.setString("Miss!");
        }

        remainingTurns--;
    }
}

void RandomGuessGameGUI::run() {
    gameClock.restart();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.close();  // Close current mode and return to main menu
                    MainMenu mainMenu;
                    mainMenu.run();
                }
                else {
                    handleCellClick(mousePos);
                }
            }
        }

        // Check game-over conditions
        int elapsedTime = static_cast<int>(gameClock.getElapsedTime().asSeconds());
        if (remainingTurns <= 0 || elapsedTime >= timeLimit) {
            feedbackText.setString(foundPlanes == totalPlanes ? "You Win!" : "Game Over!");
            sf::sleep(sf::seconds(3));
            window.close();
            MainMenu mainMenu;
            mainMenu.run();
        }

        // Draw everything
        window.clear(sf::Color::Black);  // Matrix theme
        drawGrid();
        drawUI();
        window.display();
    }
}
