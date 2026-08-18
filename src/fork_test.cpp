#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    std::cout << "Before fork()" << std::endl;

    pid_t pid = fork();

    if (pid == 0) {
        std::cout << "I am the child. About to run hello!" << std::endl;

        execl("./hello", "hello", nullptr);

        std::cout << "exec failed!" << std::endl;
    }
    else {
        std::cout << "I am the parent. Waiting for child..." << std::endl;

        waitpid(pid, nullptr, 0);

        std::cout << "Child finished!" << std::endl;
    }

    return 0;
}