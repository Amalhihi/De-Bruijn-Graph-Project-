#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> extractDecimalNumbers(const std::string& filePath) {
    std::ifstream inputFile(filePath);
    std::vector<int> decimalNumbers;

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return decimalNumbers; // Return an empty vector in case of an error.
    }

    std::string line;

    while (std::getline(inputFile, line)) {
        size_t pos = line.find("Decimal:");
        if (pos != std::string::npos) {
            int decimalValue;
            if (sscanf(line.c_str() + pos + 8, "%d", &decimalValue) == 1) {
                decimalNumbers.push_back(decimalValue);
            }
        }
    }

    inputFile.close();
    return decimalNumbers;
}


