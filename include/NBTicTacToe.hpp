#pragma once

#include "constants.hpp"
#include "player.hpp"
#include "TicTacToe.hpp"
#include "random.hpp"
#include <functional>
#include <optional>

enum class BoardError {
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
    PlayResult play(PlayerRef);
    void displayBoards() const;
    const Status& status() const { return status_; }

private:
    std::expected<void, BoardError> updateStatus(Move move);
    std::expected<void, BoardError> selectBoard();

    Status status_;
    Random random;
    NBoard nboard;
    BoardRef currentBoard;
};