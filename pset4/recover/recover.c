#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// memory image is from a FAT filesystem with 512b block size
#define BLOCK_SIZE 512

typedef uint8_t BYTE;

// funtion prototype(s)
bool matchJPEG_sig(BYTE *buffer);

int main(int argc, char *argv[]) {
    // return with exit code 1 if exactly one argument is not present
    if (argc != 2) {
        printf("Usage: ./recover <image>\n");
        return 1;
    }

    // store input file name
    char *raw_in = argv[1];
    // input file stream
    FILE *instr;
    instr = fopen(raw_in, "rb");
    // outfile stream
    FILE *outstr;
    outstr = NULL;

    // return with exit code 2 if input file cannot be opened
    if (instr == NULL) {
        printf(
            "Cannot open input file!\nCheck if file exists and you have r/w "
            "permissions to it...");
        return 2;
    }

    // stores the most recently read FAT block (512 bytes) from ptr instr
    BYTE cbuffer[BLOCK_SIZE];
    // true if a JPEG signature is found
    bool sigFound = false;
    // stores number of elements read by fread
    int elread = BLOCK_SIZE;
    // stores output JPEG count
    int fno = 0;
    // store base filename
    char outname[30];

    while (true) {
        // read a FAT block into cbuffer
        if (sigFound != true) {
            elread = fread(cbuffer, sizeof(BYTE), BLOCK_SIZE, instr);
        }  // break loop and close files if EOF is reached
        if (elread != BLOCK_SIZE) {
            printf("EOF reached!\n");
            fclose(instr);
            (outstr != NULL) ? (fclose(outstr)) : (0);
            break;
        }  // if signature is found, close old file (if exists), open new one...
        else if (matchJPEG_sig(cbuffer) && sigFound != true) {
            sigFound = true;
            // close outstr if open
            (outstr != NULL) ? (fclose(outstr)) : (0);
            // print filename to var
            sprintf(outname, "recovered2/%03i.jpg", fno++);
            // open outname with ptr outstr
            outstr = fopen(outname, "w");
            continue;
        }  // write file
        else {
            sigFound = false;
            (outstr != NULL)
                ? (fwrite(cbuffer, sizeof(BYTE), BLOCK_SIZE, outstr))
                : (0);
        }
    }

    return 0;
}

bool matchJPEG_sig(BYTE *buffer) {
    bool isMatch = (buffer[0] == 0xff && buffer[1] == 0xd8 &&
                    buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
                       ? (1)
                       : (0);
    return isMatch;
}