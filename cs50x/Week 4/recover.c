#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *raw = fopen(argv[1], "r");
    uint8_t buffer[512]; // Create an array of 512 bytes
    bool jpeg_found = false;
    int counter = 0;  // Used to name jpg files
    char filename[8]; // To store "###.jpg" + null terminator
    FILE *img = NULL;

    while (fread(buffer, 1, 512, raw))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            jpeg_found = true;
        }
        if (jpeg_found)
        {
            if (counter != 0)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter); // Make a new jpeg so that Each .jpg file
                                                    // contains only the data for one photo
            img = fopen(filename, "w");             // Opens a new file for writing
            fwrite(buffer, 1, 512, img);
            jpeg_found = false;
            counter++;
        }
        else if (counter != 0)
        {
            fwrite(buffer, 1, 512, img); // Store the slack cells
        }
    }
    fclose(raw);
    fclose(img);
}
