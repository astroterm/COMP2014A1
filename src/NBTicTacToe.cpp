#include <algorithm>
#if defined(__clang__)
#    define MUSTTAIL [[clang::musttail]]
#elif defined(__GNUC__) && __GNUC__ >= 15
#    define MUSTTAIL [[gnu::musttail]]
#else
#    define MUSTTAIL
#endif

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

std::expected<void, BoardError> NBTicTacToe::updateStatus(PlayerRef player, Move move) {
    for (const auto& row : nboard)
        for (const auto& ttt : row)
            if (std::holds_alternative<Won>(ttt.status)) {
                status = ttt.status;
                return std::unexpected(BoardError::GameOver);
            }
    
    if (
        std::ranges::all_of(nboard, [](const auto& row) {
            return std::ranges::all_of(row, [](const auto& ttt) {
                return std::holds_alternative<Draw>(ttt.status);
            });
        })
    ) {
        status = Draw{};
        return std::unexpected(BoardError::GameOver);
    }

    auto [row, col] = move;
    TicTacToe& newboard = nboard[row][col];

    if (std::holds_alternative<Playable>(newboard.status)) {
        currentBoard = newboard;
        return {};
    }

    MUSTTAIL return updateStatus(player, player.get().select());

}

PlayResult NBTicTacToe::play(PlayerRef player) {
    if (!std::holds_alternative<Playable>(status))
        return std::unexpected(MoveError::BoardFinished);

    if (!currentBoard) return std::unexpected(BoardError::NoBoard);

    auto [row, col] = player.get().move();

    auto result = currentBoard->get().addMove(player, {row, col});
    if (!result) return std::unexpected(result.error());

    auto select = updateStatus(player, {row, col});
    if (!select) return std::unexpected(select.error());

    return {};
}

