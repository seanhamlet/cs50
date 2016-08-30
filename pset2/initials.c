/* initials - Prints capitalized initials of full name

    Implements an algorithm that extracts the initials of a full name and 
    converts it to uppercase (if needed).
    
INPUTS:
    name:       string, User prompted full name

OUTPUTS:
    initials:   char, Uppercase characters of initials printed to the terminal

Date: 07-04-2016
Name: Sean M Hamlet
*/

#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main(void)
{
    // Capture user's full name
    string name = GetString();
    
    // If needed, convert first inital to uppercase and print it
    printf("%c", toupper(name[0]));
    
    // if string is not NULL, then loop through each character
    if (name != NULL)
    {
        for (int i = 0, n = strlen(name); i < n; i++)
        {
            // If space character in name, then print out uppercase of next 
            // character, which should be first letter of name (first, last, middle)   
            if (isspace(name[i]))
            {
                printf("%c", toupper(name[i + 1]));
            }
        }
    }
    
    // Print newline to move command line to next line
    printf("\n");
}