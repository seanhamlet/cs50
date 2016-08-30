/* mario - Prints pyramid from Mario using hashes

    This code prints a pyramid from Mario using hashes. The user is 
    prompted for the height of the pyramid and then the pyramid prints out.
    
INPUTS:
    height:     int, User prompted value of height of the pyramid in levels
                Height input must be non-negative and < 23.

Date: 06-26-2016
Name: Sean M Hamlet
*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
 
    // Prompt user for height (must be non-negative and < 23)   
    do
    {
        printf("Height: ");
        height = GetInt();
    } while (height < 0 || height > 23);
    
    // Create hash pyramid
    for (int i = 0; i < height; i++)
    {
        // Print space for each line
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        
        // Print hashes for each line
        // Num hashes goes to i + 2
        for (int k = 0; k < i + 2; k++)
        {
            printf("#");
        }
        
        // Move to next line
        printf("\n");
    }
    return 0;
}