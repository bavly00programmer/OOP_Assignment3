//
// Created by Bavly on 11/25/2025.
//

#ifndef GAME10_H
#define GAME10_H

#include <deque>

#include "BoardGame_Classes.h"
using namespace std;


class infinity_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    int count=0;
    deque<pair<int, int>> MOVES;

   infinity_Board();


    bool update_board(Move<char> *move);

    bool is_win(Player<char> *player);

    bool is_lose(Player<char> *) { return false; };

    bool is_draw(Player<char> *player);

    bool game_is_over(Player<char> *player);
};


class infinity_UI : public UI<char> {
public:
    infinity_UI();

    ~infinity_UI() {
    };


    Player<char> *create_player(string &name, char symbol, PlayerType type);

    virtual Move<char> *get_move(Player<char> *player);
};


#endif //GAME10_H
