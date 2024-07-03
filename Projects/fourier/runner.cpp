#include <cstdlib>  // For std::system
#include <cstdlib>  // For std::system
#include <string>
#include <vector>

int main() {
    // Define a vector with the set values
    std::vector<int> values = {50, 1};

    // Call main.cpp with each value in the vector
    for (int value : values) {
        std::string command = "./Projects/fourier/main " + std::to_string(value);
        std::system(command.c_str());
    }

    return 0;
}

