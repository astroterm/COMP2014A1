#include <algorithm>
#include <iostream>

#include "NBTicTacToe.hpp"
#include "TicTacToe.hpp"

#include "random.hpp"

namespace {
    bool sameTTT(BoardRef ref, const TicTacToe* ttt) {
        return ref && &ref->get() == ttt;
    }
}

NBTicTacToe::NBTicTacToe() :
    status {},
    random {},
    nboard {},
    currentBoard (
        nboard[
            random.range(0, BOARDSIZE)
        ][
            random.range(0, BOARDSIZE)
        ]
    )
{}

NBTicTacToe::NBTicTacToe(int seed) :
    status {},
    random {seed},
    nboard {},
    currentBoard (
        nboard[
            random.range(0, BOARDSIZE)
        ][
            random.range(0, BOARDSIZE)
        ]
    )
{}

void NBTicTacToe::displayBoards() const {
    std::cout << std::string(41, '=') << '\n';
    for (const auto& row : nboard) {
        for (const auto& col : row) {
            std::cout << " " << std::string(
                11, sameTTT(currentBoard, &col) ? '*' : '-'
            ) << "  ";
        }
        std::cout << '\n';
        for (int i = 0; i < BOARDSIZE; i++) {
            for (const auto& col : row) {
                col.displayRow(i, sameTTT(currentBoard, &col) ? '*' : '|', '|');
                std::cout << " ";
            }
            std::cout << "\n";
            if (i != BOARDSIZE - 1) {
                for (const auto& col : row) {
                    std::cout
                        << (sameTTT(currentBoard, &col) ? '*' : '|')
                        << " -   -   - "
                        << (sameTTT(currentBoard, &col) ? '*' : '|')
                        << ' ';
                }
                std::cout << '\n';
            }
        }
        for (const auto& col : row) {
            std::cout << " " << std::string(
                11, sameTTT(currentBoard, &col) ? '*' : '-'
            ) << "  ";
        }
        std::cout << "\n";
    }
    std::cout << std::string(41, '=') << "\n\n";
}

std::expected<void, BoardError> NBTicTacToe::updateStatus(Move move) {
    for (const auto& row : nboard)
        for (const auto& ttt : row)
            if (std::holds_alternative<Won>(ttt.getStatus())) {
                status = ttt.getStatus();
                return std::unexpected(BoardError::GameOver);
            }
    
    if (
        std::ranges::all_of(nboard, [](const auto& row) {
            return std::ranges::all_of(row, [](const auto& ttt) {
                return std::holds_alternative<Draw>(ttt.getStatus());
            });
        })
    ) {
        status = Draw{};
        return std::unexpected(BoardError::GameOver);
    }

    auto [row, col] = move;
    TicTacToe& newboard = nboard[row][col];

    if (std::holds_alternative<Playable>(newboard.getStatus())) {
        currentBoard = newboard;
        return {};
    }

    while (!selectBoard());
    return {};

}

PlayResult NBTicTacToe::play(PlayerRef player) {
    if (!std::holds_alternative<Playable>(status))
        return std::unexpected(MoveError::BoardFinished);

    if (!currentBoard) return std::unexpected(BoardError::NoBoard);

    auto [row, col] = player.get().move();

    auto result = currentBoard->get().addMove(player, {row, col});
    if (!result) return std::unexpected(result.error());

    auto select = updateStatus({row, col});
    if (!select) return std::unexpected(select.error());

    return {};
}

std::expected<void, BoardError> NBTicTacToe::selectBoard() {
    int row = random.range(0, BOARDSIZE);
    int col = random.range(0, BOARDSIZE);

    if (std::holds_alternative<Draw>(nboard[row][col].getStatus()))
        return std::unexpected(BoardError::BoardFull);

    currentBoard = nboard[row][col];
    return {};
}