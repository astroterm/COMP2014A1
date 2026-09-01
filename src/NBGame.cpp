#include "NBGame.hpp"
#include "NBTicTacToe.hpp"
#include "player.hpp"
#include <variant>
#include <iostream>
#include <memory>


NBGame::NBGame() :
    players {
        std::make_unique<HumanPlayer>('X', "Player 1"),
        std::make_unique<RandomPlayer>('O', "Player 2"),
    },
    board {}
{}

void NBGame::play() {
    PlayResult result;
    board.displayBoards();
    while (std::holds_alternative<Playable>(board.status)) {
        for (auto& player : players) {
            do {
                result = board.play(*player);
                if (result || 
                    !std::holds_alternative<Playable>(
                        board.status
                    )
                ) {
                    board.displayBoards();
                    break;
                }
            } while (true);
            
            if (!std::holds_alternative<Playable>(
                board.status
            )) break;
        }
    }
    if (std::holds_alternative<Draw>(board.status)) {
        std::cout << "The game ended in a draw.\n";
    } else {
        std::cout << "The winner is: " <<
        std::get<Won>(board.status).player.get().name
        << "!!\n";
    }
}