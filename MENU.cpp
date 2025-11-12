//
// Created by HP on 11/11/2025.
//
#include<iostream>
#include<limits>
#include "NUM.h"
using namespace std;


int getChoice(int mn, int mx) {
    int choice;
    while (true) {
        cout << "enter choice between [ " << mn << " , " << mx << " ] :" ;
        if (cin >> choice) {
            if (mn <= choice && choice <= mx) {
                return choice;
            }
            cout << "invalid choice\n";
            cout << "try again with number between [ " << mn << " , " << mx << " ]\n" ;

        } else {
            cout << "Invalid input! Please enter a number\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


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
    cout << "0 - Exit Application\n\n";

    int choice =getChoice(0,11);
    cout<<"\n\n";
    return choice;
}

bool playAgain() {
    cout << "thanks for playing!\n";
    cout << "Do you want to play again?\n";
    cout << "1.Yes\n";
    cout << "2.No\n";
    int choice=getChoice(1,2);
    cout<<"\n\n";
    return choice == 1;
}


void numericalTicTacToeRun() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    // Create an instance of the specific UI for Numerical Tic-Tac-Toe
    UI<int> *game_ui = new NUM_UI();

    // Create the game board
    Board<int> *num_board = new NUM_Board();

    // Set up players (returns dynamically allocated array of Player pointers)
    Player<int> **players = game_ui->setup_players();

    // Create the game manager
    GameManager<int> num_game(num_board, players, game_ui);

    // Run the game loop
    num_game.run();

    // --- Cleanup ---
    delete num_board;

    for (int i = 0; i < 2; ++i)
        delete players[i];

    delete[] players;
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
                while (playAgain()) {
                    cout << "Thank you for playing!\n";
                }
                cout << "This game is under construction!" << endl;
                break;
            }
            case 2: {
                cout << "This game is under construction!" << endl;
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
                cout << "This game is under construction!" << endl;
                break;
            }
            case 6: {
                cout << "This game is under construction!" << endl;
                break;
            }
            case 7: {
                cout << "This game is under construction!" << endl;
                break;
            }
            case 8: {
                cout << "This game is under construction!" << endl;
                break;
            }
            case 9: {
                do {
                    numericalTicTacToeRun();
                } while (playAgain());
                break;
            }
            case 10: {
                cout << "This game is under construction!" << endl;
                break;
            }
            case 11: {
                cout << "This game is under construction!" << endl;
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