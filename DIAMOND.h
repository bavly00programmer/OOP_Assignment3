//
// Created by M on 01/12/2025.
//
/**
 * @file DIAMOND.h
 * @brief Diamond Tic-Tac-Toe game implementation
 * @details Tic-Tac-Toe played on a diamond-shaped board with special win conditions.
 * @author M
 * @date 01/12/2025
 */
#ifndef DIAMOND_H
#define DIAMOND_H
#include "BoardGame_Classes.h"
#include <vector>
#include <utility>

using namespace std;

/**
 * @class DIAMOND_Board
 * @brief Board implementation for Diamond Tic-Tac-Toe
 * @extends Board<char>
 *
 * Implements a 5x5 board where only diamond-shaped cells are playable.
 * Win condition requires both a line of 3 and a line of 4.
 */

class DIAMOND_Board : public Board<char> {
private:
    char blank_symbol = '.';///< Symbol representing empty cells

public:
 /**
     * @brief Default constructor
     * @details Initializes a 5x5 board for diamond-shaped game
     */
   DIAMOND_Board();
/**
     * @brief Destructor
     */
   ~DIAMOND_Board() override {}
 /**
     * @brief Update the board with a player's move
     * @param move Pointer to the move containing position and symbol
     * @return true if move was successful, false otherwise
     */
bool update_board(Move<char>* move) override;
/**
     * @brief Check if the player has won
     * @param player Pointer to the player to check
     * @return true if player has both a line of 3 and a line of 4
     */
bool is_win(Player<char>* player) override;
 /**
     * @brief Check if the player has lost
     * @param player Pointer to the player to check
     * @return false (lose condition not used in this game)
     */
bool is_lose(Player<char>* player) override {return false;}
/**
     * @brief Check if the game is a draw
     * @param player Pointer to the current player
     * @return true if all diamond cells are filled with no winner
     */
bool is_draw(Player<char>* player) override;
/**
     * @brief Check if the game is over
     * @param player Pointer to the current player
     * @return true if game is over (win or draw)
     */
bool game_is_over(Player<char>* player) override;

//helper method for diamond board
 /**
     * @brief Check if cell is within diamond shape
     * @param x Row index
     * @param y Column index
     * @return true if position is valid diamond cell
     */
bool is_valid_cell(int x, int y) const;
 /**
     * @brief Check if player has a line of 3
     * @param player Pointer to the player to check
     * @return true if player has 3 in a row within diamond
     */
bool check_line_of_three(Player<char>* player) const;
 /**
     * @brief Check if player has a line of 4
     * @param player Pointer to the player to check
     * @return true if player has 4 in a row within diamond
     */
bool check_line_of_four(Player<char>* player) const;
 /**
     * @brief Evaluate board state for AI
     * @param ai AI player symbol
     * @param human Human player symbol
     * @return Score (+10 for AI win, -10 for human win, 0 otherwise)
     */
int evaluate(char ai, char human);
 /**
     * @brief Minimax algorithm for AI decision making
     * @param ai AI player symbol
     * @param human Human player symbol
     * @param alpha the best value that the maximizer currently can guarantee
     * @param beta the best value that the minimizer currently can guarantee
     * @param maximizing Whether it's the maximizing player's turn
     * @return Best score from current board state
     */
int minimax(char ai, char human, bool maximizing, int alpha, int beta ,int depth);
/**
     * @brief Find best move for AI using minimax
     * @param ai AI player symbol
     * @param human Human player symbol
     * @return Pair of (row, column) for best move
     */
pair<int,int> find_best_move(char ai, char human);
/**
     * @brief Get all valid diamond positions
     * @param positions Reference to vector to fill with positions
     */
void get_diamond_position(vector<pair<int, int>>& positions) const;
//fast helper that takes a char instead of a player  object
     bool check_win_fast(char symbol);


private:
///<pre-defined diamond positions in a 5x5 grid
static const vector<pair<int, int>> DIAMOND_CELLS;

};
/**
 * @class DIAMOND_UI
 * @brief User Interface for Diamond Tic-Tac-Toe game
 * @extends UI<char>
 */
class DIAMOND_UI : public UI<char> {
public:
/**
     * @brief Default constructor
     * @details Displays diamond shape diagram and welcome message
     */
DIAMOND_UI();
 /**
     * @brief Destructor
     */
~DIAMOND_UI() override {}
 /**
     * @brief Create a player instance
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
 Player<char>* create_player(string& name, char symbol,PlayerType type) override;
/**
     * @brief Get a move from a player
     * @param player Pointer to the current player
     * @return Pointer to the Move object
     * @details Uses smart AI with minimax for computer players
     */
 Move<char>* get_move(Player<char>* player) override;
/**
     * @brief Setup two players for the game
     * @return Array of 2 Player pointers
     */
 Player<char>** setup_players() override;

private:
/**
     * @brief Check if position is within diamond shape
     * @param x Row index
     * @param y Column index
     * @return true if position is valid diamond cell
     */
bool is_diamond_position(int x, int y) const;

};



#endif //DIAMOND_H

