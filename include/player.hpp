#pragma once

#include <utility>
#include <functional>
#include <string>

using Move = std::pair<int, int>;

class Player {
public:
    Player();
    Move move();
    char token;
    std::string name;
};

using PlayerRef = std::reference_wrapper<Player>;