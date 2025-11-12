//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>  // for toupper()
#include "NUM.h"

using namespace std;

//--------------------------------------- X_O_Board Implementation

NUM_Board::NUM_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool NUM_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int num = move->get_symbol();

    if (num >= 1 && num <= 9 &&
        find(used_numbers.begin(), used_numbers.end(), num) == used_numbers.end() &&
        board[x][y] == 0) {
        board[x][y] = num;
        used_numbers.push_back(num);
        n_moves++;
        return true;
        }
    return false;
}


bool NUM_Board::is_win(Player<int>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    for (int i = 0; i < rows; i++)
        if (board[i][0] + board[i][1] + board[i][2] == 15) return true;

    for (int j = 0; j < columns; j++)
        if (board[0][j] + board[1][j] + board[2][j] == 15) return true;

    if (board[0][0] + board[1][1] + board[2][2] == 15) return true;
    if (board[0][2] + board[1][1] + board[2][0] == 15) return true;


    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

bool NUM_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool NUM_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

NUM_UI::NUM_UI() : UI<int>("Weclome to FCAI Numerical Tic-Tac-Toe Game by Dr El-Ramly", 3) {}

Player<int>* NUM_UI::create_player(string& name, int symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<int>(name, symbol, type);
}

Move<int>* NUM_UI::get_move(Player<int>* player) {
    int x, y,num;
    vector<int> used_numbers;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "Enter your move (number 1-9): ";
        cin >>x>>y>> num;

    } else {
        do {
            x = rand() % 3;
            y = rand() % 3;
            num = rand() % 9 + 1;
        } while (find(used_numbers.begin(), used_numbers.end(), num) != used_numbers.end());

    }
    return new Move<int>(x, y, num);
}
