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
    {0,3},                                   // Row 0 (1 cell)
        {1,2}, {1,3}, {1,4},                     // Row 1 (3 cells)
        {2,1}, {2,2}, {2,3}, {2,4}, {2,5},       // Row 2 (5 cells)
        {3,0}, {3,1}, {3,2}, {3,3}, {3,4}, {3,5}, {3,6}, // Row 3 (7 cells)
        {4,1}, {4,2}, {4,3}, {4,4}, {4,5},       // Row 4 (5 cells)
        {5,2}, {5,3}, {5,4},                     // Row 5 (3 cells)
        {6,3}                                    // Row 6 (1 cell)
};
DIAMOND_Board::DIAMOND_Board() : Board(7,7){
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
if(x <0 || x >= 7 || y <0 || y >= 7)
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
    vector<pair<int, int>> positions;
    get_diamond_position(positions);

    for(const auto& start : positions) {
        int x = start.first;
        int y = start.second;

        // Check Horizontal (Right)
        if(is_valid_cell(x, y+3)) { // Only need to check the furthest cell validity effectively
            if (board[x][y] == s && board[x][y+1] == s && board[x][y+2] == s && board[x][y+3] == s)
                return true;
        }

        // Check Vertical (Down)
        if(is_valid_cell(x+3, y)) {
            if(board[x][y] == s && board[x+1][y] == s && board[x+2][y] == s && board[x+3][y] == s)
                return true;
        }

        // Check Diagonal (Down-Right)
        if(is_valid_cell(x+3, y+3)) {
            if(board[x][y] == s && board[x+1][y+1] == s && board[x+2][y+2] == s && board[x+3][y+3] == s)
                return true;
        }

        // Check Diagonal (Down-Left)
        if(is_valid_cell(x+3, y-3)) {
            if (board[x][y] == s && board[x+1][y-1] == s && board[x+2][y-2] == s && board[x+3][y-3] == s)
                return true;
        }
    }
    return false;
}
bool DIAMOND_Board::check_win_fast(char s) {
    //we reuse the logic but for a simple char's'
    vector<pair<int, int>> positions;
    get_diamond_position(positions);
    bool has_3=false;
    bool has_4=false;
    for(const auto& start : positions) {
        int x = start.first;
        int y = start.second;
        //check lines of3
        if (!has_3) {
            // Horizontal
            if(is_valid_cell(x, y+2) && board[x][y] == s && board[x][y+1] == s && board[x][y+2] == s) has_3 = true;
            // Vertical
            else if(is_valid_cell(x+2, y) && board[x][y] == s && board[x+1][y] == s && board[x+2][y] == s) has_3 = true;
            // Diagonal Down-Right
            else if(is_valid_cell(x+2, y+2) && board[x][y] == s && board[x+1][y+1] == s && board[x+2][y+2] == s) has_3 = true;
            // Diagonal Down-Left
            else if(is_valid_cell(x+2, y-2) && board[x][y] == s && board[x+1][y-1] == s && board[x+2][y-2] == s) has_3 = true;
        }
        // --- Check Lines of 4 ---
        if(!has_4) {
            // Horizontal
            if(is_valid_cell(x, y+3) && board[x][y] == s && board[x][y+1] == s && board[x][y+2] == s && board[x][y+3] == s) has_4 = true;
            // Vertical
            else if(is_valid_cell(x+3, y) && board[x][y] == s && board[x+1][y] == s && board[x+2][y] == s && board[x+3][y] == s) has_4 = true;
            // Diagonal Down-Right
            else if(is_valid_cell(x+3, y+3) && board[x][y] == s && board[x+1][y+1] == s && board[x+2][y+2] == s && board[x+3][y+3] == s) has_4 = true;
            // Diagonal Down-Left
            else if(is_valid_cell(x+3, y-3) && board[x][y] == s && board[x+1][y-1] == s && board[x+2][y-2] == s && board[x+3][y-3] == s) has_4 = true;
        }
        if (has_3 && has_4) return true;
        }
    return has_3 && has_4;
    }


//AI smart code
int DIAMOND_Board::evaluate(char ai, char human) {

    if (check_win_fast(ai)) return +10;
    if (check_win_fast(human)) return -10;

    return 0;
}
//minimax
int DIAMOND_Board::minimax(char ai, char human, bool maximizing, int alpha, int beta, int depth) {
    int score = evaluate(ai, human);

    // Terminal states (Win/Loss)
    if (score == 10 || score == -10)
        return score;

    // Terminal state (Draw/Full Board)
    if (n_moves >= DIAMOND_CELLS.size()) return 0;
    if (depth <= 0) return 0; //stop recursion here

    if (maximizing) {
        int best = -1000;
        for (auto &pos : DIAMOND_CELLS) {
            int x = pos.first;
            int y = pos.second;

            // Check if cell is empty
            if (board[x][y] == '.') {
                board[x][y] = ai;
                n_moves++;

                // Recurse with depth -1
                best = max(best, minimax(ai, human, false, alpha, beta,-1));

                // Backtrack
                board[x][y] = '.';
                n_moves--;

                // Alpha-Beta Pruning
                alpha = max(alpha, best);
                if (beta <= alpha) {
                    break; // Beta cutoff
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (auto &pos : DIAMOND_CELLS) {
            int x = pos.first;
            int y = pos.second;

            // Check if cell is empty
            if (board[x][y] == '.') {
                board[x][y] = human;
                n_moves++;

                best = min(best, minimax(ai, human, true, alpha, beta,-1));

                // Backtrack
                board[x][y] = '.';
                n_moves--;

                // Alpha-Beta Pruning
                beta = min(beta, best);
                if (beta <= alpha) {
                    break; // Alpha cutoff
                }
            }
        }
        return best;
    }
}
pair<int,int> DIAMOND_Board::find_best_move(char ai, char human) {
    int bestValue = -1000;
    pair<int,int> bestMove = {-1, -1};
    int alpha = -1000;
    int beta = 1000;
    int MAX_DEPTH = 3;

    for (auto &pos : DIAMOND_CELLS) {
        int x = pos.first;
        int y = pos.second;

        if (board[x][y] == '.') {
            board[x][y] = ai;
            n_moves++;

            // Call minimax with initial alpha-beta limits
            int moveVal = minimax(ai, human, false, alpha, beta, MAX_DEPTH);

            board[x][y] = '.';
            n_moves--;

            if (moveVal > bestValue) {
                bestValue = moveVal;
                bestMove = pos;
            }
            alpha= max(alpha, bestValue);
        }
    }
    return bestMove;
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
    {0,3},                                   // Row 0 (1 cell)
        {1,2}, {1,3}, {1,4},                     // Row 1 (3 cells)
        {2,1}, {2,2}, {2,3}, {2,4}, {2,5},       // Row 2 (5 cells)
        {3,0}, {3,1}, {3,2}, {3,3}, {3,4}, {3,5}, {3,6}, // Row 3 (7 cells)
        {4,1}, {4,2}, {4,3}, {4,4}, {4,5},       // Row 4 (5 cells)
        {5,2}, {5,3}, {5,4},                     // Row 5 (3 cells)
        {6,3}
};
  for(const auto& pos : diamond_cells) {
     if (pos.first == x && pos.second == y){
         return (abs(x-3)+abs(y-3))<=3;
}
}
return false;
}
DIAMOND_UI::DIAMOND_UI() : UI<char>("Welcome to Diamond Tic-Tac-Toe", 1) {
    cout << "    0 1 2 3 4 5 6\n";
    cout << "  0       * \n";
    cout << "  1     * * * \n";
    cout << "  2   * * * * * \n";
    cout << "  3 * * * * * * *\n";
    cout << "  4   * * * * * \n";
    cout << "  5     * * * \n";
    cout << "  6       * \n";
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
            cout << "Row(0-6, must be in diamond shape):";
            x = getChoice(0,6);
            cout <<"Column(0-6, must be in diamond shape):";
            y = getChoice(0,6);

            if (is_diamond_position(x,y)) {
                valid_move = true;
            }else {
                cout << "Invalid position! That's not part of the diamond shape.\n";
            }
        }
    }else {
        //computer player
       DIAMOND_Board* boardPtr  = dynamic_cast<DIAMOND_Board*>(player->get_board_ptr());

        char ai = player->get_symbol();
        char human = (ai == 'X')? 'O':'X';

        pair<int,int> bestMove = boardPtr->find_best_move(ai, human);

        x = bestMove.first;
        y = bestMove.second;

        cout<<"Computer chooses position: (" << x << ", " << y << ")\n";
    }
    return new Move<char>(x, y, player->get_symbol());
}





