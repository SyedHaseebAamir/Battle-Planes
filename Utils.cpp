#include "Utils.h"
#include <iostream>

namespace Utils {
    int getValidatedInput(int min, int max) {
        int input;
        while (true) {
            std::cin >> input;
            if (std::cin.fail() || input < min || input > max) {
                std::cin.clear(); // Clear error flags
                std::cin.ignore(1000, '\n'); // Ignore invalid input
                std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
            }
            else {
                return input;
            }
        }
    }
}
