//
// Created by HP on 11/11/2025.
//
#include<iostream>
#include"BoardGame_Classes.h"
#include "fourInRow.h"
#include "NUM.h"
#include"SUS.h"
#include "Help_Function.h"
#include "InfinityTic-Tac-Toe.h"
#include "MISERE.h"
#include "xo4x4.h"
#include "OBgame.h"
#include "DIAMOND.h"
using namespace std;

// NUM.cpp

int display_menu_and_get_choice() {
    cout << "\n=========================================\n";
    cout << "          CS213 - Games Menu\n";
    cout << "===========================================\n";

    cout << "WELLCOME TO (PROJECT NAME)\n";
    cout << "1. SUS\n";
    cout << "2. Four-in-a-row\n";
    cout << "3. 5x5 TicTacToe\n";
    cout << "4. Word Tic-tac-toe\n";
    cout << "5. Misere TicTacToe\n";
    cout << "6. Diamond Tic-Tac-Toe\n";
    cout << "7. 4x4 Tic-Tac-Toe\n";
    cout << "8. Pyramid Tic-Tac-Toe\n";
    cout << "9. Numerical Tic-Tac-Toe\n";
    cout << "10. Obstacles Tic-Tac-Toe\n";
    cout << "11. Infinity Tic-Tac-Toe\n";
    cout << "0 - Exit Application\n\n";

    int choice = getChoice(0, 11);
    cout << "\n\n";
    return choice;
}

bool playAgain() {
    cout << "thanks for playing!\n";
    cout << "Do you want to play again?\n";
    cout << "1.Yes\n";
    cout << "2.No\n";
    int choice = getChoice(1, 2);
    cout << "\n\n";
    return choice == 1;
}

template<typename T>

void run_game(Board<T> *game_board, UI<T> *game_ui) {
    srand(static_cast<unsigned int>(time(0)));

    Player<T> **players = game_ui->setup_players();
    GameManager<T> game(game_board, players, game_ui);
    game.run();

    // Cleanup
    delete game_board;
    for (int i = 0; i < 2; ++i)
        delete players[i];
    delete[] players;
    delete game_ui;
}


int main() {
    int choice;
    do {
        choice = display_menu_and_get_choice();
        switch (choice) {
            case 0: {
                cout << "Thank you for playing!\n";
                cout << "Exiting application. \n Goodbye!\n";
            }
            break;
            case 1: {
                do {
                    run_game(new SUS_Board, new SUS_UI);
                } while (playAgain());
                break;
            }
            case 2: {
                do {
                    run_game(new fourBoard, new fourUI);
                } while (playAgain());
                break;
            }
            case 3: {
                cout << "This game is under construction!" << endl;
                break;
            }
            case 4: {
                cout << "This game is under construction!" << endl;
                break;
            }
            case 5: {
                do {
                    run_game(new MISERE_Board, new MISERE_UI);
                    cout << "Thank you for playing!\n";
                } while (playAgain());
                break;
            }
            case 6: {
                do{
                    run_game(new DIAMOND_Board, new DIAMOND_UI);
                    cout <<"Thank you for playing\n";
                }while (playAgain());
                break;
            }
            case 7: {
                do {
                    run_game(new X_O_Board, new XO_UI);
                } while (playAgain());
                break;
            }
            case 8: {
                cout << "This game is under construction!" << endl;
                break;
            }
            case 9: {
                do {
                    run_game(new NUM_Board, new NUM_UI);
                } while (playAgain());
                break;
            }
            case 10: {
                do {

                    run_game(new ObstaclesBoard, new ObstaclesUI);
                } while (playAgain());
                break;
            }
            case 11: {
                do {
                    run_game(new infinity_Board, new infinity_UI);
                } while (playAgain());
                break;
            }
            default: {
                cout << "Invalid choice!" << endl;
                break;
            }
        }
    } while (choice != 0);
    return 0;
}
