/**
 * @file NUM.h
 * @brief Numerical Tic-Tac-Toe game implementation
 * @details Tic-Tac-Toe with numbers instead of X and O.
 *          Odd player uses odd numbers (1,3,5,7,9), even player uses even numbers (2,4,6,8).
 *          Winner is first to have 3 numbers in a row summing to 15.
 * @author Bavly
 */
#ifndef NUM_H
#define NUM_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>
using namespace std;
/**
 * @class NUM_Board
 * @brief Board implementation for Numerical Tic-Tac-Toe
 * @extends Board<int>
 * 
 * Implements a 3x3 board where players place numbers instead of symbols.
 * Each number can only be used once in the entire game.
 */
class NUM_Board : public Board<int> {
private:
    int blank_symbol = 0;///< Value representing empty cells

public:
 /**
     * @brief Default constructor
     * @details Initializes a 3x3 board with all cells empty (0)
     */
    NUM_Board();
 /**
     * @brief Update the board with a player's move
     * @param move Pointer to the move containing position and number
     * @return true if move was successful, false otherwise
     * @details Checks if number is valid for player and not already used
     */
    bool update_board(Move<int> *move)override;
/**
     * @brief Check if the player has won
     * @param player Pointer to the player to check
     * @return true if player has 3 numbers in a row summing to 15
     */
    bool is_win(Player<int> *player)override;
 /**
     * @brief Check if the player has lost
     * @param player Pointer to the player to check
     * @return false (lose condition not used in this game)
     */
    bool is_lose(Player<int> *player)override { return false; };
/**
     * @brief Check if the game is a draw
     * @param player Pointer to the current player
     * @return true if all cells are filled with no winner
     */
    bool is_draw(Player<int> *player)override;
  /**
     * @brief Check if the game is over
     * @param player Pointer to the current player
     * @return true if game is over (win or draw)
     */
    bool game_is_over(Player<int> *player)override;
  /**
     * @brief Check if number is valid for given player
     * @param num Number to check
     * @param player Pointer to the player
     * @return true if number is valid for player (odd/even as appropriate)
     */
    bool is_valid_number_for_player(int num, Player<int> *player);
  /**
     * @brief Get list of used numbers
     * @return Vector of numbers already placed on board
     */
    vector<int> get_used_numbers()const;
 /**
     * @brief Get cell value at position
     * @param x Row index
     * @param y Column index
     * @return Value at specified position
     */
    int get_cell(int x, int y) const;

    /**
     * @brief Get blank symbol value
     * @return Value representing empty cell (0)
     */
    int get_blank_symbol() const;
};
/**
 * @class NUM_Player
 * @brief Player specialization for Numerical Tic-Tac-Toe
 * @extends Player<int>
 * 
 * Tracks whether player is odd or even and their available numbers.
 */
class NUM_Player : public Player<int> {
    string id; ///< even or odd
    vector<int> ValidNum;///< Valid numbers for this player

public:
 /**
     * @brief Constructor for NUM_Player
     * @param n Player name
     * @param id_ Player type ("odd" or "even")
     * @param t Player type (Human or Computer)
     */
    NUM_Player(const string &n, const string &id_, PlayerType t);
/**
     * @brief Get available numbers for player
     * @param used Vector of numbers already used in game
     * @return Vector of numbers still available to this player
     */
    vector<int> getValidNumbers(const vector<int> &used);
  /**
     * @brief Get player type ID
     * @return "odd" or "even"
     */
    string get_id() const;
};
/**
 * @class NUM_UI
 * @brief User Interface for Numerical Tic-Tac-Toe game
 * @extends UI<int>
 */
class NUM_UI : public UI<int> {

public:
/**
     * @brief Default constructor
     * @details Displays welcome message for Numerical Tic-Tac-Toe
     */
    NUM_UI();

    /**
     * @brief Destructor
     */
    ~NUM_UI() {
    };

 /**
     * @brief Create a player instance
     * @param name Player's name
     * @param symbol Player's symbol (1 for odd, 2 for even)
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<int> *create_player(string &name, int symbol, PlayerType type) override;
 /**
     * @brief Get a move from a player
     * @param player Pointer to the current player
     * @return Pointer to the Move object
     * @details For human players, prompts for position and number selection
     */
    Move<int> *get_move(Player<int> *player) override;
 /**
     * @brief Setup two players for the game
     * @return Array of 2 Player pointers
     * @details Sets up ODD and EVEN players instead of X and O
     */
    Player<int> **setup_players() override;
};

#endif // NUM_H


