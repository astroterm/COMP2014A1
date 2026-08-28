#include "TicTacToe.hpp"

#include <expected>
#include <iostream>
#include <array>
#include <variant>

#include "constants.hpp"
#include "player.hpp"

namespace {
    bool samePlayer(PlayerRef a, PlayerRef b) {
        return &a.get() == &b.get();
    }
}

TicTacToe::TicTacToe() :
    board  {},
    status {}
{}

bool TicTacToe::displayRow(int row, char separator) const {
    if (row >= BOARDSIZE || row < 0) return false;
    for (const auto& tile : board[row]) {
        std::cout << separator << " ";
        if (auto* taken = std::get_if<Taken>(&tile))
            std::cout << taken->player.get().token;
        else std::cout << " ";
        std::cout << " ";
    }
    std::cout << separator;
    return true;
}

std::expected<void, MoveError> TicTacToe::addMove(PlayerRef player) {
    auto [row, col] = player.get().move();

    if (!std::holds_alternative<Playable>(status))
        return std::unexpected(MoveError::BoardFinished);

    if (row >= BOARDSIZE || col >= BOARDSIZE || row < 0 || col < 0)
        return std::unexpected(MoveError::OutOfBounds);

    if (!std::holds_alternative<Empty>(board[row][col]))
        return std::unexpected(MoveError::TileTaken);

    board[row][col] = Taken {player};

    return {};
}

bool TicTacToe::playerWin(PlayerRef player) {
    std::bitset<9> bitboard;
    int i = 0;
    for (const auto row : board)
        for (const auto& tile : row)
            if (auto* taken = std::get_if<Taken>(&tile))
                if (samePlayer(player, taken->player))
                    bitboard.set(i++);

}

