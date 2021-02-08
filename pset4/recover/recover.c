#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
    BYTE cbuffer[512];
    // true if a JPEG signature is found
    bool sigFound = false;
    // stores number of elements read by fread
    int elread = 512;
    // stores output JPEG count
    int fno = 0;
    // store base filename
    char outname[30];

    while (true) {
        // read a FAT block into cbuffer
        if (sigFound != true) {
            elread = fread(cbuffer, sizeof(BYTE), 512, instr);
        }  // break loop if EOF is reached
        if (elread != 512) {
            printf("EOF reached!\n");
            break;
        }  // if signature is found, close old file (if exists), open new one...
        else if (matchJPEG_sig(cbuffer) && sigFound != true) {
            sigFound = true;
            // close outstr if open
            (outstr != NULL) ? (fclose(outstr)) : (0);
            // print filename to var
            sprintf(outname, "%03i.jpg", fno++);
            // open outname with ptr outstr
            outstr = fopen(outname, "w");
            continue;
        }  // write file
        else {
            sigFound = false;
            (outstr != NULL) ? (fwrite(cbuffer, sizeof(BYTE), 512, outstr))
                             : (0);
        }
    }
    fclose(outstr);
    fclose(instr);
    return 0;
}

bool matchJPEG_sig(BYTE *buffer) {
    BYTE pos0 = 0xff, pos1 = 0xd8, pos2 = 0xff;
    BYTE pos3[] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
                   0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef};

    int pos = 0;

    while (true) {
        if (pos == 0 && buffer[pos] == pos0) {
            pos++;
            continue;
        } else if (pos == 1 && buffer[pos] == pos1) {
            pos++;
            continue;
        } else if (pos == 2 && buffer[pos] == pos2) {
            pos++;
            continue;
        } else if (pos == 3) {
            for (int i = 0; i < 16; i++) {
                if (buffer[pos] == pos3[i]) {
                    pos++;
                    break;
                }
            }
        } else {
            break;
        }
    }
    bool isMatch = (pos == 4) ? (true) : (false);
    return isMatch;
}