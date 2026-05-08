#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// 1. GRAYSCALE: Convert image to shades of gray
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of Red, Green, and Blue values
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            int rounded_avg = round(average);

            // Apply the same value to all three colors
            image[i][j].rgbtRed = rounded_avg;
            image[i][j].rgbtGreen = rounded_avg;
            image[i][j].rgbtBlue = rounded_avg;
        }
    }
}

// 2. SEPIA: Apply a reddish-brown vintage tone
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Apply Sepia formula
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Cap the value at 255 if it's higher
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}

// 3. REFLECT: Flip the image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Only loop until the middle to swap sides
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// 4. BLUR: Box blur (3x3 average)
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy to read from
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
            float totalR = 0, totalG = 0, totalB = 0;
            int count = 0;

            // Search in 3x3 grid around the pixel
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    int ni = i + r;
                    int nj = j + c;

                    // Check if neighbor pixel is within image boundaries
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalR += copy[ni][nj].rgbtRed;
                        totalG += copy[ni][nj].rgbtGreen;
                        totalB += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Write the average to the original image
            image[i][j].rgbtRed = round(totalR / count);
            image[i][j].rgbtGreen = round(totalG / count);
            image[i][j].rgbtBlue = round(totalB / count);
        }
    }
}
