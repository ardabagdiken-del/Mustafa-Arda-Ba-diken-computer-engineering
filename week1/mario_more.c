// mario_more.c
// CS50x - Week 1, Problem Set 1 (Bonus)
//
// Exercise: Mario (More Comfortable)
// ------------------------------------
// Print a DOUBLE half-pyramid separated by a two-space gap.
//
// Expected output (height = 4):
//    #  #
//   ##  ##
//  ###  ###
// ####  ####
//
// How to compile:  make mario_more
// How to run:      ./mario_more
// How to check:    check50 cs50/problems/2024/x/mario/more

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Use a do-while loop to prompt for height.
    // Keep re-prompting until height is between 1 and 8 (inclusive).
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Print each row of the double pyramid
    for (int row = 1; row <= height; row++)
    {
        // 1. Print leading spaces for the LEFT pyramid
        for (int spaces = 0; spaces < height - row; spaces++)
        {
            printf(" ");
        }

        // 2. Print hashes for the LEFT side
        for (int hashes = 0; hashes < row; hashes++)
        {
            printf("#");
        }

        // 3. Print the two-space gap
        printf("  ");

        // 4. Print hashes for the RIGHT side
        for (int hashes = 0; hashes < row; hashes++)
        {
            printf("#");
        }

        // 5. Move to the next line
        printf("\n");
    }

    return 0;
}
