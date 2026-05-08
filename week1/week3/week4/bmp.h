#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // 1. Open input file
    FILE *inptr = fopen("input.bmp", "r");
    if (inptr == NULL) return 1;

    // 2. Read BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // 3. Read BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure it's a 24-bit BMP
    if (bf.bfType != 0x4d42 || bi.biBitCount != 24)
    {
        fclose(inptr);
        return 2;
    }

    // Get image dimensions
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // 4. Allocate memory for pixels
    // We use a 2D array of RGBTRIPLEs
    RGBTRIPLE (*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Calculate padding for scanlines (BMP rows must be multiples of 4 bytes)
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // 5. Read pixel data from file
    for (int i = 0; i < height; i++)
    {
        // Read row of pixels
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);

        // Skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // --- (This is where you would call your filter functions) ---

    // 6. Close file and free memory
    fclose(inptr);
    free(image);
    
    return 0;
}
