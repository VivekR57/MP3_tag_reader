#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include "type.h"

/**
 * Structure to hold music file information.
 */
typedef struct
{
    char *Filename;   // Name of the MP3 file
    FILE *fptr_fname; // File pointer for the MP3 file
} Music;

// Function prototypes
OperationType check_operation_type(char *argv);
Status read_and_validate(int argc, char *argv[], Music *music);
void printHelp();
Status viewInfo(Music *music);
Status openFiles(Music *music);
Status closeFiles(Music *music);
Status checkheaderandversion(FILE *fname);
Status read_info(Music *music, const char *tag);
void little_to_big(char *ptr, int size);

#endif // VIEW_H