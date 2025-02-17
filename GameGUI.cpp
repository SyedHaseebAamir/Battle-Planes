#include "GameGUI.h"
#include <cstdlib>
#include <ctime>

GameGUI::GameGUI() : window(sf::VideoMode(1000, 800), "Battle Planes"), playerTurn(true), gameOver(false), attempts(0), playerWins(0), botWins(0) {
    resetGame();

    // Load the font for rendering text
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Failed to load font.\n";
    }

    // Initialize the Exit button
     // Initialize the Exit button
    exitButton.setSize(sf::Vector2f(120, 50));
    exitButton.setFillColor(sf::Color(0, 128, 0));  // Green
    exitButton.setPosition(850, 20);
}

void GameGUI::drawGrid(const std::vector<std::vector<char>>& grid, int xOffset, int yOffset, bool hidePlanes) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            sf::RectangleShape cell(sf::Vector2f(static_cast<float>(cellSize - 2), static_cast<float>(cellSize - 2)));
            cell.setPosition(static_cast<float>(xOffset + j * cellSize), static_cast<float>(yOffset + i * cellSize));
            cell.setOutlineThickness(2);
            cell.setOutlineColor(sf::Color(0, 255, 0));  // Glowing green border
            cell.setFillColor(sf::Color::Black);  // Default black

            if (grid[i][j] == 'H') {
                cell.setFillColor(sf::Color::Red);  // Hit
            }
            else if (grid[i][j] == 'M') {
                cell.setFillColor(sf::Color(50, 50, 50));  // Miss (dark gray)
            }
            else if (grid[i][j] == 'P' && !hidePlanes) {
                cell.setFillColor(sf::Color(0, 128, 0));  // Plane (visible green)
            }

            window.draw(cell);
        }
    }
}

void GameGUI::handleGridClick(const sf::Vector2i& mousePos) {
    int xOffset = 550;  // Bot grid xOffset
    int yOffset = 100;  // Bot grid yOffset

    // Check if the exit button was clicked
    if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        gameOver = true;  // End the game
        return;
    }

    // Check if the click is within the bot's grid
    if (mousePos.x >= xOffset && mousePos.x < xOffset + gridSize * cellSize &&
        mousePos.y >= yOffset && mousePos.y < yOffset + gridSize * cellSize) {
        int col = (mousePos.x - xOffset) / cellSize;
        int row = (mousePos.y - yOffset) / cellSize;

        if (botGrid[row][col] == 'P') {
            botGrid[row][col] = 'H';  // Mark hit
            showMessage("You hit a bot plane!");
        }
        else if (botGrid[row][col] == '.') {
            botGrid[row][col] = 'M';  // Mark miss
            showMessage("You missed!");
        }

        attempts++;
        playerTurn = false;  // End player's turn
    }
}

void GameGUI::botTurn() {
    int row, col;
    do {
        row = rand() % gridSize;
        col = rand() % gridSize;
    } while (playerGrid[row][col] == 'H' || playerGrid[row][col] == 'M');

    if (playerGrid[row][col] == 'P') {
        playerGrid[row][col] = 'H';  // Bot hit
        showMessage("The bot hit your plane!");
    }
    else {
        playerGrid[row][col] = 'M';  // Bot miss
        showMessage("The bot missed!");
    }

    playerTurn = true;  // Bot's turn ends
}

bool GameGUI::allPlanesDestroyed(const std::vector<std::vector<char>>& grid) {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell == 'P') {
                return false;
            }
        }
    }
    return true;
}

void GameGUI::placePlayerPlanes() {
    std::cout << "Place 3 planes on the grid. Each plane occupies 3 cells.\n";

    for (int i = 0; i < 3; i++) {
        int row, col;
        char orientation;

        do {
            std::cout << "Plane " << i + 1 << " (Enter row, column, and orientation [H/V]): ";
            std::cin >> row >> col >> orientation;

            // Validate placement
        } while (row < 0 || row >= gridSize || col < 0 || col >= gridSize ||
            (orientation == 'H' && col + 2 >= gridSize) ||
            (orientation == 'V' && row + 2 >= gridSize) ||
            playerGrid[row][col] == 'P');

        if (orientation == 'H') {
            for (int j = 0; j < 3; j++) {
                playerGrid[row][col + j] = 'P';  // Place horizontally
            }
        }
        else {
            for (int j = 0; j < 3; j++) {
                playerGrid[row + j][col] = 'P';  // Place vertically
            }
        }
    }
}

void GameGUI::placeBotPlanes() {
    for (int i = 0; i < 3; i++) {
        int row, col;
        char orientation;

        do {
            row = rand() % gridSize;
            col = rand() % gridSize;
            orientation = (rand() % 2 == 0) ? 'H' : 'V';
        } while ((orientation == 'H' && col + 2 >= gridSize) ||
            (orientation == 'V' && row + 2 >= gridSize) ||
            botGrid[row][col] == 'P');

        if (orientation == 'H') {
            for (int j = 0; j < 3; j++) {
                botGrid[row][col + j] = 'P';  // Place horizontally
            }
        }
        else {
            for (int j = 0; j < 3; j++) {
                botGrid[row + j][col] = 'P';  // Place vertically
            }
        }
    }
}

void GameGUI::drawExitButton() {
    window.draw(exitButton);

    sf::Text exitText;
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(20);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(exitButton.getPosition().x + 20, exitButton.getPosition().y + 10);
    window.draw(exitText);
}

void GameGUI::displayGameInfo(const std::string& turnMessage) {
    sf::Text infoText;

    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color(0, 255, 0));

    // Display attempts
    infoText.setString("Attempts: " + std::to_string(attempts));
    infoText.setPosition(50, 10);
    window.draw(infoText);

    // Display whose turn
    infoText.setString(turnMessage);
    infoText.setPosition(400, 10);
    window.draw(infoText);

    // Draw the Exit button
    drawExitButton();
}

void GameGUI::drawScoreBox() {
    sf::RectangleShape scoreBox(sf::Vector2f(300, 50));
    scoreBox.setFillColor(sf::Color(0, 64, 0));  // Dark green
    scoreBox.setOutlineThickness(2);
    scoreBox.setOutlineColor(sf::Color(0, 255, 0));  // Glowing green border
    scoreBox.setPosition(350, 700);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: Player " + std::to_string(playerWins) + " - AI " + std::to_string(botWins));
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color(0, 255, 0));
    scoreText.setPosition(370, 715);

    window.draw(scoreBox);
    window.draw(scoreText);
}

void GameGUI::showMessage(const std::string& message) {
    sf::Text messageText;

    messageText.setFont(font);
    messageText.setString(message);
    messageText.setCharacterSize(25);
    messageText.setFillColor(sf::Color::Black);
    messageText.setPosition(300, 550);

    window.draw(messageText);
    window.display();

    // Pause for a short duration to display the message
    sf::sleep(sf::seconds(1));
}

void GameGUI::resetGame() {
    playerGrid = std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize, '.'));
    botGrid = std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize, '.'));

    placeBotPlanes();

    playerTurn = true;
    gameOver = false;
    attempts = 0;
}

void GameGUI::showEndMenu() {
    showMessage(allPlanesDestroyed(botGrid) ? "You won!" : "You lost!");

    playerWins += allPlanesDestroyed(botGrid);
    botWins += allPlanesDestroyed(playerGrid);

    sf::Text endText;
    endText.setFont(font);
    endText.setCharacterSize(25);
    endText.setFillColor(sf::Color::Black);
    endText.setString("Play again? (Click 'Exit' to return to main menu)");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (exitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.close();
                    return;
                }
                resetGame();
                runPlayerVsBotMode();
            }
        }

        window.clear(sf::Color::White);
        window.draw(endText);
        window.draw(exitButton);
        window.display();
    }
}

void GameGUI::runPlayerVsBotMode() {
    placePlayerPlanes();  // Allow the player to place their planes

    while (window.isOpen() && !gameOver) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && playerTurn) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                handleGridClick(mousePos);
            }
        }

        if (!playerTurn) {
            botTurn();
        }

        if (allPlanesDestroyed(botGrid) || allPlanesDestroyed(playerGrid)) {
            gameOver = true;
            showMessage(allPlanesDestroyed(botGrid) ? "You won!" : "You lost!");
        }

        window.clear(sf::Color::Black);  // Matrix theme background
        displayGameInfo(playerTurn ? "Your Turn" : "Bot's Turn");
        drawGrid(playerGrid, 50, 100, false);  // Player grid
        drawGrid(botGrid, 550, 100, true);      // Bot grid
        drawScoreBox();
        window.display();
    }
}