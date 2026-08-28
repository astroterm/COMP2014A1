#pragma once

#include <array>
#include <variant>
#include <expected>
#include <functional>

#include "constants.hpp"
#include "player.hpp"

struct Won { std::reference_wrapper<Player> player; };
struct Draw {};
struct Playable {};
using Status = std::variant<Playable, Won, Draw>;

struct Taken { std::reference_wrapper<Player> player; };
struct Empty {};
using Tile = std::variant<Empty, Taken>;

enum class MoveError {
    OutOfBounds,
    TileTaken,
    BoardFinished,
};


class TicTacToe {
public:
    TicTacToe();
    std::expected<void, MoveError> addMove(Player*);
    bool displayRow(int, char) const;

private:
    bool isValidMove(int, int) const;
    Status gameStatus() const;

    std::array<std::array<Tile, BOARDSIZE>, BOARDSIZE> board;
    Status status;
};
