//
// Created by M on 23/11/2025.
//
/**
 * @file MISERE.h
 * @brief Misère Tic-Tac-Toe game implementation
 * @details Reverse Tic-Tac-Toe where the player who gets 3 in a row LOSES.
 *          Also known as "Avoid Tic-Tac-Toe" or "Notakto".
 * @author M
 * @date 23/11/2025
 */
#ifndef MISERE_H
#define MISERE_H
#include "BoardGame_Classes.h"
#include "Help_Function.h"

using namespace std;


/**
 * @class MISERE_Board
 * @brief Board implementation for Misère Tic-Tac-Toe
 * @extends Board<char>
 * 
 * Implements a standard 3x3 Tic-Tac-Toe board with reversed win conditions:
 * - Player wins if OPPONENT gets 3 in a row
 * - Player loses if THEY get 3 in a row
 * Includes smart AI using Minimax algorithm.
 */
class MISERE_Board : public Board<char> {
private:
    char blank_symbol = '.';
    ///< character used to represent an empty cell on the board.
public:
    /**
     *@brief default constructor 
     *@details Initializes a 3x3 board with all cells empty
     */
    MISERE_Board();
/**
     * @brief Destructor
     */
    ~MISERE_Board() override;
 /**
     * @brief Evaluate board state for AI
     * @param ai AI player symbol
     * @param human Human player symbol
     * @return Score (+10 if human has 3 in a row, -10 if AI has 3 in a row, 0 otherwise)
     */
int evaluate(char ai, char human);
/**
     * @brief Minimax algorithm for AI decision-making
     * @param ai AI player symbol
     * @param human Human player symbol
     * @param maximizing Whether it's the maximizing player's turn
     * @return Best score from current board state
     */
int minimax(char ai,char human, bool maximizing);
 /**
     * @brief Find best move for AI using minimax
     * @param ai AI player symbol
     * @param human Human player symbol
     * @return Pair of (row, column) for best move
     */
pair<int,int> find_best_move(char ai,char human);

     /**
     * @brief Update the board with a player's move
     * @param move Pointer to the move containing position and symbol
     * @return true if move was successful, false otherwise
     */
    bool update_board(Move<char> *move)override;

   /**
     * @brief Check if the given player has won the game
     * @param player Pointer to the player to check
     * @return true if player has won (opponent has 3 in a row)
     * @details In Misère Tic-Tac-Toe, a player wins if the OTHER player gets three in a row
     */
    bool is_win(Player<char> *player)override;

   /**
     * @brief Check if the given player has lost the game
     * @param player Pointer to the player to check
     * @return true if player has lost (they have 3 in a row)
     * @details In Misère Tic-Tac-Toe, a player loses if THEY get three in a row
     */
    bool is_lose(Player<char> *player)override;

   /**
     * @brief Check if the game has ended in a draw
     * @param player Pointer to the current player
     * @return true if board is full and no one has won/lost
     */
    bool is_draw(Player<char> *player)override;

  /**
     * @brief Determine if the game is over (win or draw)
     * @param player Pointer to the current player
     * @return true if game is over (win, lose, or draw)
     */
    bool game_is_over(Player<char> *player) override;

    /**
     * @brief Displays the board with proper formatting
     */
};

/**
 * @class MISERE_UI
 * @brief User Interface for the Misère Tic-Tac-Toe game
 * @extends UI<char>
 */
class MISERE_UI : public UI<char> {
public:
    /**
     * @brief Default constructor
     * @details Displays welcome message for Misère Tic-Tac-Toe
     */
    MISERE_UI();

    /**
    *@brief Destructor
     */
    ~MISERE_UI() override = default;

    /**
     * @brief Create a player of the specified type
     * @param name Player's name
     * @param symbol Player's symbol ('X' or 'O')
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<char> *create_player(string &name, char symbol, PlayerType type)override ;

    /**
     * @brief Get the next move from a player
     * @param player Pointer to the current player
     * @return Pointer to the Move object
     * @details Uses smart AI with minimax for computer players
     */
     Move<char> *get_move(Player<char> *player) override;
};


#endif //MISERE_H



