#include <iostream>
#include <cstddef>

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

int main() {
    byte c;
    unsigned long long out_stream = 0; //NOTE Na datový typ této proměnné ses vybodl, že? :) //NOTE Zavádějící název proměnné
    while (!std::cin.eof() && (std::cin >> c)) { //NOTE No jo, není to C++ krásné? :D
        if (if_bit_one(c, 7)) { /// Checks if the byte is ascii or UTF
            int limit = 7; //NOTE Nic neříkající název proměnné
            while (if_bit_one(c, limit)) limit--; /// Finds how many 1s before the first 0
            for (int i = 7 - limit; i > 0; --i) { //NOTE Tohle fakt nečitelný for loop
                if (std::cin.eof()) { return 1; }
                if (i == 7 - limit) { /// Length defining byte //NOTE Lepší mít místo special case na první průchod cyklu tohle mimo cyklus? :)
                    out_stream = trim(c, 7 - limit);
                } else { /// Continuing byte
                    std::cin >> c;
                    out_stream = (out_stream << 0x6) | trim(c, 0x2); //NOTE To 0x6 je zavádějící mít hexadecimálně. Tím, že je to hexadecimálně dáváš většinou najevo, že je důležitý binární/hexadecimální zápis spíš než samotná hodnota
                }
            }
        } else { //NOTE Obecně je vhodná snaha mít co nejmíň vnořený kód. Zvyšuje to čitelnost. Použil bych continue
            out_stream = c;
        }
        printf("%u\n", out_stream);
    }
}
