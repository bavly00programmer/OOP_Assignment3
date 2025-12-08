//
// Created by Bavly on 11/25/2025.
//
/**
 * @file InfinityTic-Tac-Toe.h
 * @brief Infinity Tic-Tac-Toe game implementation
 * @details Tic-Tac-Toe with a 3x3 board where only the last 3 moves remain visible.
 *          Older moves disappear as new moves are made (circular buffer of moves).
 * @author Bavly
 * @date 11/25/2025
 */
#ifndef GAME10_H
#define GAME10_H

#include <deque>

#include "BoardGame_Classes.h"
using namespace std;
/**
 * @class infinity_Board
 * @brief Board implementation for Infinity Tic-Tac-Toe
 * @extends Board<char>
 * 
 * Implements a 3x3 board where only the last 3 moves remain on the board.
 * Older moves are automatically removed (FIFO - First In First Out).
 */

class infinity_Board : public Board<char> {
private:
    char blank_symbol = '.';///< Symbol representing empty cells

public:
    int count=0;///< Counter for tracking number of moves since last removal
    deque<pair<int, int>> MOVES;///< Queue to track move history
/**
     * @brief Default constructor
     * @details Initializes a 3x3 board with all cells empty
     */
   infinity_Board();
 /**
     * @brief Update the board with a player's move
     * @param move Pointer to the move containing position and symbol
     * @return true if move was successful, false otherwise
     * @details Removes oldest move when 4 moves have been made (keeps only last 3)
     */
    bool update_board(Move<char> *move) override;
/**
     * @brief Check if the player has won
     * @param player Pointer to the player to check
     * @return true if player has 3 pieces in a row with current visible pieces
     */
    bool is_win(Player<char> *player) override;
/**
     * @brief Check if the player has lost
     * @param player Pointer to the player to check
     * @return false (lose condition not used in this game)
     */
    bool is_lose(Player<char> *player)override { return false; };
/**
     * @brief Check if the player has lost
     * @param player Pointer to the player to check
     * @return false (lose condition not used in this game)
     */
    bool is_draw(Player<char> *player) override;
  /**
     * @brief Check if the game is over
     * @param player Pointer to the current player
     * @return true if game is over (win or draw)
     */
    bool game_is_over(Player<char> *player)override;
};

/**
 * @class infinity_UI
 * @brief User Interface for Infinity Tic-Tac-Toe game
 * @extends UI<char>
 */
class infinity_UI : public UI<char> {
public:
 /**
     * @brief Default constructor
     * @details Displays welcome message for Infinity Tic-Tac-Toe
     */
    infinity_UI();
 /**
     * @brief Destructor
     */
    ~infinity_UI() {
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
     * @details For human players, prompts for row and column input (0-2)
     *          For computer players, selects random position
     */
    virtual Move<char> *get_move(Player<char> *player);
};


#endif //GAME10_H
