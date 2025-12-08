//
// Created by Bavly on 11/27/2025.
//
/**
 * @file OBgame.h
 * @brief Obstacles Tic-Tac-Toe game implementation
 * @details Tic-Tac-Toe with randomly placed obstacles that block cells.
 * @author Bavly
 * @date 11/27/2025
 */

#ifndef OBgame_H
#define OBgame_H
#include "BoardGame_Classes.h"

/**
 * @class ObstaclesBoard
 * @brief Board implementation for Obstacles Tic-Tac-Toe
 * @extends Board<char>
 * 
 * Implements a 6x6 board where obstacles ('#') are randomly placed
 * every 2 moves, blocking those cells from play.
 */
class ObstaclesBoard: public Board<char> {
private:
    char BlankSymbol = '.'; ///< Symbol representing empty cells
    char ObstacleSymbol = '#';///< Symbol representing obstacle cells

public:
/**
     * @brief Default constructor
     * @details Initializes a 6x6 board with all cells empty
     */
    ObstaclesBoard();
/**
     * @brief Destructor
     */
    ~ObstaclesBoard()override;
 /**
     * @brief Update the board with a player's move
     * @param move Pointer to the move containing position and symbol
     * @return true if move was successful, false otherwise
     * @details Places obstacles every 2 moves after the first move
     */
    bool update_board(Move<char> *move) override;
/**
     * @brief Check if the game is a draw
     * @param player Pointer to the current player
     * @return true if board is full of no winner
     */
    bool is_draw(Player<char> *player) override;
 /**
     * @brief Check if the player has lost
     * @param player Pointer to the player to check
     * @return true if player has lost (opponent has 4 in a row)
     */
    bool is_lose(Player<char> *player) override;
/**
     * @brief Check if the player has won
     * @param player Pointer to the player to check
     * @return true if player has 4 pieces in a row
     */
    bool is_win(Player<char> *player) override;
 /**
     * @brief Check if the game is over
     * @param player Pointer to the current player
     * @return true if game is over (win, lose, or draw)
     */
    bool game_is_over(Player<char> *player) override;
};


/**
 * @class ObstaclesUI
 * @brief User Interface for Obstacles Tic-Tac-Toe game
 * @extends UI<char>
 */
class ObstaclesUI : public UI<char> {
private:
public:
 /**
     * @brief Default constructor
     * @details Displays welcome message for Obstacles Tic-Tac-Toe
     */
    ObstaclesUI();
 /**
     * @brief Destructor
     */
    ~ObstaclesUI()override;
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
     */
    Player<char> **setup_players() override;
 /**
     * @brief Get a move from a player
     * @param player Pointer to the current player
     * @return Pointer to the Move object
     */
    Move<char> *get_move(Player<char> *player) override;
};

#endif //OBgame_H
