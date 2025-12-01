#ifndef xo4x4_H
#define xo4x4_H

#include "BoardGame_Classes.h"
using namespace std;

class X_O_Board : public Board<char> {
public:
    int start_x = -1;
    int start_y = -1;
    char blank_symbol = '.';

    X_O_Board();

    char get_cell(int x, int y) const {
        return board[x][y];
    }

    bool update_board(Move<char> *move) override;

    bool is_win(Player<char> *player) override;

    bool is_lose(Player<char> *) override { return false; };

    bool is_draw(Player<char> *player) override;

    bool game_is_over(Player<char> *player) override;
};

class XO_UI : public UI<char> {
public:
    XO_UI();

    ~XO_UI() {
    };

    Player<char> *create_player(string &name, char symbol, PlayerType type) override;

    Move<char> *get_move(Player<char> *player) override;
};


#endif //xo4x4_H
