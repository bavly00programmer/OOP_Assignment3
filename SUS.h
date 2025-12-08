//
// Created by Bavly on 11/24/2025.
//
/**
 * @file SUS.h
 * @brief SUS (Spell "SUS") Tic-Tac-Toe game implementation
 * @details Players place 'S', 'U', 'S' in sequence to spell "SUS" horizontally,
 *          vertically, or diagonally. Points are awarded for each "SUS" sequence.
 * @author Bavly
 * @date 11/24/2025
 */
#ifndef SUS_H
#define SUS_H
#include<map>
#include "BoardGame_Classes.h"

/**
 * @class SUS_Board
 * @brief Board implementation for SUS Tic-Tac-Toe
 * @extends Board<char>
 * 
 * Implements a 3x3 board where players alternate placing 'S' and 'U' to
 * spell "SUS". Points are awarded for each complete "SUS" sequence.
 */

class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.';///< Symbol representing empty cells
    static int SUS_Sequence;///< Static counter for total SUS sequences
    map<char, int> points_map;///< Map tracking points for each player
public:
 /**
     * @brief Default constructor
     * @details Initializes a 3x3 board with all cells empty
     */
    SUS_Board();
 /**
     * @brief Update the board with a player's move
     * @param move Pointer to the move containing position and symbol
     * @return true if move was successful, false otherwise
     * @details Awards points for any new "SUS" sequences created by the move
     */
    bool update_board(Move<char> *move) override;
/**
     * @brief Check if the player has won
     * @param player Pointer to the player to check
     * @return true if player has more points than opponent when board is full
     */
    bool is_win(Player<char> *player) override;
   /**
     * @brief Check if the game is a draw
     * @param player Pointer to the current player
     * @return true if board is full and players have equal points
     */
    bool is_draw(Player<char> *player) override;
 /**
     * @brief Check if the player has lost
     * @param player Pointer to the player to check
     * @return true if player has fewer points than opponent when board is full
     */
    bool is_lose(Player<char> *player) override;
  /**
     * @brief Check if the game is over
     * @param player Pointer to the current player
     * @return true if all cells are filled
     */
    bool game_is_over(Player<char> *player) override;
 /**
     * @brief Count points for a specific player
     * @param player Pointer to the player
     * @return Number of points (SUS sequences) for the player
     */
    int count_points_for(Player<char> *player);

    /**
     * @brief Count total SUS sequences on board
     * @param boardPtr Pointer to the board to check
     * @return Number of complete "SUS" sequences on the board
     */
     int count_sequences(SUS_Board *board);

};

/**
 * @class SUS_UI
 * @brief User Interface for SUS Tic-Tac-Toe game
 * @extends UI<char>
 */
class  SUS_UI: public UI<char> {

public:
/**
     * @brief Default constructor
     * @details Displays welcome message for SUS Tic-Tac-Toe
     */
    SUS_UI();
 /**
     * @brief Destructor
     */
    ~SUS_UI() {
    };

    /**
     * @brief Create a player instance
     * @param name Player's name
     * @param symbol Player's symbol ('S' or 'U')
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char> *create_player(string &name, char symbol, PlayerType type);
/**
     * @brief Get a move from a player
     * @param player Pointer to the current player
     * @return Pointer to the Move object
     */
    Move<char> *get_move(Player<char> *) override;
 /**
     * @brief Setup two players for the game
     * @return Array of 2 Player pointers
     * @details Sets up Player S and Player U (instead of X and O)
     */
    Player<char> **setup_players() override;
};


#endif //SUS_H
