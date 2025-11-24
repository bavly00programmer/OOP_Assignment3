//
// Created by Bavly on 11/25/2025.
//
#include <iostream>
#include<limits>
#include "Help_Function.h"
using namespace std;

int getChoice(int mn, int mx) {
    int choice;
    while (true) {
        cout << "Enter choice between [" << mn << " , " << mx << "]: ";
        if (cin >> choice) {
            if (mn <= choice && choice <= mx) {
                return choice;
            }
            cout << "Invalid choice. Try again.\n";
        } else {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int getNUmber() {
    {
        int choice;
        while (true) {
            cout << "Enter choice from Available numbers : ";
            if (cin >> choice) {
                return choice;
            }
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
