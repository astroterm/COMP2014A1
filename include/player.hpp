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
    char token() const { return token_; };
    const std::string& name() const { return name_; }


private:
    char token_;
    std::string name_;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(char, std::string);
    Move move() override;
};

class RandomPlayer : public Player {
public:
    RandomPlayer(char, std::string);
    Move move() override;
private:
    Random random;
};

using PlayerRef = std::reference_wrapper<Player>;