#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Game::Game() : maxPlanes(3) {}

// Play vs Bot Mode
void Game::playVsBot() {
    cout << "\n========== PLAY VS BOT ==========\n";
    playerBoard.resetBoard();
    botBoard.resetBoard();

    cout << "Setting up the game...\n";
    playerPlacePlanes();
    botPlacePlanes();

    cout << "\nAll planes are set. Let the game begin!\n";
    gameLoop();
}

// Player places their planes
void Game::playerPlacePlanes() {
    cout << "\n--- Player Plane Placement ---\n";
    for (int i = 1; i <= maxPlanes; i++) {
        int x, y;
        char orientation;
        cout << "Place plane " << i << " (size 3).\n";
        cout << "Enter row (0-9): ";
        cin >> x;
        cout << "Enter column (0-9): ";
        cin >> y;
        cout << "Enter orientation (H for Horizontal, V for Vertical): ";
        cin >> orientation;

        if (!playerBoard.placePlane(x, y, orientation, 3)) {
            cout << "Invalid placement. Try again.\n";
            i--;
        }
        else {
            cout << "Plane " << i << " placed successfully.\n";
        }
    }
    playerBoard.displayBoard(false);
}

// Bot places planes randomly
void Game::botPlacePlanes() {
    srand(static_cast<unsigned>(time(0)));
    for (int i = 1; i <= maxPlanes; i++) {
        int x = rand() % 10;
        int y = rand() % 10;
        char orientation = (rand() % 2 == 0) ? 'H' : 'V';

        if (!botBoard.placePlane(x, y, orientation, 3)) {
            i--; // Retry placement
        }
    }
    cout << "Bot has placed its planes.\n";
}

// Game loop for player vs bot
void Game::gameLoop() {
    bool playerTurn = true;

    while (true) {
        cout << "\n--- Current Status ---\n";
        cout << "Player's Board:\n";
        playerBoard.displayBoard(false);
        cout << "\nBot's Board (hidden):\n";
        botBoard.displayBoard(true);

        if (playerTurn) {
            cout << "\n--- Player's Turn ---\n";
            int x, y;
            cout << "Enter row (0-9) to attack: ";
            cin >> x;
            cout << "Enter column (0-9): ";
            cin >> y;

            if (botBoard.isHit(x, y)) {
                cout << "You hit a plane!\n";
            }
            else {
                cout << "You missed.\n";
            }
        }
        else {
            cout << "\n--- Bot's Turn ---\n";
            int x = rand() % 10;
            int y = rand() % 10;

            cout << "Bot attacks (" << x << ", " << y << ").\n";
            if (playerBoard.isHit(x, y)) {
                cout << "The bot hit your plane!\n";
            }
            else {
                cout << "The bot missed.\n";
            }
        }

        // Check victory or defeat
        if (botBoard.allPlanesDestroyed()) {
            cout << "\nYou won! All bot planes destroyed.\n";
            break;
        }
        else if (playerBoard.allPlanesDestroyed()) {
            cout << "\nYou lost! All your planes destroyed.\n";
            break;
        }

        playerTurn = !playerTurn;
    }
}

// Display game info
void Game::displayGameInfo() {
    cout << "\n========== GAME INFO ==========\n";
    cout << "Battle Planes is a grid-based strategy game where:\n";
    cout << "1. You can play against an AI bot.\n";
    cout << "2. Planes are placed on a 10x10 grid.\n";
    cout << "3. You win by destroying all opponent planes.\n";
}
