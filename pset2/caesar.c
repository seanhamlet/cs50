/* caesar - Prints caesar-cipher encrypted plaintext

    Implements an caesar cipher algorithm that allows a user to define a secret 
    key (non-negative integer) and plaintext to be encrypted. The encrypted text
    is then printed to the terminal.
    
INPUTS:
    secretKey:      int, Command-line argument of secret key to be used in
                    caesar cipher algorithm
    plainText:      string, Plaintext to be encrypted using secret key and 
                    caesar cipher algorithm

OUTPUTS:
    encryptedText:  char, Caesar cipher encrypted plaintext printed to the 
                    terminal

Date: 07-04-2016
Name: Sean M Hamlet
*/

#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    int secretKey;
    string plainText;
    
    int getASCIIshift(char p);
    char encrypt(char p, int k);
    
    // Make sure user provides secret key via command line
    if (argc != 2)
    {
        printf("Please provide a secret key at the command line.\n");
        return 1;
    }
    
    // Capture user input of non-negative integer
    secretKey = atoi(argv[1]);
    
    // Verify that user input is non-negative (and a digit)
    if (!isdigit(secretKey) && secretKey < 0)
    {
        printf("Please provide a non-negative integer for the secret key.\n");
        return 1;
    }
    
    // Capture user plaintext message
    plainText = GetString();
    
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        if (isalpha(plainText[i]))
        {
            printf("%c", encrypt(plainText[i], secretKey));
        } else
        {
            printf("%c", plainText[i]);   
        }
    }
    
    // Print new line
    printf("\n");
    
    return 0;
}

int getASCIIshift(char p)
{
    /* getASCIIshift - Computes ASCII shift from zero-based alphabet numbering

    This function assists in converting from ASCII letter numbering, where 
    'A' begins at 65 and 'a' begins at 97, to zero-based alphabet numbering
    (A - Z or a - z) --> (0 - 25)
    
    INPUTS:
        p:      char, Character to determine ASCII shift for
    
    OUTPUTS:
        asciiShift:  int, Shift amount for either upper or lower case character
    
    Date: 07-16-2016
    Name: Sean M Hamlet
    */
    int asciiShift;
    
    if (isupper(p))
        {
            asciiShift = 'A';
        } else
        {
            asciiShift = 'a';
        }
        
    return asciiShift;
}

char encrypt(char p, int k)
{
    /* encrypt - Encrypts character using a Caesar cipher algorithm
    
    INPUTS:
        p:      char, Plain text character to encrypt
        k:      int,  Secret key to use to Caesar cipher encrypt
    
    OUTPUTS:
        c:      char, Encrypted charcter
    
    Date: 07-16-2016
    Name: Sean M Hamlet
    */
    
    int c;
    
    // Get shift amount between ascii number and A-Z (0-25)
    int asciiShift = getASCIIshift(p);
    
    // Convert plain text ascii to zero-based alphabet numbering (A-Z --> 0-25)
    c = (int) p - asciiShift;
    
    // Apply Caesar algorithm by shifting character by secret key
    c += k;
    
    // Ensure that secret key can be handled if greater than 26
    c %= 26;
    
    // Convert from alphabet numbering to plain text ascii numbering
    c += asciiShift;
    
    // Convert from int ascii to character by casting
    c = (char) c;
    
    return c;
}