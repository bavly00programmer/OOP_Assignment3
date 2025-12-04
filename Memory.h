//
// Created by  HEBA on 12/4/2025.
//
#ifndef MEMORY_H
#define MEMORY_H
#include "BoardGame_Classes.h"
using namespace std;


class memory_Board : public Board<char> {
private:
    char blank_symbol = '.';
    vector<vector<char>> hidden_board;

public:

    memory_Board();
    ~memory_Board()override;

    bool update_board(Move<char>* move)override;

    bool is_win(Player<char>* player)override;

    bool is_lose(Player<char>*) override;

    bool is_draw(Player<char>* player)override;

    bool game_is_over(Player<char>* player)override;

};

class memory_UI : public UI<char> {

public:

    memory_UI();

    ~memory_UI() override;



    Player<char>* create_player(string& name, char symbol, PlayerType type)override;


     Move<char>* get_move(Player<char>* player) override;
};

#endif //MEMORY_H
