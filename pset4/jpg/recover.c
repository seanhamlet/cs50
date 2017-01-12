/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 * 
 * Written by: Sean M Hamlet
 * Date: 20161028
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

bool is_start_of_jpg(BYTE block[512]);

bool is_first_jpg = true;
bool is_jpg_block = false;
int  n_jpg_found = 0;

// jpg pointer
FILE* img = NULL;

char jpg_name[8];

int main(void)
{
    // 1. Open the memory card file
    FILE* cardptr = fopen("card.raw", "r");
    if (cardptr == NULL)
    {
        printf("Could not open %s.\n", "card.raw");
        return 2;
    }
    
    // 512 byte block of temporary storage
    // define char array of 512 BYTES
    BYTE block[512];

    // loop through blocks with while loop and loop until can't fread anymore (end of file)
    // remember that each time the while loop condition is checked
    //  the fread function is being called so there is no need to 
    //  call fread again within the while loop itself.
    
    // read next 512 Bytes
    while(fread(&block, sizeof(block), 1, cardptr) == 1)
    {
        // find the beginning of jpg
        if (is_start_of_jpg(block))
        {
            if (!is_first_jpg)
            {
                // close previous jpg file
                fclose(img);
            }
            
            // create new jpg filename
            sprintf(jpg_name, "%03d.jpg", n_jpg_found);
            
            // open new jpg file
            img = fopen(jpg_name, "a"); 
            if (img == NULL)
            {
                printf("Could not open %s.\n", jpg_name);
                return 2;
            }
            
            is_jpg_block = true;
            n_jpg_found++;
        }
        
        if (is_jpg_block)
        {
            // store data in jpg file
            fwrite(&block, sizeof(block), 1, img);
        } 
    }
    
    fclose(cardptr);
    fclose(img);
}

bool is_start_of_jpg(BYTE block[512])
{
    // First 3 bytes of jpg: 0xff 0xd8 0xff
    // Fourth byte of jpg: 0xeX where 'X' is don't care
    // Therefore, you can find the fourth by by a bitwise right shift by 4 to check if
    // the first four bits are equal to 'e'
    return block[0] == 0xff & block[1] == 0xd8 & block[2] == 0xff & (block[3] >> 4 == 0x0e);
}