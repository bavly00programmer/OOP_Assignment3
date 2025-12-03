//
// Created by M on 01/12/2025.
//
#include "DIAMOND.h"
#include "Help_function.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
//Diamond shape position in a 5x5 grid
const vector<pair<int, int>> DIAMOND_Board::DIAMOND_CELLS = {
{0,2},//top
{1,1}, {1,2}, {1,3},//second row
{2,0}, {2,1},{2,2}, {2,3},{2,4}, //middle row
{3,1}, {3,2}, {3,3}, //fourth row
{4,2}  //bottom
};
DIAMOND_Board::DIAMOND_Board() : Board(5,5){
//Initialize all cells with blank symbol
for(auto& row : board)
   for (auto& cell : row)
          cell = blank_symbol;
}
bool DIAMOND_Board::is_valid_cell(int x, int y) const {
//check if position is within diamond shape
for(const auto& pos : DIAMOND_CELLS) {
    if(pos.first == x && pos.second == y){
return true;
}
}
return false;
}
void DIAMOND_Board::get_diamond_position(vector<pair<int, int>>& positions) const {
positions = DIAMOND_CELLS;
}
bool DIAMOND_Board::update_board(Move<char>* move){
int x = move->get_x();
int y = move->get_y();
char symbol = move->get_symbol();

//check if position is valid and within diamond shape
if(x <0 || x >= 5 || y <0 || y >= 5)
return false;
if(!is_valid_cell(x,y))
return false;

//check if cell is empty
if(board[x][y] != blank_symbol)
return false;

//update the board
board[x][y] = symbol;
n_moves++;
return true;
}

bool DIAMOND_Board::check_line_of_three(Player<char>* player) const {
char s = player->get_symbol();

//check horizontal lines of 3 within diamond
vector<pair<int, int>> positions;
get_diamond_position(positions);

for(const auto& start : positions) {
int x = start.first;
int y = start.second;

//check horizontal right
if(is_valid_cell(x,y) && is_valid_cell(x,y+1) && is_valid_cell(x,y+2) && is_valid_cell(x,y+3)){
if (board[x][y] == s && board[x][y+1] == s && board[x][y+2] == s)
return true;
}

//check vertical down
if(is_valid_cell(x,y) && is_valid_cell(x+1,y) && is_valid_cell(x+2,y)){
 if(board[x][y] == s && board[x+1][y] == s && board[x+2][y] == s)
return true;
}

//check diagonal down-right
if(is_valid_cell(x,y) && is_valid_cell(x+1,y+1) && is_valid_cell(x+2,y+2)){
 if(board[x][y] == s && board[x+1][y+1] == s && board[x+2][y+2] == s)
return true;
}

//check diagonal down-left
if(is_valid_cell(x,y) && is_valid_cell(x+1,y-1) && is_valid_cell(x+2,y-2)){
 if (board[x][y] == s && board[x+1][y-1] == s && board[x+2][y-2] == s)
return true;
}
}
return false;
}

bool DIAMOND_Board::check_line_of_four(Player<char>* player)const {
char s = player->get_symbol();

//check for lines of 4 within diamond
//these are only possible in the middle row and middle column

//check middle row horizontal
if (board[2][0] == s && board[2][1] == s && board[2][2] == s && board[2][3] == s)
return true;
if(board[2][1] == s && board[2][2] == s && board[2][3] == s && board[2][4] == s)
return true;

//check middle column vertical
if(board[0][2] ==s && board[1][2]==s && board[2][2] == s && board[3][2] == s)
return true;
if (board[1][2] == s && board[2][2] == s && board[3][2] == s && board[4][2] == s)
return true;

//check diagonal only the diamond portion
if (board [1][1] == s && board [2][2] ==s && board [3][3] == s)
return false; //this is only 3 cells in diamond shape

if (board[1][3] == s && board[2][2] ==s && board[3][1] == s)
return false;  //this is only 3 cells in diamond shape

//check for L-shaped or other patterns of 4 within diamond
if(board[1][1] == s && board[1][2] == s && board[1][3] == s && board[2][2] == s)
return true;

if(board[1][1] == s && board[2][1] == s && board[3][1] == s && board[2][2] == s)
return true;

return false;

}
bool DIAMOND_Board::is_win(Player<char>* player) {
   return check_line_of_three(player) && check_line_of_four(player);
}
bool DIAMOND_Board::is_draw(Player<char>* player) {
   return (n_moves >= DIAMOND_CELLS.size() && !is_win(player));
}
bool DIAMOND_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
//DIAMOND_UI Implementation
bool DIAMOND_UI::is_diamond_position(int x, int y) const {
//Same diamond positions as in the board
vector<pair<int, int>> diamond_cells = {
    {0, 2},
    {1, 1}, {1, 2}, {1, 3},
    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4},
    {3, 1}, {3, 2}, {3, 3},
    {4, 2}
};
  for(const auto& pos : diamond_cells) {
     if (pos.first == x && pos.second == y){
         return true;
}
}
return false;
}
DIAMOND_UI::DIAMOND_UI() : UI<char>("Welcome to Diamond Tic-Tac-Toe", 1) {
    cout << "    0 1 2 3 4\n";
    cout << "  0     *\n";
    cout << "  1   * * *\n";
    cout << "  2 * * * * *\n";
    cout << "  3   * * *\n";
    cout << "  4     *\n";
    cout << "(* marks valid positions)\n\n";
}
Player<char>* DIAMOND_UI::create_player(string& name, char symbol, PlayerType type) {
cout << "Crating" << (type == PlayerType::HUMAN ? "Human" : "Computer") << " Player: " << name << " (" << symbol << ")\n";
return new Player<char>(name, symbol, type);
}
Player<char> **DIAMOND_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = {"Human", "Computer"};

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X" , type_options);
    players[0] = create_player(nameX , 'X' , typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O" , type_options);
    players[1] = create_player(nameO , 'O' , typeO);
    return players;
}

Move<char> *DIAMOND_UI::get_move(Player<char>* player) {
    int x=-1;
    int y=-1;

    if (player->get_type() == PlayerType::HUMAN) {
        bool valid_move = false;
        while(!valid_move) {
            cout << player->get_name() << " (" << player->get_symbol() << "), enter your move:\n";
            cout << "Row(0-4, must be in diamond shape):";
            x = getChoice(0,4);
            cout <<"Column(0-4, must be in diamond shape):";
            y = getChoice(0,4);

            if (is_diamond_position(x,y)) {
                valid_move = true;
            }else {
                cout << "Invalid position! That's not part of the diamond shape.\n";
            }
        }
    }else {
        //computer player - choose random diamond position
        vector<pair<int,int>> diamond_cells = {
            {0, 2},
            {1, 1}, {1, 2}, {1, 3},
            {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4},
            {3, 1}, {3, 2}, {3, 3},
            {4, 2}
        };
        //check for empty cells
        DIAMOND_Board* boardPtr = dynamic_cast<DIAMOND_Board*>(player->get_board_ptr());
        if (boardPtr) {
            //find all empty cells
            vector<pair<int,int>> empty_cells;
            for (const auto& pos : diamond_cells) {
                if (boardPtr->get_board_matrix()[pos.first][pos.second] == '.') {
                    empty_cells.push_back(pos);
                }
            }
            if (!empty_cells.empty()) {
                int index = rand() % empty_cells.size();
                x= empty_cells[index].first;
                y= empty_cells[index].second;
            }else{
                // all cells filled
                x=0; y=2;
            }
        }else {
            //fallback
            x= rand()%5;
            y= rand()%5;
            //make sure it's diamond pos
            while (!is_diamond_position(x,y)) {
                x=rand()%5;
                y=rand()%5;
            }
        }
        cout<<"Computer chooses position: (" << x << ", " << y << ")\n";
    }
    return new Move<char>(x, y, player->get_symbol());
}





