#pragma once

#include <utility>

class Player {
public:
    Player();
    std::pair<int, int> move(); // returns 0-idexed integers
    char token;
};