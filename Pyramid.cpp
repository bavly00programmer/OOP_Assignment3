//
// Created by HEBA on 12/1/2025.
//
#include "Pyramid.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

#include "Help_Function.h"


using namespace std;

//Board Implementation

pyramid_Board::pyramid_Board() : Board(3, 5) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    board [0][0] = '#';
    board [0][1] = '#';
    board [0][3] = '#';
    board [0][4] = '#';
    board [1][0] = '#';
    board [1][4] = '#';

}

pyramid_Board::~pyramid_Board() {}


bool pyramid_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    //check if position is valid
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }
    //check if cell belongs to pyramid shape
    if (board[x][y] == '#') {
        cout<<"Invalid position"<<endl;
        return false;
    }

    // Undo move
        if (mark == 0) {
            if (board[x][y] == blank_symbol) {
                return false;
            }
            n_moves--;
            board[x][y] = blank_symbol;
        }
    //check if cell is empty
    if (board[x][y] != blank_symbol) {
        return false;
    }
    // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
             return true;
};


bool pyramid_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    // Bottom row: 4 possibilities
    if (board[1][1] == sym && board[1][2] == sym && board[1][3] == sym)
        return true;

    if (board[2][0] == sym && board[2][1] == sym && board[2][2] == sym)
        return true;

    if (board[2][1] == sym && board[2][2] == sym && board[2][3] == sym)
        return true;

    if (board[2][2] == sym && board[2][3] == sym && board[2][4] == sym)
        return true;

    // Column 2
    if (board[0][2] == sym && board[1][2] == sym && board[2][2] == sym)
        return true;

    // Diagonal
    if (board[0][2] == sym && board[1][3] == sym && board[2][4] == sym)
        return true;

    // Anti_diagonal
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym)
        return true;

    return false;
}

bool pyramid_Board::is_lose(Player<char> *player) {
    return false;
}







bool pyramid_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool pyramid_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//UI Implementation

pyramid_UI::pyramid_UI() : UI<char>("Weclome to FCAI PYRAMID Game", 3) {

}

pyramid_UI::~pyramid_UI() {}


Player<char> **pyramid_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = {"Human", "Computer"};

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X" , type_options);
    players[0] = create_player(nameX , 'X' , typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O" , type_options);
    players[1] = create_player(nameO , 'O' , typeO);
    return players;
}

Player<char>* pyramid_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "AI")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* pyramid_UI::get_move(Player<char>* player) {
    pyramid_Board* b = (pyramid_Board*)player->get_board_ptr();
    char sym = player->get_symbol();
    char opp = (sym == 'X') ? 'O' : 'X';

    int rows = b->get_rows();
    int cols = b->get_columns();

    if (player->get_type() == PlayerType::HUMAN) {
        int x, y;
        cout << "It's your turn!\n";
        cout << "Row (0-2): ";
        x = getChoice(0, 2);
        cout << "Column (0-4): ";
        y = getChoice(0, 4);

        return new Move<char>(x, y, sym);
    }

    Player<char> self("ai", sym, PlayerType::HUMAN);
    Player<char> enemy("enemy", opp, PlayerType::HUMAN);

    //Try to win
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (b->get_cell(i, j) != '.') continue;

            b->set_cell(i, j, sym);
            if (b->is_win(&self)) {
                b->set_cell(i, j, '.');
                return new Move<char>(i, j, sym);
            }
            b->set_cell(i, j, '.');
        }
    }

    //Prevent oppenent
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (b->get_cell(i, j) != '.') continue;

            b->set_cell(i, j, opp);
            if (b->is_win(&enemy)) {
                b->set_cell(i, j, '.');
                return new Move<char>(i, j, sym);
            }
            b->set_cell(i, j, '.');
        }
    }

    //Random choice
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (b->get_cell(i, j) == '.') {
                return new Move<char>(i, j, sym);
            }
        }
    }

    // no valid move
    return new Move<char>(0, 0, sym);
}
