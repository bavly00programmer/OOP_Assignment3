#ifndef NUM_H
#define NUM_H
#include "BoardGame_Classes.h"

using namespace std;

/**
 * @class NUM_Board
 * @brief Represents the Numerical Tic-Tac-Toe game board.
 * @see Board
 */
class NUM_Board : public Board<int> {
private:
    int blank_symbol = 0;
    ///< Character used to represent an empty cell on the board.

    // يفضل إضافة قائمة بالأرقام المستخدمة هنا إذا لم تكن موجودة في Board الأساسية
    // vector<int> used_numbers;

public:
    /**
     * @brief Default constructor that initializes a 3x3 board.
     */
    NUM_Board();

    /**
     * @brief Updates the board with a player's move.
     */
    bool update_board(Move<int>* move);

    /**
     * @brief Checks if the given player has won the game.
     */
    bool is_win(Player<int>* player); // P كبير

    /**
     * @brief Checks if the given player has lost the game.
     */
    bool is_lose(Player<int>*) { return false; }; // P كبير

    /**
     * @brief Checks if the game has ended in a draw.
     */
    bool is_draw(Player<int>* player); // P كبير

    /**
     * @brief Determines if the game is over (win or draw).
     */
    bool game_is_over(Player<int>* player); // P كبير

    // تصحيح الخطأ هنا P كبير
    bool is_valid_number_for_player(int num, Player<int>* player);
};


/**
 * @class NUM_UI
 * @brief User Interface class for the Numerical Tic-Tac-Toe game.
 * @see UI
 */

class NUM_UI : public UI<int> {
public:
    /**
     * @brief Constructs an NUM_UI object.
     */
    NUM_UI();

    /**
     * @brief Destructor for NUM_UI.
     */
    ~NUM_UI() {};

    /**
     * @brief Creates a player of the specified type.
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type); // P كبير

    /**
     * @brief Retrieves the next move from a player.
     */
    virtual Move<int>* get_move(Player<int>* player); // P كبير
};

#endif // NUM.H
