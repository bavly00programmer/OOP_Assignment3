//
// Created by Bavly on 11/24/2025.
//
/**
 * @file Help_Function.h
 * @brief Helper functions for input validation
 * @details Provides utility functions for getting valid user input.
 * @author Bavly
 * @date 11/24/2025
 */
#ifndef HELP_FUNCTION_H
#define HELP_FUNCTION_H
/**
 * @brief Get a valid integer choice within a range
 * @param mn Minimum allowed value
 * @param mx Maximum allowed value
 * @return Valid integer input from user
 * @details Prompts user repeatedly until valid input is received
 */

int getChoice(int mn, int mx);
/**
 * @brief Get a valid number from user
 * @return Valid integer input from user
 * @details Prompts user repeatedly until a valid number is received
 */
int getNUmber ();


#endif //HELP_FUNCTION_H
