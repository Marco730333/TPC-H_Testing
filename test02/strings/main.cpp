#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <chrono>
#include <sstream>

int main() {
    const int numPhoneNumbers = 1000000;

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> countryCodeDist(1, 99);
    std::uniform_int_distribution<int> partDist(100, 999);
    std::uniform_int_distribution<int> lastPartDist(1000, 9999);

    std::vector<std::string> phoneNumbers;
    phoneNumbers.reserve(numPhoneNumbers);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numPhoneNumbers; ++i) {
        int countryCode = countryCodeDist(gen);
        int part1 = partDist(gen);
        int part2 = partDist(gen);
        int lastPart = lastPartDist(gen);

        std::ostringstream oss;
        oss << countryCode << "-" << part1 << "-" << part2 << "-" << lastPart;
        phoneNumbers.push_back(oss.str());
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "String generation took: " << duration.count() << " seconds.\n";

    return 0;
}
