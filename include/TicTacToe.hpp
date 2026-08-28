#pragma once

#include <array>
#include "constants.hpp"

class TicTacToe {
public:
    TicTacToe();
    int addMove(int, int);
    int displayRow(int) const;

private:
    bool isValidMove(int, int) const;
    int gameStatus() const;

    std::array<std::array<int, BOARDSIZE>, BOARDSIZE> board;
};