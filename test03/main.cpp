#include <iostream>      // For console output
#include <vector>        // To store phone numbers
#include <random>        // For generating random numbers
#include <string>        // To store phone numbers as strings
#include <chrono>        // To measure execution time
#include <fstream>       // For file output

// Structure to store phone number in both binary and string formats
struct PhoneNumber {
    unsigned long long binary; // Binary representation
    std::string asString;      // String representation

    // Constructor to generate phone number from random country code and number
    PhoneNumber(unsigned long long countryCode, unsigned long long number) {
        // Create binary representation by combining country code and number
        binary = (countryCode * 10000000000ULL) + number;
        
        // Create string representation in the format: XXX-XXX-XXX-XXXX
        asString = std::to_string(countryCode) + "-" +
                   std::to_string(number / 10000000) + "-" +
                   std::to_string((number / 10000) % 1000) + "-" +
                   std::to_string(number % 10000);
    }
};

int main() {
    const int numPhoneNumbers = 1000000; // Number of phone numbers to generate

    // Vector to store all generated phone numbers
    std::vector<PhoneNumber> phoneNumbers;
    phoneNumbers.reserve(numPhoneNumbers); // Reserve memory for better performance

    // Setup random number generators
    std::random_device rd;                 // Random device for seeding
    std::mt19937 gen(rd());                // Mersenne Twister engine for randomness
    std::uniform_int_distribution<unsigned long long> countryCodeDist(1, 999); // Country code range: 1-999
    std::uniform_int_distribution<unsigned long long> numberDist(1000000000, 9999999999ULL); // 10-digit number

    // Generate phone numbers and store them in the vector
    for (int i = 0; i < numPhoneNumbers; ++i) {
        unsigned long long countryCode = countryCodeDist(gen); // Random country code
        unsigned long long number = numberDist(gen);           // Random 10-digit number

        // Add the generated phone number to the vector
        phoneNumbers.emplace_back(countryCode, number);
    }

    // -------------------------------------------------
    // Dump the phone numbers in Binary format
    // -------------------------------------------------
    auto startBinary = std::chrono::high_resolution_clock::now(); // Start timer

    // Open a file in binary mode
    std::ofstream binaryFile("phone_numbers_binary.dat", std::ios::binary);

    // Write each phone number's binary representation to the file
    for (const auto& phoneNumber : phoneNumbers) {
        binaryFile.write(reinterpret_cast<const char*>(&phoneNumber.binary), sizeof(phoneNumber.binary));
    }

    binaryFile.close(); // Close the file
    auto endBinary = std::chrono::high_resolution_clock::now(); // End timer
    std::chrono::duration<double> durationBinary = endBinary - startBinary;

    // Display time taken for the binary dump
    std::cout << "Binary dump took: " << durationBinary.count() << " seconds.\n";

    // -------------------------------------------------
    // Dump the phone numbers as Strings
    // -------------------------------------------------
    auto startString = std::chrono::high_resolution_clock::now(); // Start timer

    // Open a text file for string output
    std::ofstream stringFile("phone_numbers_string.txt");

    // Write each phone number's string representation to the file
    for (const auto& phoneNumber : phoneNumbers) {
        stringFile << phoneNumber.asString << "\n";
    }

    stringFile.close(); // Close the file
    auto endString = std::chrono::high_resolution_clock::now(); // End timer
    std::chrono::duration<double> durationString = endString - startString;

    // Display time taken for the string dump
    std::cout << "String dump took: " << durationString.count() << " seconds.\n";

    return 0;
}
