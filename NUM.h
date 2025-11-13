#ifndef NUM_H
#define NUM_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
using namespace std;

class NUM_Board : public Board<int> {
private:
    int blank_symbol = 0;

public:
    NUM_Board();

    bool update_board(Move<int> *move);
    bool is_win(Player<int> *player);
    bool is_lose(Player<int> *) { return false; };
    bool is_draw(Player<int> *player);
    bool game_is_over(Player<int> *player);

    bool is_valid_number_for_player(int num, Player<int> *player);

    // 🔹 أضف التصريحات دي لأنها مستخدمة في .cpp
    vector<int> get_used_numbers() const;
    int get_cell(int x, int y) const;
    int get_blank_symbol() const;
};

class NUM_Player : public Player<int> {
    string id; // even or odd
    vector<int> ValidNum;

public:
    NUM_Player(const string &n, const string &id_, PlayerType t);

    vector<int> getValidNumbers(const vector<int> &used);
    string get_id() const;
};

class NUM_UI : public UI<int> {
public:
    NUM_UI();
    ~NUM_UI() {}

    Player<int> *create_player(string &name, int symbol, PlayerType type);
    Move<int> *get_move(Player<int> *player);

    Player<int>** setup_players() override;
};

#endif // NUM_H
