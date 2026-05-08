// credit.c
// CS50x - Week 1, Problem Set 1
//
// Exercise: Credit Card Validator
// --------------------------------
// Validate a credit card number using Luhn's Algorithm,
// then identify whether it is AMEX, MASTERCARD, VISA, or INVALID.
//
// How to compile:  make credit
// How to run:      ./credit
// How to check:    check50 cs50/problems/2024/x/credit

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for a credit card number using get_long()
    long number = get_long("Number: ");

    // -----------------------------------------------------------------------
    // STEP 1: Count the number of digits
    // -----------------------------------------------------------------------
    int length = 0;
    long temp_number = number;
    while (temp_number > 0)
    {
        temp_number /= 10;
        length++;
    }

    // -----------------------------------------------------------------------
    // STEP 2: Apply Luhn's Algorithm
    // -----------------------------------------------------------------------
    int sum_doubled = 0;
    int sum_rest = 0;
    long luhn_number = number;

    for (int i = 0; i < length; i++)
    {
        int digit = luhn_number % 10;
        luhn_number /= 10;

        // If position i is ODD (starting from i=0 as last digit)
        if (i % 2 != 0)
        {
            int doubled = digit * 2;
            // Add digits of product (e.g., 12 -> 1 + 2)
            sum_doubled += (doubled % 10) + (doubled / 10);
        }
        else
        {
            // If position i is EVEN, add directly to sum_rest
            sum_rest += digit;
        }
    }

    // -----------------------------------------------------------------------
    // STEP 3: Check validity
    // -----------------------------------------------------------------------
    if ((sum_doubled + sum_rest) % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // -----------------------------------------------------------------------
    // STEP 4: Identify card type
    // -----------------------------------------------------------------------
    long first_two = number;
    while (first_two >= 100)
    {
        first_two /= 10;
    }

    // Identify card brand based on length and starting digits
    if (length == 15 && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (first_two >= 51 && first_two <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && (first_two / 10 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
