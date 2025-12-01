//
// Created by Bavly on 11/27/2025.
//

#include "fourInRow.h"
#include"Help_Function.h"

fourBoard::fourBoard(): Board<char>(6, 7) {
    for (auto i = 0; i < 6; i++) {
        for (auto j = 0; j < 7; j++) {
            board[i][j] = BlankSymbol;
        }
    }
}

fourBoard::~fourBoard() {
}

bool fourBoard::update_board(Move<char> *move) {
    int y = move->get_y();
    int x = -1;
    char symbol = move->get_symbol();
    if (board[0][y] != BlankSymbol || !(0 <= y && y < columns)) {
        return false;
    }
    for (int i = rows - 1; i >= 0; i--) {
        if (board[i][y] == BlankSymbol) {
            x = i;
            break;
        }
    }

    if (x == -1)return false;

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool fourBoard::is_win(Player<char> *player) {
    if (n_moves >= rows * columns) return false;
    char s = player->get_symbol();
    //check for rows


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j + 3 < columns; j++) {
            if (board[i][j] == s
                && board[i][j + 1] == s
                && board[i][j + 2] == s
                && board[i][j + 3] == s)
                return true;
        }
    }

    //check for columns
    for (int i = 0; i + 3 < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == s
                && board[i+1][j] == s
                && board[i+2][j] == s
                && board[i+3][j] == s)
                return true;
        }
    }

    //check for diagonals
    for (int i = 0; i + 3 < rows; i++) {
        for (int j = columns - 1; j - 3 >= 0; j--) {
            if (board[i][j] == s
                && board[i + 1][j - 1] == s
                && board[i + 2][j - 2] == s
                && board[i + 3][j - 3] == s)
                return true;
        }
    }

    for (int i = 0; i + 3 < rows; i++) {
        for (int j = 0; j + 3 < columns; j++) {
            if (board[i][j] == s
              && board[i+1][j+1] == s
              && board[i+2][j+2] == s
              && board[i+3][j+3] == s)
                return true;
        }
    }


    return false;
}

bool fourBoard::is_draw(Player<char> *player) {
    return (n_moves == rows * columns && !is_win(player));
}

bool fourBoard::is_lose(Player<char> *player) {
    if (n_moves < rows * columns) return false;
    return !is_win(player);
}

bool fourBoard::game_is_over(Player<char> *player) {
    if (n_moves < rows * columns) return false;
    return is_win(player) || is_draw(player) || is_lose(player);
}


//UI implementation


fourUI::fourUI() : UI("Welcome to FCAI four in row Game", 3) {
}
fourUI::~fourUI() {

}

Player<char> *fourUI::create_player(string &name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
            << " player (" << symbol << "): " << name << "\n";
    return new Player<char>(name, symbol, type);
}


Player<char> **fourUI::setup_players() {
    Player<char> **players = new Player<char> *[2];
    vector<string> type_options = {"Human", "Computer"};

    string name1 = get_player_name("Player X");
    PlayerType type1 = get_player_type_choice("Player X", type_options);
    char sy1 ='X';
    players[0] = create_player(name1, sy1, type1);

    string name2 = get_player_name("Player O");
    PlayerType type2 = get_player_type_choice("Player O", type_options);
    char sy2 = 'O';
    players[1] = create_player(name2, sy2, type2);
    return players;
}


Move<char> *fourUI::get_move(Player<char> *player) {
    int y;
    int x = 0;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << "it's your turn! \n";
        cout << "enter your move:\n";
        cout << "Column (0-6)\n";
        y = getChoice(0, 6); //help function
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}
