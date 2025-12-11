//
// Created by Mostafa Mamdoh on 12/2/2025.
//

#include "fivebyfivetic_tac_toe.h"

#include "Help_Function.h"
#include <iostream>
using namespace std;


///==============================
///        BOARD LOGIC
///==============================

FiveByFive_Board::FiveByFive_Board() : Board(5, 5) {
    for (auto& row : board)
        for (auto& c : row)
            c = blank_symbol;
}

bool FiveByFive_Board::update_board(Move<char>* move) {

    int x = move->get_x();
    int y = move->get_y();
    char s = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (board[x][y] != blank_symbol)
        return false;

    int before = count_sequences(this);

    board[x][y] = s;
    n_moves++;

    int after = count_sequences(this);
    int gained = after - before;

    points_map[s] += gained;

    return true;
}


/// Count all 3-in-a-row for X and O
int FiveByFive_Board::count_sequences(FiveByFive_Board* b) {

    int count = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {

            char c = b->board[i][j];
            if (c == '.') continue;

            // RIGHT
            if (j + 2 < 5 &&
                b->board[i][j + 1] == c &&
                b->board[i][j + 2] == c)
                count++;

            // DOWN
            if (i + 2 < 5 &&
                b->board[i + 1][j] == c &&
                b->board[i + 2][j] == c)
                count++;

            // DIAGONAL DOWN-RIGHT
            if (i + 2 < 5 && j + 2 < 5 &&
                b->board[i + 1][j + 1] == c &&
                b->board[i + 2][j + 2] == c)
                count++;

            // DIAGONAL DOWN-LEFT
            if (i + 2 < 5 && j - 2 >= 0 &&
                b->board[i + 1][j - 1] == c &&
                b->board[i + 2][j - 2] == c)
                count++;
        }
    }

    return count;
}


int FiveByFive_Board::count_points_for(Player<char>* p) {
    return points_map[p->get_symbol()];
}


bool FiveByFive_Board::is_win(Player<char>* p) {
    if (n_moves < 24) return false;

    char me = p->get_symbol();
    char opp = (me == 'X' ? 'O' : 'X');

    return points_map[me] > points_map[opp];
}

bool FiveByFive_Board::is_lose(Player<char>* p) {
    if (n_moves < 24) return false;

    char me = p->get_symbol();
    char opp = (me == 'X' ? 'O' : 'X');

    return points_map[me] < points_map[opp];
}

bool FiveByFive_Board::is_draw(Player<char>* p) {
    if (n_moves < 24) return false;

    char me = p->get_symbol();
    char opp = (me == 'X' ? 'O' : 'X');

    return points_map[me] == points_map[opp];
}

bool FiveByFive_Board::game_is_over(Player<char>* p) {
    return n_moves == 24;
}



///==============================
///             UI
///==============================

FiveByFive_UI::FiveByFive_UI()
        : UI("Welcome to Five-by-Five Tic Tac Toe!", 5) {}


Player<char>* FiveByFive_UI::create_player(string& name, char sym, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "Human" : "Computer")
         << " Player (" << sym << "): " << name << endl;

    return new Player<char>(name, sym, type);
}


Player<char>** FiveByFive_UI::setup_players() {

    Player<char>** players = new Player<char>*[2];
    vector<string> types = {"Human", "Computer"};

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", types);
    players[0] = create_player(nameX, 'X', typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", types);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}


Move<char>* FiveByFive_UI::get_move(Player<char>* player) {

    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {

        cout << player->get_name() << ", it's your turn!\n";
        cout << "Enter row (0–4): ";
        x = getChoice(0, 4);

        cout << "Enter column (0–4): ";
        y = getChoice(0, 4);
    }
    else { /// Computer move
        x = rand() % 5;
        y = rand() % 5;
    }

    return new Move<char>(x, y, player->get_symbol());
}