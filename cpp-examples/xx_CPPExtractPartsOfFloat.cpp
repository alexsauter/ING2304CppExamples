#include <iostream>
#include <bitset>
#include <bit> // Required for std::bit_cast

int main() {
    float num = -9.25f; // Example float

    // Step 1: Bitwise-reinterpret the float as a 32-bit unsigned integer
    uint32_t bits = std::bit_cast<uint32_t>(num);

    // Step 2: Apply bitmasks and shifts
    uint32_t sign = (bits >> 31) & 0x1;
    uint32_t raw_exponent = (bits >> 23) & 0xFF;
    uint32_t mantissa = bits & 0x7FFFFF;

    // Step 3: Calculate the true biased exponent
    int true_exponent = static_cast<int>(raw_exponent) - 127;

    // Output results
    std::cout << "Float: " << num << "\n";
    std::cout << "Sign bit: " << sign << " (" << (sign ? "Negative" : "Positive") << ")\n";
    std::cout << "Raw Exponent (Biased): " << raw_exponent << " (Binary: " << std::bitset<8>(raw_exponent) << ")\n";
    std::cout << "True Exponent (Unbiased): " << true_exponent << "\n";
    std::cout << "Mantissa (Bits): " << mantissa << " (Binary: " << std::bitset<23>(mantissa) << ")\n";

    return 0;
}
