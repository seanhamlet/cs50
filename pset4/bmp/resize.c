/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes an input and saves as different file size.
 * 
 * Written by: Sean M Hamlet
 * Date: 20161028
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize <resize-factor> infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    if (n < 1 | n > 100)
    {
        printf("<resize-factor> n must be a positive integer less than or equal to 100\n.");
        return 1;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // update outfile's header information based on n.
    
    // create outfile's BITMAPFILEHEADER
    BITMAPFILEHEADER bfo = bf;

    // create outfile's BITMAPINFOHEADER
    BITMAPINFOHEADER bio = bi;
    
    // width and height scale by n (does not include padding)
    bio.biWidth *= n;
    bio.biHeight *= n;
    
    // determine padding for output file's scanlines
    int paddingout =  (4 - (bio.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update biSizeImage by computing the size of a scan line and multiplying that by the absolute value of the image height
    bio.biSizeImage = ((sizeof(RGBTRIPLE) * bio.biWidth) + paddingout) * abs(bio.biHeight);
    
    // update bfSize based on new biSizeImage
    bfo.bfSize = bio.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for input file's scanlines
    int paddingin =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //repeat this line for every n
        for (int line = 0; line < n; line++)
        {
            //fseek back to beginning of inptr row after first loop
            if (line > 0) {
                int rowLengthInBytes = 3*bi.biWidth + paddingin;
                fseek(inptr, -rowLengthInBytes, SEEK_CUR);
            }
            
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
            
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                //repeat writing pixel to output file for every n
                for (int pix = 0; pix < n; pix++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            
            }

            // skip over padding of input file
            fseek(inptr, paddingin, SEEK_CUR);
    
            // then add padding for output file
            for (int k = 0; k < paddingout; k++)
            {
                fputc(0x00, outptr);
            }
        }
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
