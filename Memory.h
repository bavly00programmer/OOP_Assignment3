//
// Created by  HEBA on 12/4/2025.
//
/**
 * @file Memory.h
 * @brief Memory Tic-Tac-Toe game implementation
 * @details Tic-Tac-Toe where moves are hidden until a win condition is checked.
 *          Players make moves without seeing opponent's moves until game ends.
 * @author HEBA
 * @date 12/4/2025
 */
#ifndef MEMORY_H
#define MEMORY_H
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class memory_Board
 * @brief Board implementation for Memory Tic-Tac-Toe
 * @extends Board<char>
 * 
 * Implements a 3x3 board with two layers: visible board (shows '#') and 
 * hidden board (stores actual moves). Players cannot see opponent's moves.
 */
class memory_Board : public Board<char> {
private:
    char blank_symbol = '.';///< Symbol representing empty cells
    vector<vector<char>> hidden_board;///< Hidden board storing actual moves

public:
 /**
     * @brief Default constructor
     * @details Initializes both visible and hidden 3x3 boards
     */
    memory_Board();
/**
     * @brief Destructor
     */
    ~memory_Board()override;
 /**
     * @brief Update the board with a player's move
     * @param move Pointer to the move containing position and symbol
     * @return true if move was successful, false otherwise
     * @details Records move in hidden board, shows '#' on visible board
     */
    bool update_board(Move<char>* move)override;
 /**
     * @brief Check if the player has won
     * @param player Pointer to the player to check
     * @return true if player has 3 pieces in a row in hidden board
     */
    bool is_win(Player<char>* player)override;
  /**
     * @brief Check if the player has lost
     * @param player Pointer to the player to check
     * @return true if board is full and player hasn't won
     */
    bool is_lose(Player<char>*player) override;
 /**
     * @brief Check if the game is a draw
     * @param player Pointer to the current player
     * @return true if all cells are filled with no winner
     */
    bool is_draw(Player<char>* player)override;

    /**
     * @brief Check if the game is over
     * @param player Pointer to the current player
     * @return true if game is over (win or draw)
     */
    bool game_is_over(Player<char>* player)override;

};
/**
 * @class memory_UI
 * @brief User Interface for Memory Tic-Tac-Toe game
 * @extends UI<char>
 */
class memory_UI : public UI<char> {

public:
 /**
     * @brief Default constructor
     * @details Displays welcome message for Memory Tic-Tac-Toe
     */
    memory_UI();
  /**
     * @brief Destructor
     */
    ~memory_UI() override;

  /**
     * @brief Create a player instance
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */

    Player<char>* create_player(string& name, char symbol, PlayerType type)override;
 /**
     * @brief Get a move from a player
     * @param player Pointer to the current player
     * @return Pointer to the Move object
     */

     Move<char>* get_move(Player<char>* player) override;
};

#endif //MEMORY_H


