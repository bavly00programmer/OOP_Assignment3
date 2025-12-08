//
// Created by Bavly on 11/27/2025.
//
/**
 * @file fourInRow.h
 * @brief Four-in-a-Row game (Connect Four) implementation
 * @details Classic Connect Four game where players drop pieces into columns.
 *          First player to get 4 in a row (horizontal, vertical, or diagonal) wins.
 * @author Bavly
 * @date 11/27/2025
 */

#ifndef FOURINROW_H
#define FOURINROW_H
#include "BoardGame_Classes.h"

/**
 * @class fourBoard
 * @brief Board implementation for Four-in-a-Row (Connect Four) game
 * @extends Board<char>
 * 
 * Implements a 6x7 board where pieces fall to the lowest available position
 * in the selected column.
 */

class fourBoard : public Board<char> {
private:
    char BlankSymbol = '.'; ///<symbol representing empty cells

public:
    /**
     * @brief Default constructor
     * @details Initializes a 6x7 board with all cells empty
     */
    fourBoard();
     /**
     * @brief Destructor
     */
    ~fourBoard();
 /**
     * @brief Update the board with a player's move
     * @param move Pointer to the move containing column and symbol
     * @return true if move was successful, false otherwise
     * @details Drops the piece to the lowest available row in the selected column
     */
    bool update_board(Move<char> *move) override;
 /**
     * @brief Check if the game is a draw
     * @param player Pointer to the current player (unused in this implementation)
     * @return true if board is full with no winner
     */
    bool is_draw(Player<char> *) override;
  /**
     * @brief Check if the player has lost
     * @param player Pointer to the player to check
     * @return true if player has lost (opponent has 4 in a row)
     */
    bool is_lose(Player<char> *) override;
    /**
     * @brief Check if the player has won
     * @param player Pointer to the player to check
     * @return true if player has 4 pieces in a row (horizontal, vertical, or diagonal)
     */

    bool is_win(Player<char> *) override;
/**
     * @brief Check if the game is over
     * @param player Pointer to the current player
     * @return true if game is over (win, lose, or draw)
     */
    bool game_is_over(Player<char> *) override;
};
/**
 * @class fourUI
 * @brief User Interface for Four-in-a-Row game
 * @extends UI<char>
 * 
 * Handles player setup and move input for the Four-in-a-Row game.
 */

class fourUI : public UI<char> {
private:
public:
 /**
     * @brief Default constructor
     * @details Displays welcome message for Four-in-a-Row game
     */
    fourUI();
 /**
     * @brief Destructor
     */
    ~fourUI();
 /**
     * @brief Create a player instance
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char> *create_player(string &name, char symbol, PlayerType type) override;
/**
     * @brief Setup two players for the game
     * @return Array of 2 Player pointers
     * @details Prompts for player names and types (Human/Computer)
     */
    Player<char> **setup_players() override;

    /**
     * @brief Get a move from a player
     * @param player Pointer to the current player
     * @return Pointer to the Move object
     * @details For human players, prompts for column input (0-6)
     *          For computer players, selects a random column
     */
    Move<char> *get_move(Player<char> *) override;
};

#endif //FOURINROW_H
