#include <iostream>
#include <vector>
#include "primeFactors.h"
std::vector<int> decomposeIntoPrimeFactors(int number) {
    std::vector<int> primeFactors;

    // Check and add the factor of 2
    while (number % 2 == 0) {
        primeFactors.push_back(2);
        number /= 2;
    }

    // Check and add odd factors
    for (int i = 3; i * i <= number; i += 2) {
        while (number % i == 0) {
            primeFactors.push_back(i);
            number /= i;
        }
    }

    // If the remaining number is a prime greater than 2
    if (number > 2) {
        primeFactors.push_back(number);
    }

    return primeFactors;
}

