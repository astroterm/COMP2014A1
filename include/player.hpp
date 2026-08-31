#pragma once

#include <utility>
#include <functional>
#include <string>
#include "random.hpp"

using Move = std::pair<int, int>;

class Player {
public:
    Player(char, std::string);
    virtual ~Player() = default;
    virtual Move move() = 0;

    char token;
    std::string name;
    Random random;
};

class HumanPlayer : public Player {
public:
    HumanPlayer();
    Move move() override;
};

class RandomPlayer : public Player {
public:
    RandomPlayer();
    Move move() override;
};

using PlayerRef = std::reference_wrapper<Player>;