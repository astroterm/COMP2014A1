#pragma once

#include <utility>

class Player {
public:
    char token;
    std::pair<int, int> move(); // returns 0-idexed integers
};