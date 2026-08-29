#pragma once

#include <utility>

using Move = std::pair<int, int>;

class Player {
public:
    Player();
    Move move(); // returns 0-idexed integers
    char token;
};

using PlayerRef = std::reference_wrapper<Player>;