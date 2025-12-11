/**
 * @file Ultimate.h
 * @brief Ultimate Tic-Tac-Toe game implementation
 * @details 9 Tic-Tac-Toe boards arranged in a 3x3 grid, forming a meta-game.
 *          Winning a small board gives control of that cell in the main board.
 * @author Bavly
 */
#ifndef ULTIMATE_H
#define ULTIMATE_H

#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;


const char BlankSymbol = '.';///< Symbol representing empty cells
const char blockSymbol = '#';///< Symbol representing blocked cells
const char invaledSymbol = 'x';///< Symbol representing invalid cells


/**
 * @brief Get the current small board index based on move position
 * @param x Row index of move
 * @param y Column index of move
 * @return Index of small board (0-8)
 */

int getCurrentBoard(int &x, int &y);
/**
 * @brief Get starting row index for a small board
 * @param current Small board index (0-8)
 * @return Starting row index for that board
 */
int getindexI(int &current);
/**
 * @brief Get starting column index for a small board
 * @param current Small board index (0-8)
 * @return Starting column index for that board
 */
int getindexJ(int &current);

// =========================
// ==       ultimateBoard ==
// =========================
/**
 * @class ultimateBoard
 * @brief Board implementation for Ultimate Tic-Tac-Toe
 * @extends Board<char>
 * 
 * Implements a 9x9 board divided into 9 smaller 3x3 boards.
 * Winning a small board gives control of that cell in the 3x3 meta-board.
 */
class ultimateBoard : public Board<char> {
private:
    char mainboard[3][3] = {
        {BlankSymbol, BlankSymbol, BlankSymbol},
        {BlankSymbol, BlankSymbol, BlankSymbol},
        {BlankSymbol, BlankSymbol, BlankSymbol}
    };///< Meta-board tracking winners of each small board

public:
 /**
     * @brief Default constructor
     * @details Initializes a 9x9 ultimate board
     */
    ultimateBoard();
 /**
     * @brief Destructor
     */
    ~ultimateBoard();

    /**
     * @brief Update the board with a player's move
     * @param move Pointer to the move containing position and symbol
     * @return true if move was successful, false otherwise
     * @details Restricts moves to specific small board based on previous move
     */
    bool update_board(Move<char> *move) override;
  /**
     * @brief Check if the player has won
     * @param player Pointer to the player to check
     * @return true if player wins a small board and then the meta-board
     */
    bool is_win(Player<char> *player) override;
/**
     * @brief Check if the player has lost
     * @param player Pointer to the player to check
     * @return false (lose condition handled by opponent's win)
     */
    bool is_lose(Player<char> *player) override;
 
    /**
     * @brief Check if the game is a draw
     * @param player Pointer to the current player
     * @return true if all cells are filled with no meta-board winner
     */
    bool is_draw(Player<char> *player) override;
  
    /**
     * @brief Check if the game is over
     * @param player Pointer to the current player
     * @return true if game is over (win or draw)
     */
    bool game_is_over(Player<char> *player) override;
/**
     * @brief Check if player has won the meta-board
     * @param player Pointer to the player to check
     * @return true if player has 3 in a row on the meta-board
     */
    bool check_the_mainboard(Player<char> *player);

    /**
     * @brief Get cell content at position
     * @param x Row index
     * @param y Column index
     * @return Character at specified position
     */
    char get_cell(int &x,int&y) {
        return board[x][y];
    }
};


// =========================
// ==        ultimateUI   ==
// =========================
/**
 * @class ultimateUI
 * @brief User Interface for Ultimate Tic-Tac-Toe game
 * @extends UI<char>
 */
class ultimateUI : public UI<char> {
public:
 /**
     * @brief Default constructor
     * @details Displays welcome message for Ultimate Tic-Tac-Toe
     */
    ultimateUI();

    /**
     * @brief Destructor
     */
    ~ultimateUI();
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
     * @details Restricts input based on which small board is active
     */
    Move<char> *get_move(Player<char> *player) override;
};

#endif // ULTIMATE_H
