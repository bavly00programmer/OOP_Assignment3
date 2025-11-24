//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <algorithm>
#include"Help_Function.h"
#include <cctype>  // for toupper()
#include "NUM.h"
#include"Help_Function.h"
using namespace std;

//--------------------------------------- Helper Function


//--------------------------------------- NUM_Board Implementation

NUM_Board::NUM_Board() : Board(3, 3) {
    for (auto &row: board)
        for (auto &cell: row)
            cell = blank_symbol;
}

bool NUM_Board::is_valid_number_for_player(int num, Player<int> *player) {
    if (player->get_symbol() == 1)
        return (num == 1 || num == 3 || num == 5 || num == 7 || num == 9);
    else
        return (num == 2 || num == 4 || num == 6 || num == 8);
}

bool NUM_Board::update_board(Move<int> *move) {
    int x = move->get_x();
    int y = move->get_y();
    int num = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
        return false;

    if (board[x][y] != blank_symbol)
        return false;

    if (num < 1 || num > 9 || find(used_numbers.begin(), used_numbers.end(), num) != used_numbers.end())
        return false;

    board[x][y] = num;
    used_numbers.push_back(num);
    n_moves++;
    return true;
}

bool NUM_Board::is_win(Player<int> *player) {
    // Check rows
    for (int i = 0; i < rows; i++)
        if (board[i][0] != blank_symbol && board[i][1] != blank_symbol && board[i][2] != blank_symbol &&
            board[i][0] + board[i][1] + board[i][2] == 15)
            return true;

    // Check columns
    for (int j = 0; j < columns; j++)
        if (board[0][j] != blank_symbol && board[1][j] != blank_symbol && board[2][j] != blank_symbol &&
            board[0][j] + board[1][j] + board[2][j] == 15)
            return true;

    // Check diagonals
    if (board[0][0] != blank_symbol && board[1][1] != blank_symbol && board[2][2] != blank_symbol &&
        board[0][0] + board[1][1] + board[2][2] == 15)
        return true;

    if (board[0][2] != blank_symbol && board[1][1] != blank_symbol && board[2][0] != blank_symbol &&
        board[0][2] + board[1][1] + board[2][0] == 15)
        return true;

    return false;
}

bool NUM_Board::is_draw(Player<int> *player) {
    return (n_moves == 9 && !is_win(player));
}

bool NUM_Board::game_is_over(Player<int> *player) {
    return is_win(player) || is_draw(player);
}

vector<int> NUM_Board::get_used_numbers() const {
    return used_numbers;
}

int NUM_Board::get_cell(int x, int y) const {
    return board[x][y];
}

int NUM_Board::get_blank_symbol() const {
    return blank_symbol;
}

//--------------------------------------- NUM_Player Implementation

NUM_Player::NUM_Player(const std::string &n, const std::string &id_, PlayerType t)
    : Player<int>(n, (id_ == "odd" ? 1 : 2), t), id(id_) {
    if (id == "odd")
        ValidNum = {1, 3, 5, 7, 9};
    else
        ValidNum = {2, 4, 6, 8};
}

vector<int> NUM_Player::getValidNumbers(const vector<int> &used) {
    vector<int> available;
    for (int n: ValidNum)
        if (find(used.begin(), used.end(), n) == used.end())
            available.push_back(n);
    return available;
}

string NUM_Player::get_id() const {
    return id;
}

//--------------------------------------- NUM_UI Implementation

NUM_UI::NUM_UI() : UI<int>("Welcome to FCAI Numerical Tic-Tac-Toe Game", 3) {
}


// Override create_player
Player<int> *NUM_UI::create_player(string &name, int symbol, PlayerType type) {
    string id = (symbol == 1) ? "odd" : "even";
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
            << " player (" << id << "): " << name << "\n";
    return new NUM_Player(name, id, type);
}

// Override setup_players to replace X/O with ODD/EVEN
Player<int> **NUM_UI::setup_players() {
    Player<int> **players = new Player<int> *[2];
    vector<string> type_options = {"Human", "Computer"};

    string nameOdd = get_player_name("Player ODD");
    PlayerType typeOdd = get_player_type_choice("Player ODD", type_options);
    players[0] = create_player(nameOdd, 1, typeOdd); // 1 = odd

    string nameEven = get_player_name("Player EVEN");
    PlayerType typeEven = get_player_type_choice("Player EVEN", type_options);
    players[1] = create_player(nameEven, 2, typeEven); // 2 = even

    return players;
}

Move<int> *NUM_UI::get_move(Player<int> *player) {
    int x = -1, y = -1, num = -1;

    NUM_Board *numBoard = dynamic_cast<NUM_Board *>(player->get_board_ptr());
    NUM_Player *numPlayer = dynamic_cast<NUM_Player *>(player);

    vector<int> used_numbers = numBoard ? numBoard->get_used_numbers() : vector<int>{};

    if (player->get_type() == PlayerType::HUMAN && numPlayer) {
        cout << "\n" << player->get_name() << " (" << numPlayer->get_id() << ") it's your turn.\n";
        cout << "Available numbers: ";
        vector<int> valid = numPlayer->getValidNumbers(used_numbers);
        for (int v: valid)
            cout << v << " ";
        cout << "\n";

        cout << "Row (0-2): ";
        x = getChoice(0, 2); //help function
        cout << "Column (0-2): ";
        y = getChoice(0, 2); //help function

        while (true) {
            cout << "Choose a number from available: ";
            num = getNUmber(); //help function
            if (find(valid.begin(), valid.end(), num) != valid.end()) break;
            cout << "Invalid number. Try again.\n";
        }
    } else if (numPlayer) {
        vector<int> valid = numPlayer->getValidNumbers(used_numbers);

        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (numBoard && numBoard->get_cell(x, y) != numBoard->get_blank_symbol());

        num = valid[rand() % valid.size()];
        cout << "Computer chooses: (" << x << ", " << y << ") with number " << num << endl;
    }

    return new Move<int>(x, y, num);
}
