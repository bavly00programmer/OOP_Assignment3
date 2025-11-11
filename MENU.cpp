//
// Created by HP on 11/11/2025.
//
#include<iostream>
#include "XO_Classes.h"
using namespace std;

int display_menu_and_get_choice() {
    cout << "\n=========================================\n";
    cout << "          CS213 - Games Menu\n";
    cout << "=========================================\n";

    cout << "WELLCOME TO (PROJECT NAME)\n";
    cout << "1. SUS\n";
    cout << "2. Four-in-a-row\n";
    cout << "3. 5x5 TicTacToe\n";
    cout << "4. Word Tic-tac-toe\n";
    cout << "5. Misère TicTacToe\n";
    cout << "6. Diamond Tic-Tac-Toe\n";
    cout << "7. 4x4 Tic-Tac-Toe\n";
    cout << "8. Pyramid Tic-Tac-Toe\n";
    cout << "9. Numerical Tic-Tac-Toe\n";
    cout << "10. Obstacles Tic-Tac-Toe\n";
    cout << "11. Infinity Tic-Tac-Toe\n";
    cout << "12. XO_DEMO\n";

    cout << "0 - Exit Application\n\n";

    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    return choice;
}

void xoRun() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    // Create an instance of the specific UI for X-O using a pointer
    UI<char> *game_ui = new XO_UI();

    // Create the game board. For X-O, this is an X_O_Board.
    Board<char> *xo_board = new X_O_Board();

    // Use the UI to set up the players for the game.
    // The UI returns a dynamically allocated array of Player pointers.
    Player<char> **players = game_ui->setup_players();

    // Create the game manager with the board and the array of players.
    GameManager<char> x_o_game(xo_board, players, game_ui);

    // Run the game loop.
    x_o_game.run();

    // --- Cleanup ---
    // Delete the dynamically allocated board object.
    delete xo_board;

    // Delete the individual player objects.
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    // Delete the dynamically allocated array of player pointers itself.
    delete[] players;
}

bool playAgain() {
    cout << "thanks for playing!\n";
    cout << "Do you want to play again?\n";
    cout << "1.Yes\n";
    cout << "2.No\n";
    int choice;
    cin >> choice;
    while (choice != 1 && choice != 2) {
        cout << "invalid choice\n";
        cout << "please enter 1 or 2\n";
        cin >> choice;
    }
    return choice == 1;
}


int main() {
    int choice;
    do {
        choice = display_menu_and_get_choice();
        switch (choice) {
            case 0:
                cout << "Thank you for playing!\n";
                cout << "Exiting application. \n Goodbye!\n";
                break;
            case 1:
                cout << "This game is under construction!" << endl;
                break;
            case 2:
                cout << "This game is under construction!" << endl;
                break;
            case 3:
                cout << "This game is under construction!" << endl;
                break;
            case 4:
                cout << "This game is under construction!" << endl;
                break;
            case 5:
                cout << "This game is under construction!" << endl;
                break;
            case 6:
                cout << "This game is under construction!" << endl;
                break;
            case 7:
                cout << "This game is under construction!" << endl;
                break;
            case 8:
                cout << "This game is under construction!" << endl;
                break;
            case 9:
                cout << "This game is under construction!" << endl;
                break;
            case 10:
                cout << "This game is under construction!" << endl;
                break;
            case 11:
                cout << "This game is under construction!" << endl;
                break;
            case 12:
                do {
                    xoRun();
                } while (playAgain());
            default:
                cout << "Invalid Choice\n";
        }
    } while (choice != 0) ;


    return 0;
}
