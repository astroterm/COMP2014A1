#pragma once

#include <array>
#include <variant>
#include <expected>

#include "constants.hpp"
#include "player.hpp"


struct Won { PlayerRef player; };
struct Draw {};
struct Playable {};
using Status = std::variant<Playable, Won, Draw>;

struct Taken { PlayerRef player; };
struct Empty {};
using Tile = std::variant<Empty, Taken>;

enum class MoveError {
    OutOfBounds,
    TileTaken,
    BoardFinished,
};

using Board = std::array<std::array<Tile, BOARDSIZE>, BOARDSIZE>;


class TicTacToe {
public:
    TicTacToe();
    std::expected<void, MoveError> addMove(PlayerRef, Move);
    bool displayRow(int row, char outsep, char insep) const;
    const Status& status() const;

private:
    bool playerWon(PlayerRef) const;
    void updateStatus(PlayerRef);

    Status status_;
    Board board;
    int moves;
};