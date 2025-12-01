#include "xo4x4.h"
#include"Help_Function.h"
#include <iostream>
using namespace std;


X_O_Board::X_O_Board() : Board(4, 4) {
    for (auto &row: board)
        for (auto &cell: row)
            cell = blank_symbol;

    // Player X start
    board[0][1] = 'X';
    board[0][3] = 'X';
    board[3][0] = 'X';
    board[3][2] = 'X';

    // Player O start
    board[0][0] = 'O';
    board[0][2] = 'O';
    board[3][1] = 'O';
    board[3][3] = 'O';
}


bool X_O_Board::update_board(Move<char> *m) {
    int fx = start_x;
    int fy = start_y;

    int tx = m->get_x();
    int ty = m->get_y();
    char sym = m->get_symbol();

    if (fx == tx && fy == ty && board[fx][fy] == sym) {
        start_x = start_y = -1;
        return true;
    }


    start_x = start_y = -1;


    if (fx < 0 || fy < 0 || fx >= 4 || fy >= 4) return false;
    if (board[fx][fy] != sym) return false;


    if (tx < 0 || ty < 0 || tx >= 4 || ty >= 4) return false;
    if (board[tx][ty] != blank_symbol) return false;

    int dx = abs(tx - fx);
    int dy = abs(ty - fy);

    if (!((dx == 1 && dy == 0) || (dx == 0 && dy == 1)))
        return false;


    board[fx][fy] = blank_symbol;
    board[tx][ty] = sym;

    return true;
}

bool X_O_Board::is_win(Player<char> *player) {
    char s = player->get_symbol();


    for (int i = 0; i < 4; i++)
        for (int j = 0; j <= 1; j++)
            if (board[i][j] == s && board[i][j + 1] == s && board[i][j + 2] == s)
                return true;


    for (int j = 0; j < 4; j++)
        for (int i = 0; i <= 1; i++)
            if (board[i][j] == s && board[i + 1][j] == s && board[i + 2][j] == s)
                return true;


    for (int i = 0; i <= 1; i++)
        for (int j = 0; j <= 1; j++)
            if (board[i][j] == s && board[i + 1][j + 1] == s && board[i + 2][j + 2] == s)
                return true;


    for (int i = 0; i <= 1; i++)
        for (int j = 2; j < 4; j++)
            if (board[i][j] == s && board[i + 1][j - 1] == s && board[i + 2][j - 2] == s)
                return true;

    return false;
}

bool X_O_Board::is_draw(Player<char> *player) {
    char sym = player->get_symbol();

    for (int fx = 0; fx < 4; fx++)
        for (int fy = 0; fy < 4; fy++) {
            if (board[fx][fy] != sym) continue;
            int moves[4][2] = {{fx + 1, fy}, {fx - 1, fy}, {fx, fy + 1}, {fx, fy - 1}};
            for (auto &mv: moves) {
                int tx = mv[0], ty = mv[1];
                if (tx < 0 || ty < 0 || tx >= 4 || ty >= 4) continue;
                if (board[tx][ty] == blank_symbol) return false;
            }
        }
    return true;
}
bool X_O_Board::game_is_over(Player<char> *player) {
    return is_win(player) || is_draw(player);
}


XO_UI::XO_UI() : UI("4x4 Moving Tic-Tac-Toe Game", 2) {
}

Player<char> *XO_UI::create_player(string &name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char> *XO_UI::get_move(Player<char> *player) {
    X_O_Board *b = (X_O_Board *) player->get_board_ptr();
    char sym = player->get_symbol();

    if (player->get_type() == PlayerType::HUMAN) {
        int fx, fy, tx, ty;
        cout << player->get_name() << " (" << sym << ") Move:\n";
        cout << "Enter: FROM_X\n";
        fx = getChoice(0, 3);
        cout << "Enter: FROM_Y\n";
        fy = getChoice(0, 3);
        cout << "Enter: TO_X\n";
        tx = getChoice(0, 3);
        cout << "Enter: TO_Y\n";
        ty = getChoice(0, 3);
        b->start_x = fx;
        b->start_y = fy;
        return new Move<char>(tx, ty, sym);
    }

    for (int fx = 0; fx < 4; fx++) {
        for (int fy = 0; fy < 4; fy++) {
            if (b->get_cell(fx, fy) != sym) continue;

            int moves[4][2] = {{fx + 1, fy}, {fx - 1, fy}, {fx, fy + 1}, {fx, fy - 1}};
            for (auto &mv: moves) {
                int tx = mv[0], ty = mv[1];
                if (tx < 0 || ty < 0 || tx >= 4 || ty >= 4) continue;
                if (b->get_cell(tx, ty) == b->blank_symbol) {
                    b->start_x = fx;
                    b->start_y = fy;
                    return new Move<char>(tx, ty, sym);
                }
            }
        }
    }
}
