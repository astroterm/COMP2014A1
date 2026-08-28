#pragma once

#include <array>
#include <variant>

#include "constants.hpp"
#include "player.hpp"

struct Win { Player& player; };
struct Draw {};
struct Playable {};
using Status = std::variant<Playable, Win, Draw>;

struct Taken { Player& player; };
struct Empty {};
using Tile = std::variant<Empty, Taken>;


class TicTacToe {
public:
    TicTacToe();
    int addMove(Player);
    int displayRow(int, char) const;

private:
    bool isValidMove(int, int) const;
    int gameStatus() const;

    std::array<std::array<Tile, BOARDSIZE>, BOARDSIZE> board;
    Status status;
};
