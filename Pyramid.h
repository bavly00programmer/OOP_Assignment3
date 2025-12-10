//
// Created by HEBA on 12/1/2025.
//

#ifndef PYRAMID_H
#define PYRAMID_H
#include "BoardGame_Classes.h"
using namespace std;


class pyramid_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    char get_cell(int x, int y) const {
        return board[x][y];
    }
    void set_cell(int x, int y, char value) {
        board[x][y] = value;
    }


    pyramid_Board();

    bool update_board(Move<char>* move)override;


    bool is_win(Player<char>* player)override;

    bool is_lose(Player<char>*) {
        return false;
    };

    bool is_draw(Player<char>* player)override;

    bool game_is_over(Player<char>* player)override;

};

class pyramid_UI : public UI<char> {
public:

    pyramid_UI();

    ~pyramid_UI() {};

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    Player<char> **setup_players() override;

    virtual Move<char>* get_move(Player<char>* player)override;
};

#endif //PYRAMID_H
