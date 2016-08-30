/* greedy - Prints minimum number of coins for exact change given

    Implements a greedy algorithm that prints the minimum number of coins due for
    change in dollars. The number of coins may include any value of coins (i.e.
    quarters, dimes, nickels, and pennies).
    
INPUTS:
    change_in_dollars:  float, User prompted value of change in dollars that is
                        formatted (e.g. 9.75)

OUTPUTS:
    coins:              int, Printed value to terminal of minimum number of coins
                        due for change_in_dollars value

Date: 06-26-2016
Name: Sean M Hamlet
*/

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int dollarsToCents(float change_in_dollars)
{
    
    int cents_per_dollar = 100;
    int cents = round(change_in_dollars * cents_per_dollar);
    
    return cents;
}

int main(void)
{
    float change_in_dollars;
    // Ask user how much change is owed
    printf("O hai! How much change is owed?\n");
    change_in_dollars = GetFloat();
    while (change_in_dollars < 0)
    {
        printf("How much change is owed?\n");
        // Capture user input
        change_in_dollars = GetFloat();
    }
    
    // Convert user input into cents
    int cents = dollarsToCents(change_in_dollars);
    
    
    // To Determine how many of each coin is needed:
    
    // Use while loop to keep looping until cents == 0
    // Use multiple if statements to determine if cents is >= 25, 10, 5, 1
    // If >= coin amount, coins += cents / coin amount, 
    // New cents = cents % coin amount (use mod operator to determine remainder)
    // Repeat until cents == 0
    
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    
    int coins = 0;
    
    while (cents > 0)
    {
        if (cents >= quarter)
        {
            coins += cents / quarter;
            cents = cents % quarter;
            
        } else if (cents >= dime) 
        {
            coins += cents / dime;
            cents = cents % dime;
            
        } else if (cents >= nickel)
        {
            coins += cents / nickel;
            cents = cents % nickel;
            
        } else if (cents >= penny)
        {
            coins += cents / penny;
            cents = cents % penny;
        }
        
    }
    
    printf("%d\n", coins);
    
    return 0;
}



