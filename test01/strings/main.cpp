#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

// Function to generate a phone number in the format: 33-429-790-6131
string generatePhoneNumber() {
    string phoneNumber;

    // Country code (Fixed as 33 in this example)
    phoneNumber += "33-";

    // Measure time for generating the first 3-digit segment
    auto startSub = high_resolution_clock::now();
    string part1 = to_string(100 + rand() % 900); // 3-digit segment (e.g., 429)
    auto endSub = high_resolution_clock::now();
    duration<double> durationSub = endSub - startSub;
    cout << "Time for first substring: " << durationSub.count() << " seconds" << endl;
    phoneNumber += part1 + "-";

    // Generate and add the second and third parts
    phoneNumber += to_string(100 + rand() % 900) + "-"; // 3-digit segment (e.g., 790)
    phoneNumber += to_string(1000 + rand() % 9000);     // 4-digit segment (e.g., 6131)

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
        file << generatePhoneNumber() << endl;
    }

    file.close();

    // End measuring total execution time
    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;

    cout << "1 million phone numbers generated in phone_numbers.txt" << endl;
    cout << "Total execution time: " << duration.count() << " seconds" << endl;
    return 0;
}
