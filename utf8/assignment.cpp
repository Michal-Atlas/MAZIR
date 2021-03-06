#include <iostream>

typedef unsigned char byte;

/// Checks if nth bit from the left is a one
bool if_bit_one(byte x, uint8_t position) {
    if (position > 7) throw std::overflow_error("checked bit outside range of byte");
    return x & (0x80 >> position);
}

/// Sets n bits from the left to 0 in an 8 bit byte
byte trim(byte x, byte trim) {
    return ((UINT8_MAX) >> (trim)) & x;
}

typedef uint32_t utf8_point;

int main() {
    byte c;
    utf8_point char_buffer;
    while (std::cin >> std::noskipws >> c) {
        if (!if_bit_one(c, 0)) { /// Checks if the byte is ascii
            std::cout << unsigned(c) << std::endl;
            continue;
        }
        int leading_ones = 0;
        while (if_bit_one(c, leading_ones)) leading_ones++; /// Finds how many 1s before the first 0
        char_buffer = trim(c, leading_ones); /// Length defining byte
        for (; leading_ones > 1; --leading_ones) { //NOTE Tohle fakt nečitelný for loop
            if (std::cin.eof()) throw std::runtime_error("unexpected EOF");
            std::cin >> c;
            if (!(if_bit_one(c, 0) && !if_bit_one(c, 1))) throw std::logic_error("didn't get continuing byte");
            char_buffer = (char_buffer << 6) | trim(c, 0x2);
        }
        std::cout << unsigned(char_buffer) << std::endl;
    }
    return 0;
}
