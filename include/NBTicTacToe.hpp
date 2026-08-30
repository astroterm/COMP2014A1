#pragma once

#include "constants.hpp"
#include "player.hpp"
#include "TicTacToe.hpp"
#include <functional>
#include <optional>

enum class BoardError {
    OutOfBounds,
    BoardFull,
    GameOver,
    NoBoard,
};

using NBoard = std::array<std::array<TicTacToe, BOARDSIZE>, BOARDSIZE>;
using BoardRef = std::optional<std::reference_wrapper<TicTacToe>>;
using PlayResult = std::expected<void, std::variant<BoardError, MoveError>>;


class NBTicTacToe {
public:
    NBTicTacToe();
    NBTicTacToe(int seed);
    void displayBoards() const;
    std::expected<void, BoardError> selectBoard(PlayerRef);

    Status status;
private:
    std::expected<void, BoardError> updateStatus(Move move);
    PlayResult play(PlayerRef);

    NBoard nboard;
    BoardRef currentBoard;
};