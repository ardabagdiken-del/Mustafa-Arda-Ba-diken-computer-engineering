// cash.c
// CS50x - Week 1, Problem Set 1
//
// Exercise: Cash (Greedy Change)
// --------------------------------
// Calculate the minimum number of coins needed to make change.
// Coins available: quarters (25¢), dimes (10¢), nickels (5¢), pennies (1¢)
//
// Expected output:
//   Change owed: 41
//   4
//   (1 quarter + 1 dime + 1 nickel + 1 penny)
//
// How to compile:  make cash
// How to run:      ./cash
// How to check:    check50 cs50/problems/2024/x/cash

#include <cs50.h>
#include <stdio.h>

// Function prototypes — do NOT change these signatures
int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Get the number of cents owed
    int cents = get_cents();

    // Calculate the number of each coin
    int quarters = calculate_quarters(cents);
    cents -= quarters * 25;

    int dimes = calculate_dimes(cents);
    cents -= dimes * 10;

    int nickels = calculate_nickels(cents);
    cents -= nickels * 5;

    int pennies = calculate_pennies(cents);

    // Print the total number of coins
    printf("%i\n", quarters + dimes + nickels + pennies);
}

// ---------------------------------------------------------------------------
// Implementation of the functions below.
// Each function receives the remaining cents and returns how many
// of that coin fit into it.
// ---------------------------------------------------------------------------

// Prompt the user for a non-negative number of cents
int get_cents(void)
{
    int cents;
    // Prompt the user for cents using a do-while loop
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Return the valid non-negative value
    return cents;
}

// Return how many quarters fit in cents
int calculate_quarters(int cents)
{
    // Return the number of quarters using integer division
    int quarters = cents / 25;
    return quarters;
}

// Return how many dimes fit in cents
int calculate_dimes(int cents)
{
    // Return the number of dimes using integer division
    int dimes = cents / 10;
    return dimes;
}

// Return how many nickels fit in cents
int calculate_nickels(int cents)
{
    // Return the number of nickels using integer division
    int nickels = cents / 5;
    return nickels;
}

// Return how many pennies fit in cents
int calculate_pennies(int cents)
{
    // The remaining cents are all pennies
    return cents;
}

// Final adjustments for formatting
//
//
//
//
//
//
