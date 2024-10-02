#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>

bool isOdd(int num) {
    return num % 2 != 0;
}

void generateBinaryPolynomials(int degree, std::vector<int>& polyArray) {
    int numPolynomials = pow(2, degree - 1); // We exclude the 0 coefficient case

    for (int i = 0; i < numPolynomials; i++) {
        int numCoefficients = degree + 1;
        int coefficients[numCoefficients];

        int num = i;
        for (int j = 0; j < numCoefficients; j++) {
            if (j == 0 || j == degree) {
                coefficients[j] = 1;
            } else {
                coefficients[j] = num % 2;
                num /= 2;
            }
        }

        int polynomialValue = 0;
        for (int j = 0; j < numCoefficients; j++) {
            polynomialValue += (coefficients[j] << (degree - j));
        }

        std::bitset<13> binaryValue(polynomialValue);
        if (binaryValue.count() % 2 == 1 && polynomialValue % 2 != 0) {
            polyArray.push_back(polynomialValue);
        }
    }
}


