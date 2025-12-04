#ifndef ULTIMATE_H
#define ULTIMATE_H

#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;


const char BlankSymbol = '.';
const char blockSymbol = '#';
const char invaledSymbol = 'x';



int getCurrentBoard(int &x, int &y);
int getindexI(int &current);
int getindexJ(int &current);

// =========================
// ==       ultimateBoard ==
// =========================

class ultimateBoard : public Board<char> {
private:
    char mainboard[3][3] = {
        {BlankSymbol, BlankSymbol, BlankSymbol},
        {BlankSymbol, BlankSymbol, BlankSymbol},
        {BlankSymbol, BlankSymbol, BlankSymbol}
    };

public:
    ultimateBoard();
    ~ultimateBoard();

    bool update_board(Move<char> *move) override;
    bool is_win(Player<char> *player) override;
    bool is_lose(Player<char> *player) override;
    bool is_draw(Player<char> *player) override;
    bool game_is_over(Player<char> *player) override;

    bool check_the_mainboard(Player<char> *player);
    char get_cell(int &x,int&y) {
        return board[x][y];
    }
};


// =========================
// ==        ultimateUI   ==
// =========================

class ultimateUI : public UI<char> {
public:
    ultimateUI();
    ~ultimateUI();

    Player<char> *create_player(string &name, char symbol, PlayerType type) override;
    Player<char> **setup_players() override;
    Move<char> *get_move(Player<char> *player) override;
};

#endif // ULTIMATE_H
