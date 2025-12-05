#include"Help_Function.h"
#include "Ultimate.h"


int currentBoard = -1;

ultimateBoard::ultimateBoard() : Board(9, 9) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = BlankSymbol;
        }
    }
}

ultimateBoard::~ultimateBoard() {
}

int getCurrentBoard(int &x, int &y) {
    cout << x << " " << y << " " << (y % 3) + 1 + (x % 3) * 3 << endl;
    return (x / 3) * 3 + y / 3;
}


int getindexI(int &current) {
    int temp = current / 3;
    return temp * 3;
}

int getindexJ(int &current) {
    return (current % 3) * 3;
}


bool ultimateBoard::update_board(Move<char> *move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();
    if (!(0 <= x && x < rows && 0 <= y && y < columns)) return false;

    if (board[x][y] != BlankSymbol) return false;

    if (currentBoard == -1) {

        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == '#') board[row][col] = BlankSymbol;
            }
        }

        board[x][y] = symbol;
        currentBoard = getCurrentBoard(x, y);


        n_moves++;

  //lock all cells outside mini-boards
        int i = getindexI(currentBoard);
        int j = getindexJ(currentBoard);
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (!((row >= i && row < i + 3) && (col >= j && col < j + 3))
                    && board[row][col] == BlankSymbol ){

                    board[row][col] = blockSymbol;

                    }
            }
        }
        return true;

    }

    board[x][y] = symbol;
    n_moves++;

    return true;
}

bool ultimateBoard::check_the_mainboard(Player<char> *player) {
    int i = 0;
    int j = 0;

    char s = player->get_symbol();
    for (int a = i; a < i + 3; a++) {
        if (mainboard[a][j] == s
            && mainboard[a][j + 1] == s
            && mainboard[a][j + 2] == s)
            return true;
    }


    for (int a = j; a < j + 3; a++) {
        if (mainboard[i][a] == s &&
            mainboard[i + 1][a] == s &&
            mainboard[i + 2][a] == s)
            return true;
    }

    if (mainboard[i][j] == s
        && mainboard[i + 1][j + 1] == s
        && mainboard[i + 2][j + 2] == s
    )
        return true;

    if (mainboard[i][j + 2] == s
        && mainboard[i + 1][j + 1] == s
        && mainboard[i + 2][j] == s)
        return true;

    return false;
}

bool ultimateBoard::is_win(Player<char> *player) {
    if (n_moves >= rows * columns) return false;
    bool win = false;
    char s = player->get_symbol();

    //check for rows
    const int i = getindexI(currentBoard);
    const int j = getindexJ(currentBoard);

    for (int a = i; a < i + 3; a++) {
        if (board[a][j] == s
            && board[a][j + 1] == s
            && board[a][j + 2] == s) {
            win = true;
            break;
        };
    }


    for (int a = j; a < j + 3; a++) {
        if (board[i][a] == s &&
            board[i + 1][a] == s &&
            board[i + 2][a] == s) {
            win = true;
            break;
        }
    }

    if (board[i][j] == s
        && board[i + 1][j + 1] == s
        && board[i + 2][j + 2] == s
    )
        win = true;

    if (board[i][j + 2] == s
        && board[i + 1][j + 1] == s
        && board[i + 2][j] == s)
        win = true;


    if (win) {
        mainboard[i / 3][j / 3] = s;
        currentBoard = -1;
        for (int m = i; m < i + 3; m++) {
            for (int n = j; n < j + 3; n++) {
                if (board[m][n] == BlankSymbol) {
                    board[m][n] = '*';
                    n_moves++;
                }
            }
        }

     //Return cells available if win
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == blockSymbol) {
                    board[row][col] = BlankSymbol;
                }
            }
        }

        return check_the_mainboard(player);
    }

    if (n_moves % 9 == 0) {
        mainboard[i / 3][j / 3] = '0';
        currentBoard = -1;

        ////Return cells available if draw
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == blockSymbol) {
                    board[row][col] = BlankSymbol;
                }
            }
        }
        return check_the_mainboard(player);
    }


    return false;
}

bool ultimateBoard::is_lose(Player<char> *) {
    return false;
}

bool ultimateBoard::is_draw(Player<char> *player) {
    if (n_moves == rows * columns && !is_win(player)) return true;
    return false;
}

bool ultimateBoard::game_is_over(Player<char> *player) {
    if (n_moves < rows * columns) return false;
    return is_win(player) || is_draw(player) || is_lose(player);
}


ultimateUI::ultimateUI() : UI("Welcome to FCAI ultimate Game", 3) {
}

ultimateUI::~ultimateUI() {
}


Player<char> *ultimateUI::create_player(string &name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
            << " player (" << symbol << "): " << name << "\n";
    return new Player<char>(name, symbol, type);
}


Player<char> **ultimateUI::setup_players() {
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

Move<char> *ultimateUI::get_move(Player<char> *player) {
    if (currentBoard == -1) {
        int x = -1, y = -1;

        ultimateBoard *ub = dynamic_cast<ultimateBoard *>(player->get_board_ptr());
        if (player->get_type() == PlayerType::HUMAN) {
            cout << player->get_name() << " It 's your turn" << endl;
            cout << "\nPlease enter your move x (" << 0 << ":" << 8 << ")\n";
            x = getChoice(0, 8);
            cout << "\nPlease enter your move y (" << 0 << ":" << 8 << ")\n";
            y = getChoice(0, 8);
        } else if (player->get_type() == PlayerType::COMPUTER) {
            do {
                x = rand() % 9;
                y = rand() % 9;
            } while (ub->get_cell(x, y) != '.') ;
        }
        return new Move<char>(x, y, player->get_symbol());
    } else {
        int x = -1, y = -1;
        int i = getindexI(currentBoard);
        int j = getindexJ(currentBoard);
        ultimateBoard *ub = dynamic_cast<ultimateBoard *>(player->get_board_ptr());
        if (player->get_type() == PlayerType::HUMAN) {
            cout << player->get_name() << " It 's your turn" << endl;
            cout << "\nPlease enter your move x (" << i << ":" << i + 2 << ")\n";
            x = getChoice(i, i + 2);
            cout << "\nPlease enter your move y (" << j << ":" << j + 2 << ")\n";
            y = getChoice(j, j + 2);
        } else if (player->get_type() == PlayerType::COMPUTER) {
            x = i + rand() % 3;
            y = j + rand() % 3;
        }
        return new Move<char>(x, y, player->get_symbol());
    }
}
