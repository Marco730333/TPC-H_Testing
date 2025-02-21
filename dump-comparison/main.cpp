#include <iostream>      // For console output
#include <vector>        // To store phone numbers
#include <random>        // For generating random numbers
#include <string>        // To store phone numbers as strings
#include <chrono>        // To measure execution time
#include <fstream>       // For file output
#include <ctime>    // for time()
#include <cstdlib> // for srand(), rand()
#include <utility>
#include <random> 







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

        // Generate a random 12-digit number
            // Combine two rand() calls into a 62-bit random value
            unsigned long long hi = static_cast<unsigned long long>(rand()) << 31;
            unsigned long long lo = static_cast<unsigned long long>(rand());
            unsigned long long bigRand = hi ^ lo;  // Combine them

        // map random nr into a 12-digit number
        unsigned long long number = 100000000000ULL + (bigRand % 900000000000ULL);

            
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





// -----------------------------------------
// Filter by Prefix
// -----------------------------------------

class PrefixFilter {
    public:
        // Filter binary numbers by prefix 
        static std::pair<double, std::size_t> filterBinary(const std::vector<unsigned long long>& binaryNumbers) {
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now(); // Start timer

    
            std::vector<unsigned long long> filteredNumbers;
            for (std::size_t i = 0; i < binaryNumbers.size(); ++i) {
                unsigned long long number = binaryNumbers[i];
                // Calculating the first 2 digits 
                unsigned long long prefix = number / 10000000000ULL;
    
                // Check if the prefix is in the desired set
                if (prefix == 13 || prefix == 31 || prefix == 23 || 
                    prefix == 29 || prefix == 30 || prefix == 18 || prefix == 17) {
                    filteredNumbers.push_back(number);
                }
            }
    
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now(); // End timer
            std::chrono::duration<double> duration = end - start;
            return std::make_pair(duration.count(), filteredNumbers.size()); // Return time & size
        }
    
        // Filter string numbers by prefix
        static std::pair<double, std::size_t> filterStrings(const std::vector<std::string>& stringNumbers) {
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now(); // Start timer

    
            std::vector<std::string> filteredNumbers;
            for (std::size_t i = 0; i < stringNumbers.size(); ++i) {
                std::string number = stringNumbers[i];
                // Get the prefix (first 2 characters)
                std::string prefix = number.substr(0, 2);
    
                // Check if the prefix is in the desired set
                if (prefix == "13" || prefix == "31" || prefix == "23" || 
                    prefix == "29" || prefix == "30" || prefix == "18" || prefix == "17") {
                    filteredNumbers.push_back(number);
                }
            }
    
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now(); // End timer
    std::chrono::duration<double> duration = end - start;
            return std::make_pair(duration.count(), filteredNumbers.size()); // Return time & size
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

    // Display time it took for dump
    std::cout << "Binary dump took: " << binaryDuration << " seconds.\n";
    std::cout << "String dump took: " << stringDuration << " seconds.\n";


    // Filter by prefix for binary & measure time 
    // auto [binaryFilterDuration, binaryMatches] = PrefixFilter::filterBinary(generator.getBinaryNumbers());
    std::pair<double, std::size_t> binaryResult = PrefixFilter::filterBinary(generator.getBinaryNumbers());
double binaryFilterDuration = binaryResult.first;
std::size_t binaryMatches = binaryResult.second;


    // Filter by prefix for string & measure time 
   // auto [stringFilterDuration, stringsMatches] = PrefixFilter::filterStrings(generator.getStringNumbers());
   std::pair<double, std::size_t> stringResult = PrefixFilter::filterStrings(generator.getStringNumbers());
double stringFilterDuration = stringResult.first;
std::size_t stringsMatches = stringResult.second;

    // Display time and nrs for filtering
    std::cout << "Binary prefix filter took: " << binaryFilterDuration << " seconds and detected: " << binaryMatches << " matches \n";
    std::cout << "String prefix filter took: " << stringFilterDuration << " seconds and detected: " << stringsMatches << " matches \n";

    return 0;
}
