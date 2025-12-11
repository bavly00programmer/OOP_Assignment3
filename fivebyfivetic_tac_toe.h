// Created by Mostafa on 12/6/2025.
// FiveByFive Tic Tac Toe – Count 3-in-a-row sequences


#ifndef OOPA3_FIVEBYFIVETIC_TAC_TOE_H
#define OOPA3_FIVEBYFIVETIC_TAC_TOE_H

#include <map>
#include "BoardGame_Classes.h"

/**
 * @class FiveByFive_Board
 * @brief 5x5 Tic Tac Toe board where players earn points for each 3-in-a-row
 */
class FiveByFive_Board : public Board<char> {

private:
    char blank_symbol = '.';
    std::map<char, int> points_map;

public:

    /// Constructor: initializes 5x5 board
    FiveByFive_Board();

    /// Applies a move and updates points
    bool update_board(Move<char>* move) override;

    /// Count new 3-in-a-row sequences on the board
    int count_sequences(FiveByFive_Board* boardPtr);

    /// Check if the player wins
    bool is_win(Player<char>* player) override;

    /// Check if the player loses
    bool is_lose(Player<char>* player) override;

    /// Check draw
    bool is_draw(Player<char>* player) override;

    /// True if 24 moves are made
    bool game_is_over(Player<char>* player) override;

    /// Score for a specific player
    int count_points_for(Player<char>* player);
};


/**
 * @class FiveByFive_UI
 * @brief User Interface for the 5x5 Tic Tac Toe game
 */
class FiveByFive_UI : public UI<char> {

public:

    /// Constructor that prints welcome message
    FiveByFive_UI();

    /// Create player (human/computer)
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

    /// Read a move from the player
    Move<char>* get_move(Player<char>* player) override;

    /// Setup X and O players
    Player<char>** setup_players() override;

    ~FiveByFive_UI() override = default;
};
#endif //OOPA3_FIVEBYFIVETIC_TAC_TOE_H
