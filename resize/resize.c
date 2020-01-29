#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize copy infile outfile\n");
        return 1;
    }

    char *infile = argv[2];
    char *outfile = argv[3];
    int n = atoi(argv[1]);


    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }


    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);


    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    LONG biWidthold = bi.biWidth;
    LONG biHeightold = bi.biHeight;
    int paddingold = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biWidth *= n;
    bi.biHeight *= n;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    BYTE fpixel[bi.biWidth][3];
    int sht = 0;
    for (int i = 0, biHeight = abs(biHeightold); i < biHeight; i++)
    {
        for (int j = 0; j < biWidthold; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            for (int a = 0; a < n; a++)
            {
                fpixel[sht][0] = triple.rgbtBlue;
                fpixel[sht][1] = triple.rgbtGreen;
                fpixel[sht][2] = triple.rgbtRed;
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                sht++;
            }
        }
        for (int b = 0; b < n - 1; b++)
        {
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
            for (int c = 0; c < bi.biWidth; c++)
            {
                fputc(fpixel[c][0], outptr);
                fputc(fpixel[c][1], outptr);
                fputc(fpixel[c][2], outptr);
            }
        }
        if (n != 0)
        {
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        sht = 0;
        fseek(inptr, paddingold, SEEK_CUR);
    }
    fclose(outptr);
    fclose(inptr);
    return 0;
}