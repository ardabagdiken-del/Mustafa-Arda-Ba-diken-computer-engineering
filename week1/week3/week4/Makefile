#include "helpers.h"
#include <math.h>

// ─────────────────────────────────────────────────────────────────────────────
// 1. GRAYSCALE: Convert image to black and white
// ─────────────────────────────────────────────────────────────────────────────
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of Red, Green, and Blue
            // We use 3.0 to ensure floating point division before rounding
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            int rounded_avg = round(average);

            // Set all colors to the same average value
            image[i][j].rgbtRed = rounded_avg;
            image[i][j].rgbtGreen = rounded_avg;
            image[i][j].rgbtBlue = rounded_avg;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// 2. SEPIA: Apply a reddish-brown vintage tone
// ─────────────────────────────────────────────────────────────────────────────
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // CS50 Sepia Formula
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Cap the values at 255 if they exceed the byte limit
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// 3. REFLECT: Flip the image horizontally
// ─────────────────────────────────────────────────────────────────────────────
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // We only go up to width / 2 to swap sides
        for (int j = 0; j < width / 2; j++)
        {
            // Standard swap algorithm using a temporary variable
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// 4. BLUR: Box blur (averaging a 3x3 grid of pixels)
// ─────────────────────────────────────────────────────────────────────────────
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image to read from
    // We cannot modify the original 'image' directly while calculating
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalRed = 0, totalGreen = 0, totalBlue = 0;
            int counter = 0;

            // Iterate through the 3x3 neighborhood (-1 to +1)
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    int neighborRow = i + r;
                    int neighborCol = j + c;

                    // Check if the neighbor pixel is within image boundaries
                    if (neighborRow >= 0 && neighborRow < height && neighborCol >= 0 && neighborCol < width)
                    {
                        totalRed += copy[neighborRow][neighborCol].rgbtRed;
                        totalGreen += copy[neighborRow][neighborCol].rgbtGreen;
                        totalBlue += copy[neighborRow][neighborCol].rgbtBlue;
                        counter++;
                    }
                }
            }

            // Update the original image with the average of neighbors
            image[i][j].rgbtRed = round(totalRed / counter);
            image[i][j].rgbtGreen = round(totalGreen / counter);
            image[i][j].rgbtBlue = round(totalBlue / counter);
        }
    }
}
