#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <chrono>

using namespace std;
using namespace chrono;

// Function to generate a phone number represented in bits
string generatePhoneNumberInBits() {
    string phoneNumber;

    // Country code (Fixed as 33 in this example)
    int countryCode = 33;
    bitset<8> countryBits(countryCode);
    phoneNumber += countryBits.to_string() + "-";

    // Measure time for generating the first 3-digit segment
    auto startSub = high_resolution_clock::now();
    int part1 = 100 + rand() % 900; // 3-digit segment (e.g., 429)
    auto endSub = high_resolution_clock::now();
    duration<double> durationSub = endSub - startSub;
    cout << "Time for first segment: " << durationSub.count() << " seconds" << endl;

    bitset<10> part1Bits(part1);  // 10 bits are enough for numbers up to 999
    phoneNumber += part1Bits.to_string() + "-";

    // Generate the second and third parts
    int part2 = 100 + rand() % 900; // Another 3-digit segment (e.g., 790)
    int part3 = 1000 + rand() % 9000; // 4-digit segment (e.g., 6131)

    bitset<10> part2Bits(part2);  // 10 bits for the second 3-digit segment
    bitset<14> part3Bits(part3);  // 14 bits for the 4-digit segment

    phoneNumber += part2Bits.to_string() + "-";
    phoneNumber += part3Bits.to_string();

    return phoneNumber;
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator

    ofstream file("phone_numbers.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    // Start measuring total execution time
    auto start = high_resolution_clock::now();

    // Generate 1 million phone numbers
    for (int i = 0; i < 1000000; ++i) {
        file << generatePhoneNumberInBits() << endl;
    }

    file.close();

    // End measuring total execution time
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;

    cout << "1 million phone numbers (in bits) generated in phone_numbers.txt" << endl;
    cout << "Total execution time: " << duration.count() << " seconds" << endl;
    return 0;
}
