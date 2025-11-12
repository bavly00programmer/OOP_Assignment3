/**
 * @file XO_Classes.h
 * @brief Defines the X-O (Tic-Tac-Toe) specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `X_O_Board`: A specialized board class for the Tic-Tac-Toe game.
 * - `XO_UI`: A user interface class tailored to X-O game setup and player interaction.
 */

#ifndef NUM_CLASSES_H
#define NUM_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class NUM_Board
 * @brief Represents the Tic-Tac-Toe game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for the Tic-Tac-Toe (X-O) game, including
 * move updates, win/draw detection, and display functions.
 *
 * @see Board
 */
class NUM_Board : public Board<int> {
private:
    int blank_symbol = 0;
    ///< Character used to represent an empty cell on the board.

public:
    /**
     * @brief Default constructor that initializes a 3x3 X-O board.
     */
    NUM_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move coordinates and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<int>* move);

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player being checked.
     * @return true if the player has a winning line, false otherwise.
     */
    bool is_win(Player<int>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false (not used in X-O logic).
     */
    bool is_lose(Player<int>*) { return false; };

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all cells are filled and no player has won, false otherwise.
     */
    bool is_draw(Player<int>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<int>* player);
};


/**
 * @class NUM_UI
 * @brief User Interface class for the X-O (Tic-Tac-Toe) game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * X-O�specific functionality for player setup and move input.
 *
 * @see UI
 */
class NUM_UI : public UI<int> {
public:
    /**
     * @brief Constructs an XO_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message "FCAI X-O".
     */
    NUM_UI();

    /**
     * @brief Destructor for XO_UI.
     */
    ~NUM_UI() {};

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object representing the player's action.
     */
    virtual Move<int>* get_move(Player<int>* player);
};

#endif // NUM.H
