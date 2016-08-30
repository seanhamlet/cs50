/* vigenere - Prints vigenere-cipher encrypted plaintext

    Implements an vigenere cipher algorithm that allows a user to define a secret 
    key (alphabetical word) and plaintext to be encrypted. The encrypted text
    is then printed to the terminal.
    
INPUTS:
    secretKey:      string, Command-line argument of secret key to be used in
                    vignere cipher algorithm
    plainText:      string, Plaintext to be encrypted using secret key and 
                    vigenere cipher algorithm

OUTPUTS:
    encryptedText:  char, Vigenere cipher encrypted plaintext printed to the 
                    terminal

Date: 07-14-2016
Name: Sean M Hamlet
*/

#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    string secretKey;
    string plainText;
    int keyIndex = 0;
    int key;
    int lengthSecretKey;
    
    int getASCIIshift(char p);
    int charToAlpha(char p);
    char encrypt(char p, int k);
    
    // If != 2 command-line arguments, return 1
    if (argc != 2)
    {
        printf("Please provide a secret key at the command line.\n");
        return 1;
    }
    
    // Capture user input of string secret key
    secretKey = argv[1];
    
    // Verify that user input string has only alphabetical characters
    for (int i = 0, n = strlen(secretKey); i < n; i++)
    {
        if (!isalpha(secretKey[i]))
        {
            printf("Please provide a only alphabetical characters for the secret key.\n");
            return 1;
        }
    }
    
    // Use length of secretKey to loop through secreKey characters with modulo
    lengthSecretKey = strlen(secretKey);
    
    // Capture user plaintext message
    plainText = GetString();
    
    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        if (isalpha(plainText[i]))
        {
            // Loop through keyword chars with modulo and keyIndex
            // create secretKey identifier that takes a character and returns an int of the secret key
            key = charToAlpha(secretKey[keyIndex % lengthSecretKey]);
            printf("%c", encrypt(plainText[i], key));
            keyIndex++;
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
    'A' begins at 65 and 'a' begins at XXX, to zero-based alphabet numbering
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

int charToAlpha(char p)
{
    /* charToAlpha - Converts ascii character to zero-based alphabet number

    This function converts from ASCII letter numbering, where 
    'A' begins at 65 and 'a' begins at 97, to zero-based alphabet numbering
    (A - Z or a - z) --> (0 - 25)
    
    INPUTS:
        p:      char, Character to convert from ASCII to zero-based alphabet numbering
    
    OUTPUTS:
        alphaNum:  int, Zero-based alphabetical number of input char p
    
    Date: 07-16-2016
    Name: Sean M Hamlet
    */
    int alphaNum;   
    
    alphaNum = (int) p - getASCIIshift(p);
    
    return alphaNum;
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