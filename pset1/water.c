/* water - Computes shower water amount measured in bottles

INPUTS:
    shower_length:      int, Length of shower in minutes
    
OUTPUTS:
    bottles_per_shower: int, Number of bottles (of water) used per shower

Date: 06-26-2016
Name: Sean M Hamlet
*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int bottles_per_min = 12;
    
    printf("minutes: ");
    int shower_length = GetInt();
    
    int bottles_per_shower = shower_length * bottles_per_min;
    
    printf("bottles: %d\n", bottles_per_shower);
}