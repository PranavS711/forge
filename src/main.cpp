#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    std::cout << "Forge starting..." << std::endl;

    std::string command;
    std::string program;

    while (true) {
        std::cout << "forge> ";
        std::cin >> command;

        if (command == "exit") {
            std::cout << "Shutting down Forge" << std::endl;
            break;
        }
        else if(command == "help"){
            std::cout << "Available commands: "<<std::endl;
            std::cout <<" help\n status\n exit\n"<<std::endl;
        }
        else if(command == "status"){
            std::cout << "Forge status" << std::endl;
             std::cout << "Jobs: 0" << std::endl;
        }
        else if(command == "run"){
            std::cin >> program;
            pid_t pid = fork();

            if (pid == 0) {
                    execl(program.c_str(), program.c_str(), nullptr);

                std::cout << "Failed to run program." << std::endl;
            }
            else {
                    waitpid(pid, nullptr, 0);
            }
        }
        else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }

    return 0;
}
