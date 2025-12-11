//
// Created by HEBA on 12/4/2025.
//
#include "Memory.h"
#include <iostream>
#include <iomanip>
#include <cctype>

#include "Help_Function.h"


using namespace std;

// Implementation

memory_Board::memory_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto &row: board)
        for (auto &cell: row)
            cell = blank_symbol;
    hidden_board = vector<vector<char> >(rows, vector<char>(columns, blank_symbol));
}

memory_Board::~memory_Board() {
}

bool memory_Board::update_board(Move<char> *move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (hidden_board[x][y] == blank_symbol || mark == 0)) {
        // Apply move
        if (mark != 0) {
            n_moves++;
            hidden_board[x][y] = toupper(mark);
            board[x][y] = '#';
        }

        return true;
    }
    return false;
}

bool memory_Board::is_win(Player<char> *player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
    };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(hidden_board[i][0], hidden_board[i][1], hidden_board[i][2]) && hidden_board[i][0] == sym) ||
            (all_equal(hidden_board[0][i], hidden_board[1][i], hidden_board[2][i]) && hidden_board[0][i] == sym))
            return true;
    }

    // Check diagonals
    if ((all_equal(hidden_board[0][0], hidden_board[1][1], hidden_board[2][2]) && hidden_board[1][1] == sym) ||
        (all_equal(hidden_board[0][2], hidden_board[1][1], hidden_board[2][0]) && hidden_board[1][1] == sym))
        return true;

    return false;
}

bool memory_Board::is_draw(Player<char> *player) {
    return (n_moves == 9 && !is_win(player));
}

bool memory_Board::is_lose(Player<char> *player) {
    if (n_moves < rows * columns) return false;
    return !is_win(player);
}

bool memory_Board::game_is_over(Player<char> *player) {
    return is_win(player) || is_draw(player);
}

//UI Implementation

memory_UI::memory_UI() : UI<char>("Weclome to FCAI Memory Tic-Tac-Toe", 3) {
}

memory_UI::~memory_UI() {

};


Player<char> *memory_UI::create_player(string &name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
            << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char> *memory_UI::get_move(Player<char> *player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "It 's your turn" << endl;
        cout << "\nPlease enter your move x (0:2)\n ";
        x = getChoice(0, 2);
        cout << "\nPlease enter your move y (0:2)\n ";
        y = getChoice(0, 2);
    } else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}
