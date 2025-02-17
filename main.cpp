#include "MainMenu.h"
#include "GameGUI.h"
#include "GameInfoGUI.h"
#include "RandomGuessGameGUI.h"
#include <iostream>

int main() {
    MainMenu menu;
    int choice = menu.run();

    if (choice == 1) {
        GameGUI game;
        game.runPlayerVsBotMode();
        return 0;
    }
    else if (choice == 2) {
        RandomGuessGameGUI randomGame;
        randomGame.run();
    }
    else if (choice == 3) {
        GameInfoGUI gameInfo;
        gameInfo.run();  // Launch Game Info GUI
        
    }
    else if (choice == 4) {
        std::cout << "Exiting the game.\n";
    }

    return 0;
}
