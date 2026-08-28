#include "TicTacToe.hpp"

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
        if (std::holds_alternative<Empty>(tile))
            std::cout << " ";
        std::cout << " ";
    }
    std::cout << separator;
    return true;
}
