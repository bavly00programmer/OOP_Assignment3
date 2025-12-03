//
// Created by M on 01/12/2025.
//

#ifndef DIAMOND_H
#define DIAMOND_H
#include "BoardGame_Classes.h"
#include <vector>
#include <utility>

using namespace std;



class DIAMOND_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
   DIAMOND_Board();
   ~DIAMOND_Board() {}

bool update_board(Move<char>* move) override;
bool is_win(Player<char>* player) override;
bool is_lose(Player<char>* player) override {return false;}
bool is_draw(Player<char>* player) override;
bool game_is_over(Player<char>* player) override;

//helper method for diamond board
bool is_valid_cell(int x, int y) const;
bool check_line_of_three(Player<char>* player) const;
bool check_line_of_four(Player<char>* player) const;
void get_diamond_position(vector<pair<int, int>>& positions) const;

private:
//pre-defined diamond positions in a 5x5 grid
static const vector<pair<int, int>> DIAMOND_CELLS;

};

class DIAMOND_UI : public UI<char> {
public:
DIAMOND_UI();
~DIAMOND_UI() {}
 Player<char>* create_player(string& name, char symbol,PlayerType type) override;
 Move<char>* get_move(Player<char>* player) override;
 Player<char>** setup_players() override;

private:
bool is_diamond_position(int x, int y) const;

};



#endif //DIAMOND_H
