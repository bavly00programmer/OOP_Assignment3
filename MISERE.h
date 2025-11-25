//
// Created by M on 23/11/2025.
//

#ifndef MISERE_H
#define MISERE_H
#include "BoardGame_Classes.h"

using namespace std;


/**
 * @class MISERE_Board
 * @brief represents the Misere tic-tac-toe game board.
 * @see Board
 */
class MISERE_Board : public Board<char> {
private:
    char blank_symbol = ' ';
    ///< character used to represent an empty cell on the board.

    public:
    /**
     *@brief default constructor that initializes a 3x3 board.
     */
    MISERE_Board();
    /**
     *@breif updates the board with a player's move'
     */
    bool update_board(Move<char>* move);

    /**
    *@brief Checks if the given player has won the game.
     * In Misère Tic-Tac-Toe, a player wins if the OTHER player gets three in a row.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * In Misère Tic-Tac-Toe, a player loses if THEY get three in a row.
     */
    bool is_lose(Player<char>* player);

    /**
     * @brief Checks if the game has ended in a draw.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     */
    bool game_over(Player<char>* player);

    /**
     * @brief Displays the board with proper formatting
     */
    void display_board();

};
/**
 * @class MISERE_UI
 * @brief User Interface class for the Misère Tic-Tac-Toe game.
 * @see UI
 */
class MISERE_UI : public UI<char> {
    public:
    /**
    * @brief Constructs an MISERE_UI object.
     */
    MISERE_UI();

    /**
    *@brief Destructor for MISERE_UI.
     */
    ~MISERE_UI(){};

    /**
    *@brief Creates a player of the specified type.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

/**
 *@brief retrieves the next move from a player.
 */
    virtual Move<char>* get_move(Player<char>* player);

};


#endif //MISERE_H
