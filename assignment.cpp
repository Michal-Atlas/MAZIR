#include <iostream>
#include <cstddef>

typedef unsigned char byte;

bool if_bit_one(byte x, int position) {
    return x & 0x1 << position;
}

byte trim(byte x, byte trim) {
    return ((UINT8_MAX) >> (trim)) & x;
}

int main() {
    byte c;
    unsigned long long out_stream = 0;
    while (!std::cin.eof() && (std::cin >> c)) {
        if (if_bit_one(c, 7)) {
            int limit = 7;
            while (if_bit_one(c, limit)) limit--;
            for (int i = 7 - limit; i > 0; --i) {

                if (std::cin.eof()) { return 1; }
                if (i == 7 - limit) {
                    out_stream = trim(c, 7 - limit);
                } else {
                    std::cin >> c;
                    out_stream = (out_stream << 0x6) | trim(c, 0x2);
                }
            }
        } else {
            out_stream = c;
        }
        printf("0x%X\n", out_stream);
    }
}