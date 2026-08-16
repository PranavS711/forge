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
        else if(userInput == "help"){
            std::cout << "Available commands: "<<std::endl;
            std::cout <<"help\n status\n exit\n"<<std::endl;
        }
        else if(userInput == "status"){
            std::cout << "Forge status" << std::endl;
             std::cout << "Jobs: 0" << std::endl;
        }
        else {
            std::cout << "Unknown command: " << userInput << std::endl;
        }
    }

    return 0;
}
