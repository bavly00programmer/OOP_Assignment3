//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>  // for toupper()
#include "NUM.h"

using namespace std;

//--------------------------------------- X_O_Board Implementation

NUM_Board::NUM_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}
bool Num_Board::if_valid_number_for_player(int num, Player<int>*player){
if (player->get_symbol()==1){//odd
    return(num==1||num==3||num==5||num==7||num==9);
}else{
    return(num==2||num==4||num==6||num==8);
}
}
bool NUM_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int num = move->get_symbol();
    
    //check if position is valid
    if(x < 0||x >= rows|| y < 0 ||y >= columns)
        return false;

    //check if cell empty
    if(board[x][y] != blank_symbol)
        return false;
    
    //check if number is in valid range and not used
    if(num<1 ||num>9|| find(used_numbers.begin(), used_numbers.end(), num) != used_numbers.end())
        return false;
    board[x][y] = num;
    used_numbers.push_back(num);
    n_moves++;
    return true;
}

bool NUM_Board::is_win(Player<int>* player) {
    //check rows
    for(int i =0;i<rows;i++){
        if(board[i][0] != blank_symbol && board[i][1]!= blank_symbol && board[i][2] != blank_symbol && board[i][0]+board[i][1]+board[i][2]==15)
            return true:
                }
    //check columns
    for(int j=0; j< columns;j++){
        if(board[0][j] != blank_symbol && board[1][j] != blank_symbol && board[2][j] != blank_symbol &&
            board[0][j] + board[1][j] + board[2][j] == 15)
            return true;
    }
    //check main diagonal
    if(board[0][0] != blank_symbol && board[1][1] != blank_symbol && board[2][2] != blank_symbol &&
        board[0][0] + board[1][1] + board[2][2] == 15) 
        return true;
}
    //check anti-diagonal
    if (board[0][2] != blank_symbol && board[1][1] != blank_symbol && board[2][0] != blank_symbol &&
        board[0][2] + board[1][1] + board[2][0] == 15)
        return true;

return false;
}
    
bool NUM_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool NUM_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

NUM_UI::NUM_UI() : UI<int>("Weclome to FCAI Numerical Tic-Tac-Toe Game", 3) {}

Player<int>* NUM_UI::create_player(string& name, int symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<int>(name, symbol, type);
}

Move<int>* NUM_UI::get_move(Player<int>* player) {
    int x, y,num;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout<< player-> get_name()<<", enter your move:\n";
        cout<<"Row (0-2);
        cin>>x;
        cout<<"Column (0-2): ";
        cin>>y;
        cout<<"Number: ";
        cin>> num;
    } else {
       //computer move - get the board pointer to access used numbers
        Board<int>* boardPtr = player->get_board_ptr();
        if(!boardPtr){
            //fallback if no board pointer
            x= rand()%3;
            y= rand()%3;

            // generate valid number based on player
             vector<int> valid_numbers = (player->get_symbol() == 1)? vector<int>{1, 3, 5, 7, 9} : vector<int>{2, 4, 6, 8};
            num = valid_numbers[rand() % valid_numbers.size()];
        }else{
            //try random valid moves until we find one that works
            bool valid_move = false;
            int attempts =0;
            vector<int> used_nums = boardPtr->get_used_numbers();

            while(!valid_move && attempts <50){
            x = rand() %3;
            y = rand() %3;

            //generate valid numbers based on player
            vector<int> valid_numbers;
            if(player->get_sympol() ==1){
              valid_numbers = {1, 3, 5, 7, 9};
             }else{
              valid_numbers = {2, 4, 6, 8};
             }
             num = valid_numbers[rand() % valid_numbers.size()];

            // Check if number is not used (simplified - in real implementation, 
            // you'd need to access the actual used numbers)
            valid_move = true; // Simplified for now
            attempts++;
            }
        }
 cout<<"Computer chooses: ("<<x<<", "<<y<<") with number "<<num<<endl;
    }
return new Move<int>(x, y, num);
}


                 
       
            
       



