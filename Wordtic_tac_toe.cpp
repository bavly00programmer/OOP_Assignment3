//
// Created by compu50store on 12/10/2025.
//

#include "Wordtic_tac_toe.h"
#include "Help_Function.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

Word_Board::Word_Board() : Board(3, 3) {
    board.assign(3, std::vector<char>(3, blank_symbol));
    load_dictionary("dic.txt");
}

bool Word_Board::load_dictionary(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) return false;

    std::string word;
    while (file >> word) {
        if (word.size() == 3)
            dictionary.insert(word);
    }
    return true;
}

bool Word_Board::check_word(const std::string &w) {
    return dictionary.count(w) > 0;
}

bool Word_Board::update_board(Move<char> *move) {
    int x = move->get_x();
    int y = move->get_y();
    char c = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (board[x][y] != blank_symbol)
        return false;

    board[x][y] = c;
    n_moves++;

    return true;
}

std::string Word_Board::get_row_word(int r) {
    std::string w;
    for (int c = 0; c < 3; c++) w += board[r][c];
    return w;
}

std::string Word_Board::get_col_word(int c) {
    std::string w;
    for (int r = 0; r < 3; r++) w += board[r][c];
    return w;
}

std::string Word_Board::get_diag1_word() {
    return std::string() + board[0][0] + board[1][1] + board[2][2];
}

std::string Word_Board::get_diag2_word() {
    return std::string() + board[0][2] + board[1][1] + board[2][0];
}

bool Word_Board::is_win(Player<char> *player) {
    return player->get_symbol();

    // Check all 8 possible 3-letter sequences
    for (int r = 0; r < 3; r++)
        if (check_word(get_row_word(r))) return true;

    for (int c = 0; c < 3; c++)
        if (check_word(get_col_word(c))) return true;

    if (check_word(get_diag1_word())) return true;
    if (check_word(get_diag2_word())) return true;

    return false;
}

bool Word_Board::is_draw(Player<char> *player) {
    return n_moves == 9 && !is_win(player);
}

bool Word_Board::is_lose(Player<char> *player) {
    return false; // No losing condition except opponent's win
}

bool Word_Board::game_is_over(Player<char> *player) {
    return is_win(player) || n_moves == 9;
}

// ---------- UI IMPLEMENTATION -------------

Word_UI::Word_UI() : UI("Welcome to Word Tic-Tac-Toe!", 3) {}

Player<char>* Word_UI::create_player(std::string &name, char symbol, PlayerType type) {
    std::cout << "Creating player (" << symbol << "): " << name << "\n";
    return new Player<char>(name, symbol, type);
}

Player<char>** Word_UI::setup_players() {
    Player<char>* players = new Player<char>[2];

    std::vector<std::string> types = {"Human", "Computer"};

    std::string name1 = get_player_name("Player 1");
    PlayerType t1 = get_player_type_choice("Player 1", types);
    players[0] = create_player(name1, 'A', t1);

    std::string name2 = get_player_name("Player 2");
    PlayerType t2 = get_player_type_choice("Player 2", types);
    players[1] = create_player(name2, 'B', t2);

    return &players;
}

Move<char>* Word_UI::get_move(Player<char> *player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        std::cout << player->get_name() << ", enter your move:\n";
        std::cout << "Row (0-2): ";
        x = getChoice(0, 2);
        std::cout << "Column (0-2): ";
        y = getChoice(0, 2);

        std::cout << "Enter a letter: ";
        char letter;
        std::cin >> letter;
        return new Move<char>(x, y, toupper(letter));
    }
    else {
        x = rand() % 3;
        y = rand() % 3;
        char letter = 'A' + (rand() % 26);
        return new Move<char>(x, y, letter);
    }
}