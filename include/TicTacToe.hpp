#pragma once

#include <array>
#include <variant>
#include <expected>
#include <functional>

#include "constants.hpp"
#include "player.hpp"

using PlayerRef = std::reference_wrapper<Player>;

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


class TicTacToe {
public:
    TicTacToe();
    std::expected<void, MoveError> addMove(PlayerRef);
    bool displayRow(int, char) const;

    Status status;
private:
    void updateStatus();

    bool playerWin(PlayerRef);

    std::array<std::array<Tile, BOARDSIZE>, BOARDSIZE> board;
    
};