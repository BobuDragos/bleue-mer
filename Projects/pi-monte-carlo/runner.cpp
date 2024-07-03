#include <iostream>
#include <cstdlib>
#include <vector>

int main() {
    std::vector<int> points_values = {100, 1000, 10000, 100000, 1000000};

    for (int points : points_values) {
        std::string command = "./Projects/pi-monte-carlo/main " + std::to_string(points);
        std::cout << "Running command: " << command << std::endl;
        int result = system(command.c_str());
        if (result != 0) {
            std::cerr << "Command failed with exit code " << result << std::endl;
        }
    }

    return 0;
}

