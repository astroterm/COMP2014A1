#pragma once

#include "constants.hpp"
#include "player.hpp"
#include "TicTacToe.hpp"
#include <memory>

using NBoard = std::array<std::array<Board, BOARDSIZE>, BOARDSIZE>;

class NBTicTacToe {
private:
    std::array<std::unique_ptr<Player>, PLAYERNUM> players;
    NBoard nboard;
};