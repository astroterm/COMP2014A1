#include "player.hpp"
#include "constants.hpp"
#include <string>
#include <iostream>


Player::Player(char token, std::string name) :
    token(token),
    name(name),
    random()
{}


HumanPlayer::HumanPlayer(char token, std::string name) : Player(token, name) {}

Move HumanPlayer::move() {
    int row, col;
    std::cout << "Make your move: \n";
    std::cout << "row: ";
    std::cin >> row;
    std::cout << "column: ";
    std::cin >> col;

    return {row - 1, col - 1};
}

RandomPlayer::RandomPlayer(char token, std::string name) : Player(token, name) {}

Move RandomPlayer::move() {
    int row = random.range(0, BOARDSIZE);
    int col = random.range(0, BOARDSIZE);

    return {row, col};
}