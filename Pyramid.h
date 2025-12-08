//
// Created by HEBA on 12/1/2025.
//
/**
 * @file Pyramid.h
 * @brief Pyramid Tic-Tac-Toe game implementation
 * @details Tic-Tac-Toe played on a pyramid-shaped board with restricted cells.
 * @author HEBA
 * @date 12/1/2025
 */

#ifndef PYRAMID_H
#define PYRAMID_H
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class pyramid_Board
 * @brief Board implementation for Pyramid Tic-Tac-Toe
 * @extends Board<char>
 * 
 * Implements a 3x5 board where only pyramid-shaped cells are playable.
 * '#' cells are blocked/invalid positions.
 */
class pyramid_Board : public Board<char> {
private:
    char blank_symbol = '.';///< Symbol representing empty cells

public:
/**
     * @brief Default constructor
     * @details Initializes a 3x5 board with pyramid shape (blocked cells marked with '#')
     */
    pyramid_Board();
 /**
     * @brief Update the board with a player's move
     * @param move Pointer to the move containing position and symbol
     * @return true if move was successful, false otherwise
     * @details Checks if position is valid and within pyramid shape
     */
    bool update_board(Move<char>* move)override;
/**
     * @brief Check if the player has won
     * @param player Pointer to the player to check
     * @return true if player has 3 pieces in a line within pyramid shape
     */

    bool is_win(Player<char>* player)override;
 /**
     * @brief Check if the player has lost
     * @param player Pointer to the player to check
     * @return false (this game doesn't have a lose condition)
     */
    bool is_lose(Player<char>*) {
        return false;
    };
/**
     * @brief Check if the game is a draw
     * @param player Pointer to the current player
     * @return true if all pyramid cells are filled with no winner
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
 * @class pyramid_UI
 * @brief User Interface for Pyramid Tic-Tac-Toe game
 * @extends UI<char>
 */
class pyramid_UI : public UI<char> {
public:
 /**
     * @brief Default constructor
     * @details Displays welcome message for Pyramid Tic-Tac-Toe
     */
    pyramid_UI();
/**
     * @brief Destructor
     */
    ~pyramid_UI() {};
 /**
     * @brief Create a player instance
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Setup two players for the game
     * @return Array of 2 Player pointers
     */

    Player<char> **setup_players() override;
 /**
     * @brief Get a move from a player
     * @param player Pointer to the current player
     * @return Pointer to the Move object
     * @details For human players, prompts for row and column input
     *          For computer players, selects random valid position
     */
    virtual Move<char>* get_move(Player<char>* player)override;
};

#endif //PYRAMID_H

