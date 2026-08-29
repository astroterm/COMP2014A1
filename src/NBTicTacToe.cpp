#include "NBTicTacToe.hpp"

#include <iostream>

#include "TicTacToe.hpp"

namespace {
    bool sameTTT(BoardRef ref, const TicTacToe* ttt) {
        return ref && &ref->get() == ttt;
    }
}

NBTicTacToe::NBTicTacToe() :
    status {},
    nboard {},
    currentBoard  ()
{}

void NBTicTacToe::displayBoards() const {
    for (const auto& row : nboard) {
        // This level is every row of boards
        for (const auto& col : row) {
            std::cout << " " << std::string(
                11, sameTTT(currentBoard, &col) ? '*' : '-'
            ) << " ";
        }
        std::cout << '\n';
        for (int i = 0; i < BOARDSIZE; i++) {
            // this level is every row of the tictactoe
            for (const auto& col : row) {
                // in here is each tictactoe itself
                col.displayRow(i, sameTTT(currentBoard, &col) ? '*' : '|', '|');
            }
            std::cout << "\n";
            if (i != BOARDSIZE - 1) for (const auto& col : row) {
                std::cout
                    << (sameTTT(currentBoard, &col) ? '*' : '-')
                    << " -   -   - "
                    << (sameTTT(currentBoard, &col) ? '*' : '-');
            }
            std::cout << '\n';
        }
        std::cout << '\n';
        for (const auto& col : row) {
            std::cout << " " << std::string(
                11, sameTTT(currentBoard, &col) ? '*' : '-'
            ) << " ";
        }
        std::cout << '\n';
    }
}


PlayResult NBTicTacToe::play(PlayerRef player) {
    if (!std::holds_alternative<Playable>(status))
        return std::unexpected(MoveError::BoardFinished);

    if (!currentBoard) return std::unexpected(BoardError::NoBoard);

    auto [row, col] = player.get().move();

    auto result = currentBoard->get().addMove(player, {row, col});
    if (!result) return std::unexpected(result.error());

    auto select = selectBoard({row, col});
    if (!select) return std::unexpected(select.error());

    return {};
}