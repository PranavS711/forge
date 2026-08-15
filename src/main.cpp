#include <iostream>
#include <string>

int main() {
    std::cout << "Forge starting..." << std::endl;

    std::string userInput;

    while (true) {
        std::cout << "forge> ";
        std::cin >> userInput;

        if (userInput == "exit") {
            std::cout << "Shutting down Forge" << std::endl;
            break;
        }
        else {
            std::cout << "You entered: " << userInput << std::endl;
        }
    }

    return 0;
}
