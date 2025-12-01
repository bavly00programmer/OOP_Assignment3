//
// Created by Bavly on 11/27/2025.
//

#include "OBgame.h"
#include"Help_Function.h"

ObstaclesBoard::ObstaclesBoard(): Board<char>(6, 6) {
    for (auto i = 0; i < 6; i++) {
        for (auto j = 0; j < 6; j++) {
            board[i][j] = BlankSymbol;
        }
    }
}

ObstaclesBoard::~ObstaclesBoard() {
}

bool ObstaclesBoard::update_board(Move<char> *move) {
    int y = move->get_y();
    int x = move->get_x();
    char symbol = move->get_symbol();

    if (board[x][y] != BlankSymbol
        || !(0 <= y && y < columns)
        || !(0 <= x && x < rows)) {
        return false;
    }


    board[x][y] = symbol;
    n_moves++;

    if (n_moves % 2 == 0 && n_moves >= 2 && n_moves - 2 <= (rows * columns)/2) {
        int i;
        int j;
        do {
            i = rand() % 6;
            j = rand() % 6;
        } while (board[i][j] != BlankSymbol);
        board[i][j] = ObstacleSymbol;

        int f;
        int h;
        do {
            f = rand() % 6;
            h = rand() % 6;
        } while (board[f][h] != BlankSymbol);
        board[f][h] = ObstacleSymbol;

        n_moves +=2;

    }
    return true;
}

bool ObstaclesBoard::is_win(Player<char> *player) {
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
                && board[i + 1][j] == s
                && board[i + 2][j] == s
                && board[i + 3][j] == s)
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

bool ObstaclesBoard::is_draw(Player<char> *player) {
    return (n_moves == rows * columns  && !is_win(player));
}

bool ObstaclesBoard::is_lose(Player<char> *player) {
    if (n_moves < rows * columns ) return false;
    return !is_win(player);
}

bool ObstaclesBoard::game_is_over(Player<char> *player) {
    if (n_moves < rows * columns) return false;
    return is_win(player) || is_draw(player) || is_lose(player);
}


//UI implementation


ObstaclesUI::ObstaclesUI() : UI("Welcome to FCAI 10.Obstacles Tic-Tac-Toe game", 3) {
}

ObstaclesUI::~ObstaclesUI() {
}

Player<char> *ObstaclesUI::create_player(string &name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
            << " player (" << symbol << "): " << name << "\n";
    return new Player<char>(name, symbol, type);
}


Player<char> **ObstaclesUI::setup_players() {
    Player<char> **players = new Player<char> *[2];
    vector<string> type_options = {"Human", "Computer"};

    string name1 = get_player_name("Player X");
    PlayerType type1 = get_player_type_choice("Player X", type_options);
    char sy1 = 'X';
    players[0] = create_player(name1, sy1, type1);

    string name2 = get_player_name("Player O");
    PlayerType type2 = get_player_type_choice("Player O", type_options);
    char sy2 = 'O';
    players[1] = create_player(name2, sy2, type2);
    return players;
}


Move<char> *ObstaclesUI::get_move(Player<char> *player) {
    int y =-1;
    int x =-1;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << "it's your turn! \n";
        cout << "enter your move:\n";
        cout << "Row (0-5)" << endl;
        x = getChoice(0, 5);
        cout << "Column (0-5)\n";
        y = getChoice(0, 5); //help function
    } else if (player->get_type() == PlayerType::COMPUTER) {
        y = rand() % player->get_board_ptr()->get_columns();
        x = rand() % player->get_board_ptr()->get_rows();
    }
    return new Move<char>(x, y, player->get_symbol());
}
