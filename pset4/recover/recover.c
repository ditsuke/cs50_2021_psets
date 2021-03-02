#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// define a "BYTE" as an 8 bit unsigned int
typedef uint8_t BYTE;

// Funtion prototype(s)
bool matchJPEG_sig(BYTE *buffer);

int main(int argc, char *argv[])
{
    // Return with exit code 1 if arg_count != 2
    if (argc != 2)
    {
        printf("Usage: ./recover <image>\n");
        return 1;
    }

    // Stores input file name
    char *raw_in = argv[1];

    // Input file stream
    FILE *instr = fopen(raw_in, "rb");

    // Output file stream
    FILE *outstr =  NULL;

    // Return with exit code 2 if input file couldn't be opened
    if (instr == NULL)
    {
        printf("Cannot open input file!\nCheck if file exists and you have r/w "
               "permissions to it...");
        return 2;
    }

    // Stores the most recently read FAT block (512 bytes) from ptr instr
    BYTE cbuffer[512];
    // True if a JPEG signature is found
    bool sigFound = false;
    // Stores number of elements read by fread
    int elread = 512;
    // Stores output JPEG count
    int fno = 0;
    // Stores base filename
    char outname[30];

    while (true)
    {
        // Read a FAT block into cbuffer
        if (sigFound != true)
        {
            elread = fread(cbuffer, sizeof(BYTE), 512, instr);
        } 
        // Break loop if EOF is reached
        if (elread != 512)
        {
            printf("EOF reached!\n");
            break;
        } 
        // If signature is found, close old file (if exists), open new one...
        else if (matchJPEG_sig(cbuffer) && sigFound != true)
        {
            sigFound = true;
            (outstr != NULL) ? (fclose(outstr)) : (0);

            // Print filename to var
            sprintf(outname, "%03i.jpg", fno++);
            // Open outname
            outstr = fopen(outname, "w");
            continue;
        } 
        // Write / keep writing file otherwise
        else
        {
            sigFound = false;
            (outstr != NULL) ? (fwrite(cbuffer, sizeof(BYTE), 512, outstr)) : (0);
        }
    }
    fclose(outstr);
    fclose(instr);
    return 0;
}

bool matchJPEG_sig(BYTE *buffer)
{
    // "posx[x]" stores byte(s) corresponding to position 'x' of JPEG signature
    BYTE posx[] = {0xff, 0xd8, 0xff};
    // Store all possible bytes for position 3
    BYTE pos_3[] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
                    0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef
                   };

    // Keep track of consecutive bytes matching pattern found
    int pos = 0;

    while (true)
    {
        // Increment pos if buffer[posx[pos]] == posx[pos]
        if ((pos == 0 || pos == 1 || pos == 2) && buffer[pos] == posx[pos])
        {
            pos++;
            continue;
        } 
        else if (pos == 3)
        {
            // Iterate over array of 4th positive byte match
            // A better design approach is possible using a binary operator.
            for (int i = 0; i < 16; i++)
            {
                // Increment pos if byte in array found
                if (buffer[pos] == pos_3[i])
                {
                    pos++;
                    break;
                }
            }
        }
        // Break out of loop if no increment condition met
        else
        {
            break;
        }
    }

    // Return true if JPEG pattern found (4 consecutive bytes matching pattern)
    bool isMatch = (pos == 4) ? (true) : (false);
    return isMatch;
}