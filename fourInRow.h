//
// Created by Bavly on 11/27/2025.
//

#ifndef FOURINROW_H
#define FOURINROW_H
#include "BoardGame_Classes.h"


class fourBoard : public Board<char> {
private:
    char BlankSymbol = '.';

public:
    fourBoard();

    ~fourBoard();

    bool update_board(Move<char> *move) override;

    bool is_draw(Player<char> *) override;

    bool is_lose(Player<char> *) override;

    bool is_win(Player<char> *) override;

    bool game_is_over(Player<char> *) override;
};


class fourUI : public UI<char> {
private:
public:
    fourUI();

    ~fourUI();

    Player<char> *create_player(string &name, char symbol, PlayerType type) override;

    Player<char> **setup_players() override;

    Move<char> *get_move(Player<char> *) override;
};

#endif //FOURINROW_H
