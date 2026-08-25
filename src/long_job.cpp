#include <iostream>
#include <unistd.h>

int main() {
    std::cout << "Long job started..." << std::endl;

    sleep(30); // Keep the process alive for 30 seconds

    std::cout << "Long job finished!" << std::endl;
    return 0;
}