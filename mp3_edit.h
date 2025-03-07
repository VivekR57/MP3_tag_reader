#ifndef MP3_EDIT_H
#define MP3_EDIT_H

#include "type.h"

/**
 * Structure to hold MP3 editing-related information
 */
typedef struct Mp3EditInfo
{
    char *src_fname;      // Source MP3 file name
    FILE *fptr_src;       // File pointer for the source MP3 file

    char out_fname[20];   // Output MP3 file name (edited version)
    FILE *fptr_out;       // File pointer for the output MP3 file

    char *modify_data;    // Data to be modified in the MP3 file
    int data_length;      // Length of the data to be modified
    char *frame;          // Frame identifier for editing (e.g., "TIT2" for title)

    int size;             // Size of the frame data
} Mp3EditInfo;

// Function prototypes
Status read_and_validate_edit(char *argv[], Mp3EditInfo *mp3Edit);
Status edit_info(Mp3EditInfo *mp3Edit);
Status open_files(Mp3EditInfo *mp3Edit);
Status check_ID3(Mp3EditInfo *mp3Edit);
Status check_mp3version(Mp3EditInfo *mp3Edit);
Status copy_header(FILE *fptr_dest, FILE *fptr_src);
Status do_change(Mp3EditInfo *mp3Edit, char str[], char frame[], int *flag);
Status check_frame(Mp3EditInfo *mp3Edit, char str[]);
Status modify_data(Mp3EditInfo *mp3Edit);
Status copy_remaining(FILE *fptr_dest, FILE *fptr_src);
Status copy_same(Mp3EditInfo *mp3Edit);
Status file_copy(Mp3EditInfo *mp3Edit);
void convert_endianess(char *ptr, int size);

#endif // MP3_EDIT_H