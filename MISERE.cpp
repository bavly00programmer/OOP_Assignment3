//
// Created by M on 23/11/2025.
//

#include "MISERE.h"
#include<algorithm>
#include<cctype>
#include<iomanip>
#include<iostream>
#include "Help_Function.h"

using namespace std;
//-----------------------------------------------------------MISERE_Board implementation

MISERE_Board::MISERE_Board() : Board(3,3){
    //Initialize all cells with blank symbol
    for (auto& row:board)
        for (auto& cell:row)
            cell = blank_symbol;
}

MISERE_Board::~MISERE_Board() {

}

bool MISERE_Board::update_board(Move<char>* move) {
    int x=move->get_x();
    int y=move->get_y();
    char symbol=move->get_symbol();
    //check if position is valid
    if (x<0 || x>=rows || y<0 || y>=columns)
        return false;
    //check if cell is empty
    if (board[x][y]!=blank_symbol)
        return false;

    //update the board
    board[x][y]=symbol;
    n_moves++;
    return true;
}

int MISERE_Board::evaluate(char ai, char human) {
    Player<char> pAI("AI", ai , PlayerType::COMPUTER);
    Player<char> pHuman("Human", human, PlayerType::HUMAN);
    if (is_lose(&pAI)) return -10; //AI made 3 in row(bad)
    if (is_lose(&pHuman)) return +10; // Human made 3 (AI wins)
    return 0;
}

int MISERE_Board::minimax(char ai, char human, bool maximizing) {
    int score =  evaluate(ai,human);

    if (score ==10 || score == -10)
        return score;
    if (n_moves == 9)
        return 0;
    if (maximizing) {
        int best = -1000;
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                if (board[i][j] == '.') {
                    board[i][j] = ai;
                    n_moves++;

                    best = max(best, minimax(ai, human, false));
                    board[i][j]='.';
                    n_moves--;
                }
            }
        }
        return best;
    }else {
        int best = 1000;
        for (int i=0;i<3;i++) {
            for (int j=0;j<3;j++) {
                if (board[i][j] == '.') {
                    board[i][j] = human;
                    n_moves++;
                    best = max(best, minimax(ai, human, true));
                    board[i][j]='.';
                    n_moves--;
                }
            }
        }
        return best;
    }

}

pair<int,int> MISERE_Board::find_best_move(char ai, char human) {
    int bestValue = -1000;
    pair<int,int> bestMove= {-1,-1};
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (board[i][j] == '.') {
                board[i][j] = ai;
                n_moves++;
                int value = minimax(ai,human,false);
                board[i][j] = '.';
                n_moves--;
                if (value > bestValue) {
                    bestValue = value;
                    bestMove = {i,j};
                }
            }
        }
    }
    return bestMove;
}

bool MISERE_Board::is_win(Player<char>* player) {
    char symbol=player->get_symbol();
    char opponent_symbol = (symbol=='X')?'O':'X';

    //In Misère Tic-Tac-Toe, you WIN if the OPPONENT has three in a row
    // Check if opponent has three in any row
    for (int i=0;i<rows;i++) {
        if (board[i][0]==opponent_symbol && board[i][1]==symbol && board[i][2]==opponent_symbol)
            return true;
    }

    // check if opponent has three in any column
    for (int j =0;j<columns;j++) {
        if (board[0][j]==opponent_symbol && board[1][j]==symbol && board[2][j]==opponent_symbol)
            return true;
    }

    //check if opponent has three in anti-diagonal
    if (board[0][2]== opponent_symbol && board[1][1]==symbol && board[2][0]==opponent_symbol)
        return true;

    //check if opponent has three in diagonal
    if (board[0][0] && board[1][1]==symbol && board[2][2]==opponent_symbol)
        return true;
    return false;
}
bool MISERE_Board::is_lose(Player<char>* player) {
    char symbol=player->get_symbol();

    //In Misère Tic-Tac-Toe, you LOSE if YOU get three in a row
    // Check if player has three in any row
    for (int i=0;i<rows;i++) {
        if (board[i][0]==symbol && board[i][1]==symbol && board[i][2]==symbol)
            return true;
    }

    //check if player has three in any column
    for (int j=0;j<columns;j++) {
        if (board[0][j]==symbol && board[1][j]==symbol && board[2][j]==symbol)
            return true;
    }

    //check if player has three in main diagonal
    if (board[0][0]== symbol && board[1][1]==symbol && board[2][2]==symbol)
        return true;

    //check if player has three in anti-diagonal
    if (board[0][2]== symbol && board[1][1]==symbol && board[2][0]==symbol)
        return true;
    return false;
}
bool MISERE_Board::is_draw(Player<char>* player) {
    // Game is a draw if board is full and no one has won/lost according to misère rules
    return (n_moves == 9 && !is_win(player) && !is_lose(player));
}

bool MISERE_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

 //-------------------------------------MISERE_UI Implementation

MISERE_UI::MISERE_UI() :UI<char>("Welcome to FCAI misere tic-tac-toe game",1){

}
Player<char> *MISERE_UI::create_player(string &name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human":"computer") << " player: " << name << " (" << symbol << ")" << endl;
    return new Player<char>(name,symbol,type);
}

Move<char>* MISERE_UI::get_move(Player<char>* player) {
    int x = -1, y = -1;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << player->get_name() << ", enter your move:\n";
        cout << "Row (0-2): ";
x=getChoice(0 ,2);
        cout << "Column (0-2): ";
       y=getChoice(0 ,2);
    } else {
        // Computer move - smart ai mode
        MISERE_Board* b= dynamic_cast<MISERE_Board*>(player->get_board_ptr());

        char ai= player->get_symbol();
        char human= (ai == 'X')?'O':'X';
        auto best = b->find_best_move(ai,human);
        x = best.first;
        y = best.second;
        cout << "Computer chooses: (" << x << ", " << y << ")" << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}







