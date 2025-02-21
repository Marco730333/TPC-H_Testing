#include <iostream>
#include <vector>
#include <random>
#include <chrono>

int main() {
    const int numPhoneNumbers = 1000000;

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned long long> countryCodeDist(1, 999);
    std::uniform_int_distribution<unsigned long long> numberDist(1000000000, 9999999999ULL);

    std::vector<unsigned long long> phoneNumbers;
    phoneNumbers.reserve(numPhoneNumbers);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numPhoneNumbers; ++i) {
        unsigned long long countryCode = countryCodeDist(gen);
        unsigned long long number = numberDist(gen);

        // Combine them as binary
        unsigned long long fullNumber = (countryCode * 10000000000ULL) + number;
        phoneNumbers.push_back(fullNumber);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Binary generation took: " << duration.count() << " seconds.\n";

    return 0;
}
