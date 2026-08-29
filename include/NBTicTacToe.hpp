#pragma once

#include "constants.hpp"
#include "player.hpp"
#include "TicTacToe.hpp"
#include <functional>
#include <optional>


using NBoard = std::array<std::array<TicTacToe, BOARDSIZE>, BOARDSIZE>;
using BoardRef = std::optional<std::reference_wrapper<TicTacToe>>;

enum class SelectBoardError {
    OutOfBounds,
    BoardFull,
    GameOver
};

class NBTicTacToe {
public:
    NBTicTacToe();
    void displayBoards() const;

    Status status;
private:
    void updateStatus();
    std::expected<void, SelectBoardError> selectBoard();
    bool play(PlayerRef);

    NBoard nboard;
    BoardRef board;
};