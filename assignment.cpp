#include <iostream>
#include <cstddef>
#include <vector>

typedef unsigned char byte;

//NOTE Exception handling

/// Checks if nth bit from the left is a one
bool if_bit_one(byte x, int position) {
    return x & 0x1 << position;
}
/// Sets n bits from the left to 0 in an 8 bit byte
byte trim(byte x, byte trim) {
    return ((UINT8_MAX) >> (trim)) & x;
}

typedef uint16_t utf8_point;

int main() {
    byte c;
    std::vector<utf8_point> out;
    utf8_point char_buffer = 0;
    while (std::cin >> std::noskipws >> c) {
        if (!if_bit_one(c, 7)) { /// Checks if the byte is ascii
            out.push_back(c);
            continue;
        }
        int leading_ones = 7;
        while (if_bit_one(c, leading_ones)) leading_ones--; /// Finds how many 1s before the first 0
        char_buffer = trim(c, 7 - leading_ones); /// Length defining byte
        for (int i = 7 - leading_ones - 1; i > 0; --i) { //NOTE Tohle fakt nečitelný for loop
            if (std::cin.eof()) { return 1; }
            std::cin >> c;
            char_buffer = (char_buffer << 6) | trim(c, 0x2);
        }
        out.push_back(char_buffer);
        char_buffer = 0;
    }
    for(byte c : out){
        printf("%u\n", c);
    }
}
