#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "Hello, Docker!" << std::endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}

