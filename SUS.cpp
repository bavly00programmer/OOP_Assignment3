//
// Created by Bavly on 11/24/2025.
//
#include"Help_Function.h"
#include "SUS.h"
//sus board Implementation

int SUS_Board::SUS_Sequence = 0;


SUS_Board::SUS_Board() : Board(3, 3) {
    for (auto &row: board)
        for (auto &cell: row)
            cell = blank_symbol;
}

bool SUS_Board::update_board(Move<char> *move) {
    int x = move->get_x();
    int y = move->get_y();
    char sy = move->get_symbol();

    //check if position is valid
    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    //check if cell empty
    if (board[x][y] != blank_symbol)
        return false;


    int before = count_sequences(this);
    board[x][y] = sy;
    n_moves++;
    int after = count_sequences(this);
    int new_points = after - before;
    points_map[sy] += new_points;
    return true;
}


int SUS_Board::count_sequences(SUS_Board *boardPtr) {
    int count = 0;


    for (int x = 0; x < boardPtr->get_rows(); x++) {
        if (boardPtr->board[x][0] == 'S' &&
            boardPtr->board[x][1] == 'U' &&
            boardPtr->board[x][2] == 'S')
            count++;
    }


    for (int y = 0; y < boardPtr->get_columns(); y++) {
        if (boardPtr->board[0][y] == 'S' &&
            boardPtr->board[1][y] == 'U' &&
            boardPtr->board[2][y] == 'S')
            count++;
    }


    if (boardPtr->board[0][0] == 'S' &&
        boardPtr->board[1][1] == 'U' &&
        boardPtr->board[2][2] == 'S')
        count++;

    if (boardPtr->board[0][2] == 'S' &&
        boardPtr->board[1][1] == 'U' &&
        boardPtr->board[2][0] == 'S')
        count++;

    return count;
}

int SUS_Board::count_points_for(Player<char> *player) {
    return points_map[player->get_symbol()];
}

bool SUS_Board::is_win(Player<char> *player) {
    if (n_moves < rows * columns) return false;

    char sym = player->get_symbol();
    char opp_sym = (sym == 'S') ? 'U' : 'S';

    return points_map[sym] > points_map[opp_sym];
}

bool SUS_Board::is_lose(Player<char> *player) {
    if (n_moves < rows * columns) return false;

    char sym = player->get_symbol();
    char opp_sym = (sym == 'S') ? 'U' : 'S';

    return points_map[sym] < points_map[opp_sym];
}

bool SUS_Board::is_draw(Player<char> *player) {
    if (n_moves < rows * columns) return false;

    char sym = player->get_symbol();
    char opp_sym = (sym == 'S') ? 'U' : 'S';

    return points_map[sym] == points_map[opp_sym];
}

bool SUS_Board::game_is_over(Player<char> *player) {
    return n_moves == rows * columns;
}

//UI implementation


SUS_UI::SUS_UI() : UI("Welcome to FCAI SUS Game", 3) {
}



Player<char> *SUS_UI::create_player(string &name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
            << " player (" << symbol << "): " << name << "\n";
    return new Player<char>(name, symbol, type);
}


Player<char> **SUS_UI::setup_players() {
    Player<char> **players = new Player<char> *[2];
    vector<string> type_options = {"Human", "Computer"};

    string nameS = get_player_name("Player S");
    PlayerType typeS = get_player_type_choice("Player S", type_options);
    players[0] = create_player(nameS, 'S', typeS);


    string nameU = get_player_name("Player U");
    PlayerType typeU = get_player_type_choice("Player U", type_options);
    players[1] = create_player(nameU, 'U', typeU);

    return players;
}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
         cout<< player->get_name()<<"it's your turn! \n";
        cout<<"enter your move:\n";
        cout << "Row (0-2): ";
        x = getChoice(0, 2); //help function
        cout << "Column (0-2): ";
        y = getChoice(0, 2); //help function
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}
