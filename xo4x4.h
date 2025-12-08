/**
 * @file xo4x4.h
 * @brief 4x4 Moving Tic-Tac-Toe game implementation
 * @details Tic-Tac-Toe on a 4x4 board where pieces can move to adjacent empty cells.
 * @author Bavly
 */
#ifndef xo4x4_H
#define xo4x4_H

#include "BoardGame_Classes.h"
using namespace std;
/**
 * @class X_O_Board
 * @brief Board implementation for 4x4 Moving Tic-Tac-Toe
 * @extends Board<char>
 * 
 * Implements a 4x4 board where pieces start in fixed positions
 * and can move to adjacent empty cells (up, down, left, right).
 */
class X_O_Board : public Board<char> {
public:
    int start_x = -1; ///< Starting x position for move (from)
    int start_y = -1;///< Starting y position for move (from)
    char blank_symbol = '.'; ///< Symbol representing empty cells
/**
     * @brief Default constructor
     * @details Initializes board with starting positions for X and O players
     */
    X_O_Board();
 /**
     * @brief Get cell content at position
     * @param x Row index
     * @param y Column index
     * @return Character at specified position
     */
    char get_cell(int x, int y) const {
        return board[x][y];
    }
 /**
     * @brief Update the board with a player's move
     * @param move Pointer to the move containing destination and symbol
     * @return true if move was successful, false otherwise
     * @details Moves a piece from start_x,start_y to move position
     */
    bool update_board(Move<char> *move) override;
/**
     * @brief Check if the player has won
     * @param player Pointer to the player to check
     * @return true if player has 3 pieces in a row (any direction)
     */
    bool is_win(Player<char> *player) override;
 /**
     * @brief Check if the player has lost
     * @param player Pointer to the player to check
     * @return false (lose condition not used in this game)
     */
    bool is_lose(Player<char> *player) override { return false; };
/**
     * @brief Check if the game is a draw
     * @param player Pointer to the current player
     * @return true if no valid moves left for the player
     */
    bool is_draw(Player<char> *player) override;
 /**
     * @brief Check if the game is over
     * @param player Pointer to the current player
     * @return true if game is over (win or draw)
     */
    bool game_is_over(Player<char> *player) override;
};
/**
 * @class XO_UI
 * @brief User Interface for 4x4 Moving Tic-Tac-Toe game
 * @extends UI<char>
 */
class XO_UI : public UI<char> {
public:
 /**
     * @brief Default constructor
     * @details Displays welcome message for 4x4 Moving Tic-Tac-Toe
     */
    XO_UI();
 /**
     * @brief Destructor
     */
    ~XO_UI() {
    };
/**
     * @brief Create a player instance
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char> *create_player(string &name, char symbol, PlayerType type) override;
 /**
     * @brief Get a move from a player
     * @param player Pointer to the current player
     * @return Pointer to the Move object
     * @details For human players, prompts for "from" and "to" positions
     *          For computer players, finds a valid move automatically
     */
    Move<char> *get_move(Player<char> *player) override;
};


#endif //xo4x4_H
