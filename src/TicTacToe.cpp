#include "TicTacToe.hpp"

#include <expected>
#include <iostream>
#include <array>
#include <variant>

#include "constants.hpp"
#include "player.hpp"



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

    if (!std::holds_alternative<Playable>(gameStatus()))
        return std::unexpected(MoveError::BoardFinished);

    if (row >= BOARDSIZE || col >= BOARDSIZE || row < 0 || col < 0)
        return std::unexpected(MoveError::OutOfBounds);

    if (!std::holds_alternative<Empty>(board[row][col]))
        return std::unexpected(MoveError::TileTaken);

    board[row][col] = Taken {player};

    return {};
}
