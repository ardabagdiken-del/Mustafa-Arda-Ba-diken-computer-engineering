#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ---------------------------------------------------------------------------
    // TODO 1: Validate command-line arguments
    // ---------------------------------------------------------------------------
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // ---------------------------------------------------------------------------
    // TODO 2: Open the memory card file for reading (binary mode)
    // ---------------------------------------------------------------------------
    FILE *card = fopen(argv[1], "rb");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // ---------------------------------------------------------------------------
    // TODO 3: Declare your variables
    // ---------------------------------------------------------------------------
    BYTE buffer[512];      // A 512-byte buffer for reading blocks
    int count = 0;         // Counter for JPEGs found
    FILE *img = NULL;      // Pointer for the current output JPEG file
    char filename[8];      // String to hold filenames like "000.jpg"

    // ---------------------------------------------------------------------------
    // TODO 4: Main loop — read one 512-byte block at a time
    // ---------------------------------------------------------------------------
    while (fread(buffer, 1, 512, card) == 512)
    {
        // STEP A: Check if this block starts a new JPEG by looking for signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // STEP B: If we already have an open file, close it before starting a new one
            if (img != NULL)
            {
                fclose(img);
            }

            // STEP C: Open a new output file
            // Use sprintf to create a string with the 3-digit filename (e.g., 001.jpg)
            sprintf(filename, "%03i.jpg", count);
            img = fopen(filename, "wb");
            
            // Increment count for the next JPEG found
            count++;
        }

        // STEP D: If we currently have an open output file, write the current block to it
        // This ensures the header block AND subsequent data blocks are saved
        if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }

    // ---------------------------------------------------------------------------
    // TODO 5: Close any remaining open file and close the card
    // ---------------------------------------------------------------------------
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);

    return 0;
}
