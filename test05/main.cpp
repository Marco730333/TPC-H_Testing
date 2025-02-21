#include <iostream>      // For console output
#include <vector>        // To store phone numbers
#include <random>        // For generating random numbers
#include <string>        // To store phone numbers as strings
#include <chrono>        // To measure execution time
#include <fstream>       // For file output
#include <bitset>        // To convert numbers to binary strings

// -------------------------------------------------
// Class to generate phone numbers in both binary and string formats
// -------------------------------------------------
class PhoneNumberGenerator {
private:
    std::vector<unsigned long long> binaryPhoneNumbers; // Vector to store binary representations
    std::vector<std::string> stringPhoneNumbers;         // Vector to store string representations
    int numPhoneNumbers;                                // Number of phone numbers to generate

public:
    // Constructor to initialize the number of phone numbers to generate
    PhoneNumberGenerator(int count) : numPhoneNumbers(count) {
        // Reserve memory for the vectors for better performance
        binaryPhoneNumbers.reserve(numPhoneNumbers);
        stringPhoneNumbers.reserve(numPhoneNumbers);
    }

    // Function to generate phone numbers and store them in the vectors
    void generateNumbers() {
        // Setup random number generators
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned long long> countryCodeDist(1, 999); // Country code range: 1-999
        std::uniform_int_distribution<unsigned long long> numberDist(1000000000, 9999999999ULL); // 10-digit number

        // Loop to generate the required number of phone numbers
        for (int i = 0; i < numPhoneNumbers; ++i) {
            unsigned long long countryCode = countryCodeDist(gen); // Generate a random country code
            unsigned long long number = numberDist(gen);           // Generate a random 10-digit number

            // Create binary representation by combining country code and number
            unsigned long long binary = (countryCode * 10000000000ULL) + number;
            binaryPhoneNumbers.push_back(binary); // Store in the binary vector

            // Create string representation in the format: XXX-XXX-XXX-XXXX
            std::string asString = std::to_string(countryCode) + "-" +
                                   std::to_string(number / 10000000) + "-" +
                                   std::to_string((number / 10000) % 1000) + "-" +
                                   std::to_string(number % 10000);
            stringPhoneNumbers.push_back(asString); // Store in the string vector
        }
    }

    // Getter to retrieve the vector of binary phone numbers
    const std::vector<unsigned long long>& getBinaryNumbers() const {
        return binaryPhoneNumbers;
    }

    // Getter to retrieve the vector of string phone numbers
    const std::vector<std::string>& getStringNumbers() const {
        return stringPhoneNumbers;
    }
};

// -------------------------------------------------
// Class to handle file output and measure execution time
// -------------------------------------------------
class FileDumper {
public:
    // Function to dump binary as human-readable 0s and 1s and measure the time taken
    static double dumpBinaryAsText(const std::vector<unsigned long long>& binaryNumbers, const std::string& filename) {
        auto start = std::chrono::high_resolution_clock::now(); // Start timer

        // Open a text file for binary output
        std::ofstream binaryTextFile(filename);

        // Convert each number to a binary string and write to the file
        for (size_t i = 0; i < binaryNumbers.size(); ++i) {
            // Convert the number to a binary string of 64 bits
            std::bitset<64> binaryString(binaryNumbers[i]);
            binaryTextFile << binaryString << "\n"; // Write to the file
        }

        binaryTextFile.close(); // Close the file

        auto end = std::chrono::high_resolution_clock::now(); // End timer
        std::chrono::duration<double> duration = end - start; // Calculate duration
        return duration.count(); // Return the time taken in seconds
    }

    // Function to dump string phone numbers to a file and measure the time taken
    static double dumpStrings(const std::vector<std::string>& stringNumbers, const std::string& filename) {
        auto start = std::chrono::high_resolution_clock::now(); // Start timer

        // Open a text file for string output
        std::ofstream stringFile(filename);

        // Write each phone number's string representation to the file
        for (size_t i = 0; i < stringNumbers.size(); ++i) {
            stringFile << stringNumbers[i] << "\n";
        }

        stringFile.close(); // Close the file

        auto end = std::chrono::high_resolution_clock::now(); // End timer
        std::chrono::duration<double> duration = end - start; // Calculate duration
        return duration.count(); // Return the time taken in seconds
    }
};

// -------------------------------------------------
// Main function to control the flow of the program
// -------------------------------------------------
int main() {
    const int numPhoneNumbers = 100000; // Number of phone numbers to generate

    // Create an instance of PhoneNumberGenerator
    PhoneNumberGenerator generator(numPhoneNumbers);

    // Generate the phone numbers
    generator.generateNumbers();

    // Dump the phone numbers in binary format (0s and 1s as text) and measure the time taken
    double binaryDuration = FileDumper::dumpBinaryAsText(generator.getBinaryNumbers(), "phone_numbers_binary.txt");

    // Dump the phone numbers as strings and measure the time taken
    double stringDuration = FileDumper::dumpStrings(generator.getStringNumbers(), "phone_numbers_string.txt");

    // Display the time taken for each file dump
    std::cout << "Binary dump took: " << binaryDuration << " seconds.\n";
    std::cout << "String dump took: " << stringDuration << " seconds.\n";

    // Compare the two durations
    if (binaryDuration < stringDuration) {
        std::cout << "Binary dump was faster by: " << stringDuration - binaryDuration << " seconds.\n";
    } else {
        std::cout << "String dump was faster by: " << binaryDuration - stringDuration << " seconds.\n";
    }

    return 0;
}
