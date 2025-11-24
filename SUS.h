//
// Created by Bavly on 11/24/2025.
//

#ifndef SUS_H
#define SUS_H
#include<map>
#include "BoardGame_Classes.h"



class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.';
    static int SUS_Sequence;
    map<char, int> points_map;
public:
    SUS_Board();

    bool update_board(Move<char> *move) override;

    bool is_win(Player<char> *player) override;

    bool is_draw(Player<char> *player) override;

    bool is_lose(Player<char> *player) override;

    bool game_is_over(Player<char> *player) override;

    int count_points_for(Player<char> *player);

     int count_sequences(SUS_Board *board);

};


class  SUS_UI: public UI<char> {
protected:PlayerType GetPlayerTypeChoice
    (string player_label, const vector<string> &options);

public:

    SUS_UI();

    ~SUS_UI() {
    };

    Player<char> *create_player(string &name, char symbol, PlayerType type);

    Move<char> *get_move(Player<char> *) override;

    Player<char> **setup_players() override;
};


#endif //SUS_H
