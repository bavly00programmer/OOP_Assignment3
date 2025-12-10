//
// Created by Mostafa on 11/26/2025
//


#ifndef OOPA3_WORDTIC_TAC_TOE_H
#define OOPA3_WORDTIC_TAC_TOE_H

#include <string>
#include <set>
#include "BoardGame_Classes.h"

/**
 * @class Word_Board
 * @brief Board logic for Word Tic-Tac-Toe
 *
 * Players place letters on a 3x3 grid. The first player to form
 * a valid 3-letter word horizontally, vertically, or diagonally wins.
 */
class Word_Board : public Board<char> {
private:
    char blank_symbol = '.';
    std::set<std::string> dictionary;   ///< Valid words loaded from dic.txt

public:
    Word_Board();

    bool update_board(Move<char> *move) override;
    bool is_win(Player<char> *player) override;
    bool is_draw(Player<char> *player) override;
    bool is_lose(Player<char> *player) override;
    bool game_is_over(Player<char> *player) override;

    bool load_dictionary(const std::string& filename);
    bool check_word(const std::string& w);

    std::string get_row_word(int r);
    std::string get_col_word(int c);
    std::string get_diag1_word();
    std::string get_diag2_word();
};

/**
 * @class Word_UI
 * @brief User Interface for Word Tic-Tac-Toe
 */
class Word_UI : public UI<char> {
public:
    Word_UI();
    ~Word_UI() override = default;

    Player<char>* create_player(std::string &name, char symbol, PlayerType type) override;
    Player<char>** setup_players() override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif