#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------------------------
// 1. GRAYSCALE: Convert each pixel to a shade of grey
// ---------------------------------------------------------------------------
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of Red, Green, and Blue
            // We use 3.0 to ensure floating point division
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            BYTE rounded_avg = round(average);

            // Set all three channels to the same average value
            image[i][j].rgbtRed = rounded_avg;
            image[i][j].rgbtGreen = rounded_avg;
            image[i][j].rgbtBlue = rounded_avg;
        }
    }
}

// ---------------------------------------------------------------------------
// 2. SEPIA: Apply a warm reddish-brown tone
// ---------------------------------------------------------------------------
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Save original values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Compute sepia values using formulas
            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            // Cap each value at 255
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}

// ---------------------------------------------------------------------------
// 3. REFLECT: Flip the image horizontally
// ---------------------------------------------------------------------------
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Only iterate to the midpoint of the row
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels using a temporary RGBTRIPLE
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// ---------------------------------------------------------------------------
// 4. BLUR: Box blur (3x3 average)
// ---------------------------------------------------------------------------
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image to read from
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate over every pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum_r = 0, sum_g = 0, sum_b = 0;
            int count = 0;

            // Iterate over the 3x3 neighborhood
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if neighbor is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sum_r += copy[ni][nj].rgbtRed;
                        sum_g += copy[ni][nj].rgbtGreen;
                        sum_b += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Assign the rounded average to the original image
            image[i][j].rgbtRed = round(sum_r / count);
            image[i][j].rgbtGreen = round(sum_g / count);
            image[i][j].rgbtBlue = round(sum_b / count);
        }
    }
}
