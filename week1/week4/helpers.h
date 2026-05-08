#include "helpers.h"
#include <math.h>

// ---------------------------------------------------------------------------
// 1. GRAYSCALE: Convert image to black and white
// ---------------------------------------------------------------------------
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of Red, Green, and Blue values
            // We use 3.0 to ensure floating point division
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            int rounded_avg = round(average);

            // Set all color channels to the same average value
            image[i][j].rgbtRed = rounded_avg;
            image[i][j].rgbtGreen = rounded_avg;
            image[i][j].rgbtBlue = rounded_avg;
        }
    }
}

// ---------------------------------------------------------------------------
// 2. SEPIA: Apply a reddish-brown vintage tone
// ---------------------------------------------------------------------------
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Apply specific weights to calculate sepia tones
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Ensure the value does not exceed the 8-bit maximum (255)
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
        // Only loop until the middle to swap sides correctly
        for (int j = 0; j < width / 2; j++)
        {
            // Standard swap algorithm using a temporary struct
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// ---------------------------------------------------------------------------
// 4. BLUR: Box blur (3x3 neighborhood average)
// ---------------------------------------------------------------------------
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a backup copy to read original pixel data from
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

            // Iterate through the 3x3 box centered on the current pixel
            for (int r = -1; r <= 1; r++)
            {
                for (int c = -1; c <= 1; c++)
                {
                    int neighborI = i + r;
                    int neighborJ = j + c;

                    // Verify the neighboring pixel exists within image boundaries
                    if (neighborI >= 0 && neighborI < height && neighborJ >= 0 && neighborJ < width)
                    {
                        totalR += copy[neighborI][neighborJ].rgbtRed;
                        totalG += copy[neighborI][neighborJ].rgbtGreen;
                        totalB += copy[neighborI][neighborJ].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average and write to the actual image
            image[i][j].rgbtRed = round(totalR / count);
            image[i][j].rgbtGreen = round(totalG / count);
            image[i][j].rgbtBlue = round(totalB / count);
        }
    }
}
