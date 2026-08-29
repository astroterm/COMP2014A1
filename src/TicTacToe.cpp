#include "TicTacToe.hpp"

#include <expected>
#include <iostream>
#include <array>
#include <variant>

#include "constants.hpp"

namespace {
    bool samePlayer(PlayerRef a, PlayerRef b) {
        return &a.get() == &b.get();
    }
}

TicTacToe::TicTacToe() :
    status {},
    board  {},
    moves (0)
{}

bool TicTacToe::displayRow(int row, char outsep, char insep) const {
    if (row >= BOARDSIZE || row < 0) return false;
    bool first = true;
    std::cout << outsep << " ";
    for (const auto& tile : board[row]) {
        if (!first) std::cout << insep << " ";
        first = false;
        if (const auto* taken = std::get_if<Taken>(&tile))
            std::cout << taken->player.get().token;
        else std::cout << " ";
        std::cout << " ";
    }
    std::cout << outsep;
    return true;
}

std::expected<void, MoveError> TicTacToe::addMove(PlayerRef player, Move move) {
    if (!std::holds_alternative<Playable>(status))
        return std::unexpected(MoveError::BoardFinished);

    auto [row, col] = move;

    if (row >= BOARDSIZE || col >= BOARDSIZE || row < 0 || col < 0)
        return std::unexpected(MoveError::OutOfBounds);

    if (!std::holds_alternative<Empty>(board[row][col]))
        return std::unexpected(MoveError::TileTaken);

    board[row][col] = Taken {player};

    moves++;
    updateStatus(player);
    return {};
}

void TicTacToe::updateStatus(PlayerRef player) {
    std::bitset<9> bitboard;
    int i = 0;
    for (const auto& row : board)
        for (const auto& tile : row) {
            if (const auto* taken = std::get_if<Taken>(&tile))
                if (samePlayer(player, taken->player))
                    bitboard.set(i);
            i++;
        }
    
    for (const auto& pattern : WIN_PATTERNS) {
        if ((bitboard & pattern) == pattern) {
            status = Won {player};
            return;
        }
    }
    if (moves >= 9) status = Draw {};
}
