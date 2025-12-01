//
// Created by Bavly on 11/27/2025.
//

#ifndef OBgame_H
#define OBgame_H
#include "BoardGame_Classes.h"


class ObstaclesBoard: public Board<char> {
private:
    char BlankSymbol = '.';
    char ObstacleSymbol = '#';

public:
    ObstaclesBoard();

    ~ObstaclesBoard()override;

    bool update_board(Move<char> *move) override;

    bool is_draw(Player<char> *) override;

    bool is_lose(Player<char> *) override;

    bool is_win(Player<char> *) override;

    bool game_is_over(Player<char> *) override;
};


class ObstaclesUI : public UI<char> {
private:
public:
    ObstaclesUI();

    ~ObstaclesUI()override;

    Player<char> *create_player(string &name, char symbol, PlayerType type) override;

    Player<char> **setup_players() override;

    Move<char> *get_move(Player<char> *) override;
};

#endif //OBgame_H
