#include <iostream>      // For console output
#include <vector>        // To store phone numbers
#include <random>        // For generating random numbers
#include <string>        // To store phone numbers as strings
#include <chrono>        // To measure execution time
#include <fstream>       // For file output






// -------------------------------------------
// generate phone numbers in binary & strings
// -------------------------------------------


class PhoneNumberGenerator {
private:
    std::vector<unsigned long long> binaryPhoneNumbers; // Vector to store binary 
    std::vector<std::string> stringPhoneNumbers;         // Vector to store strings
    int numPhoneNumbers;                                // quantity of numbrs

public:
    // Constructor 
    PhoneNumberGenerator(int count) : numPhoneNumbers(count) {
        // Reserve memory for the vectors
        binaryPhoneNumbers.reserve(numPhoneNumbers);
        stringPhoneNumbers.reserve(numPhoneNumbers);
    }

    // Generate NRs and store them in the vectors
    void generateNumbers() {
        // Random Nr. generator based on the current time
        srand(time(0)); 

        // Generate correct nr. of phone numbers
        for (int i = 0; i < numPhoneNumbers; ++i) {
            unsigned long long number = 100000000000ULL + (rand() % 900000000000ULL); // Generate a random 12-digit number
            
            // Store binary numbers
            binaryPhoneNumbers.push_back(number);

            // convert to the string format
            std::string asString = std::to_string(number / 10000000000) + "-" +
                                   std::to_string(number / 10000000) + "-" +
                                   std::to_string((number / 10000) % 1000) + "-" +
                                   std::to_string(number % 10000);
            stringPhoneNumbers.push_back(asString); // Store string numbers
        }
    }

    // Getter for binary
    const std::vector<unsigned long long>& getBinaryNumbers() const {
        return binaryPhoneNumbers;
    }

    // Getter for strings
    const std::vector<std::string>& getStringNumbers() const {
        return stringPhoneNumbers;
    }
};






// -----------------------------------------
// dump vectors & measure time for each
// -----------------------------------------


class FileDumper {
public:
    // dump binary phone numbers
    static double dumpBinary(const std::vector<unsigned long long>& binaryNumbers, const std::string& filename) {
        auto start = std::chrono::high_resolution_clock::now(); // Start timer

        // create binary file
        std::ofstream binaryFile(filename, std::ios::binary);

        // Write phone numbers to file
        for (size_t i = 0; i < binaryNumbers.size(); ++i) {
            binaryFile.write(reinterpret_cast<const char*>(&binaryNumbers[i]), sizeof(binaryNumbers[i]));
        }

        binaryFile.close(); // Close file

        auto end = std::chrono::high_resolution_clock::now(); // End timer
        std::chrono::duration<double> duration = end - start; // Calculate duration
        return duration.count(); // Return time
    }

    // Dump string phone numbers
    static double dumpStrings(const std::vector<std::string>& stringNumbers, const std::string& filename) {
        auto start = std::chrono::high_resolution_clock::now(); // Start timer

        // create string file
        std::ofstream stringFile(filename);

        // Write phone numbers to file
        for (size_t i = 0; i < stringNumbers.size(); ++i) {
            stringFile << stringNumbers[i] << "\n";
        }

        stringFile.close(); // Close file

        auto end = std::chrono::high_resolution_clock::now(); // End timer
        std::chrono::duration<double> duration = end - start; // Calculate duration
        return duration.count(); // Return time 
    }
};





// -------------------------------------------
// Main function 
// -------------------------------------------


int main() {
    const int numPhoneNumbers = 1000000; // Nr. of phone numbers to generate

    // Create an instance of PhoneNumberGenerator
    PhoneNumberGenerator generator(numPhoneNumbers);

    // Generate phone NRs
    generator.generateNumbers();

    // Dump the phone NRs in binary & measure time 
    double binaryDuration = FileDumper::dumpBinary(generator.getBinaryNumbers(), "phone_numbers_binary.txt");

    // Dump the phone NRs as strings & measure time 
    double stringDuration = FileDumper::dumpStrings(generator.getStringNumbers(), "phone_numbers_string.txt");

    // Display time it took
    std::cout << "Binary dump took: " << binaryDuration << " seconds.\n";
    std::cout << "String dump took: " << stringDuration << " seconds.\n";

    return 0;
}
