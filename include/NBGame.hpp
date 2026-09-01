#pragma once

#include <array>
#include <memory>

#include "player.hpp"
#include "constants.hpp"
#include "NBTicTacToe.hpp"

class NBGame {
public:
    NBGame();
    void play();

private:

    std::array<std::unique_ptr<Player>, PLAYERNUM> players;
    NBTicTacToe board;
};