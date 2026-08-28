#pragma once

#include <array>
#include <bitset>

inline constexpr int BOARDSIZE = 3;

inline constexpr std::array<std::bitset<9>, 8> WIN_PATTERNS = {
    std::bitset<9>(0b111000000),
    std::bitset<9>(0b000111000),
    std::bitset<9>(0b000000111),
    std::bitset<9>(0b100100100),
    std::bitset<9>(0b010010010),
    std::bitset<9>(0b001001001),
    std::bitset<9>(0b100010001),
    std::bitset<9>(0b001010100),
};