#include "type.h"
#include "view.h"
#include "mp3_edit.h"

/**
 * Function: read_and_validate_edit
 * Description: Validates the command-line arguments for editing MP3 metadata.
 * Input: argv - the array of arguments, mp3Edit - pointer to the Mp3EditInfo struct.
 * Output: Returns success if the arguments are valid, or failure if any validation check fails.
 */
Status read_and_validate_edit(char *argv[], Mp3EditInfo *mp3Edit)
{
    char extn[10];
    // Check if filename contains extension or not
    if (strchr(argv[4], '.') == NULL)
    {
        printf("-------------------------------------------------------------------------------\n\n");
        printf("ERROR: ./a.out : INVALID EXTENSION\n");
        printf("-------------------------------------------------------------------------------\n");
        return failure;
    }
    // Copy extn and check extn is mp3 or not
    strcpy(extn, strchr(argv[4], '.'));
    if (strcmp(extn, ".mp3") != 0)
    {
        printf("-------------------------------------------------------------------------------\n\n");
        printf("ERROR: ./a.out : INVALID EXTENSION\n");
        printf("-------------------------------------------------------------------------------\n");
        return failure;
    }
    // Copy filename to structure member
    mp3Edit->src_fname = argv[4];
    // Initialize output filename
    strcpy(mp3Edit->out_fname, "temp.mp3");
    // Validate edit mode option entered by user
    if (strcmp(argv[2], "-t") != 0 && strcmp(argv[2], "-a") != 0 && strcmp(argv[2], "-A") != 0 && strcmp(argv[2], "-m") != 0 && strcmp(argv[2], "-y") != 0 && strcmp(argv[2], "-c") != 0)
    {
        printf("-------------------------------------------------------------------------------\n\n");
        printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
        printf("USAGE :\nTo edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
        printf("-------------------------------------------------------------------------------\n");
        return failure;
    }
    // Copy user entered edit option
    mp3Edit->frame = argv[2];
    // Copy new data to be modified
    mp3Edit->modify_data = argv[3];
    // Store the length of new data
    mp3Edit->data_length = strlen(mp3Edit->modify_data) + 1;
    return success;
}

/**
 * Function: edit_info
 * Description: Edits the MP3 file's metadata based on user input.
 * Input: mp3Edit - pointer to the Mp3EditInfo struct.
 * Output: Returns success if the metadata is edited successfully, or failure if any error occurs.
 */
Status edit_info(Mp3EditInfo *mp3Edit)
{
    // Open source and duplicate files
    if (open_files(mp3Edit) == failure)
    {
        printf("Error in opening files\n");
        return failure;
    }
    // Check for file is ID3 format or not
    if (check_ID3(mp3Edit) == failure)
    {
        printf("Invalid Mp3 ID format\n");
        return failure;
    }
    // Check mp3file version is valid
    if (check_mp3version(mp3Edit) == failure)
    {
        printf("Invalid ID3 version\n");
        return failure;
    }
    // Copy header data to duplicate file
    if (copy_header(mp3Edit->fptr_out, mp3Edit->fptr_src) == failure)
    {
        printf("Error in copying header\n");
        return failure;
    }
    // Flag to indicate whether we need to continue or copying is completed
    int flag = 0;
    // Do check frame is TIT2 and whether user need to modify title
    if (do_change(mp3Edit, "TIT2", "-t", &flag) == failure || (flag))
    {
        // Modification completed if flag is set , No need to continue
        if (flag)
        {
            printf("----------CHANGE THE TITLE-------------\n\n");
            printf("TITLE   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------TITLE CHANGED SUCCESSFULLY----------\n\n");
            return success;
        }
        printf("Error\n");
        return failure;
    }
    // Do check frame is TPE1 and whether user need to modify artist
    if (do_change(mp3Edit, "TPE1", "-a", &flag) == failure || (flag))
    {
        // Modification completed if flag is set , No need to continue
        if (flag)
        {
            printf("----------CHANGE THE ARTIST-------------\n\n");
            printf("ARTIST   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------ARTIST CHANGED SUCCESSFULLY----------\n\n");
            return success;
        }
        printf("Error\n");
        return failure;
    }
    // Do check frame is TALB and whether user need to modify album
    if (do_change(mp3Edit, "TALB", "-A", &flag) == failure || (flag))
    {
        // Modification completed if flag is set , No need to continue
        if (flag)
        {
            printf("----------CHANGE THE ALBUM-------------\n\n");
            printf("ALBUM   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------ALBUM CHANGED SUCCESSFULLY----------\n\n");
            return success;
        }
        printf("Error\n");
        return failure;
    }
    // Do check frame is TYER and whether user need to modify year
    if (do_change(mp3Edit, "TYER", "-y", &flag) == failure || (flag))
    {
        // Modification completed if flag is set , No need to continue
        if (flag)
        {
            printf("----------CHANGE THE YEAR-------------\n\n");
            printf("YEAR   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------YEAR CHANGED SUCCESSFULLY----------\n\n");
            return success;
        }
        printf("Error\n");
        return failure;
    }
    // Do check frame is TCON and whether user need to modify content
    if (do_change(mp3Edit, "TCON", "-m", &flag) == failure || (flag))
    {
        // Modification completed if flag is set , No need to continue
        if (flag)
        {
            printf("----------CHANGE THE CONTENT-------------\n\n");
            printf("CONTENT   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------CONTENT CHANGED SUCCESSFULLY----------\n\n");
            return success;
        }
        printf("Error\n");
        return failure;
    }
    // Do check frame is COMM and whether user need to modify comment
    if (do_change(mp3Edit, "COMM", "-c", &flag) == failure || (flag))
    {
        // Modification completed if flag is set , No need to continue
        if (flag)
        {
            printf("----------CHANGE THE COMMENT-------------\n\n");
            printf("COMMENT   : %s\n\n", mp3Edit->modify_data);
            fclose(mp3Edit->fptr_src);
            fclose(mp3Edit->fptr_out);
            file_copy(mp3Edit);
            printf("----------COMMENT CHANGED SUCCESSFULLY----------\n\n");
            return success;
        }
        printf("Error\n");
        return failure;
    }
    return success;
}

/**
 * Function: open_files
 * Description: Opens the source and duplicate MP3 files.
 * Input: mp3Edit - pointer to the Mp3EditInfo struct.
 * Output: Returns success if the files are opened successfully, or failure if there is an error opening the files.
 */
Status open_files(Mp3EditInfo *mp3Edit)
{
    // Open original mp3 file and validate whether its opened or not
    mp3Edit->fptr_src = fopen(mp3Edit->src_fname, "r");
    if (mp3Edit->fptr_src == NULL)
    {
        perror("Error opening source file");
        return failure;
    }
    // Open a duplicate file and validate whether its opened or not
    mp3Edit->fptr_out = fopen(mp3Edit->out_fname, "w");
    if (mp3Edit->fptr_out == NULL)
    {
        perror("Error opening temp file");
        return failure;
    }
    return success;
}

/**
 * Function: check_ID3
 * Description: Checks if the MP3 file has a valid ID3 header.
 * Input: mp3Edit - pointer to the Mp3EditInfo struct.
 * Output: Returns success if the header is valid, or failure if there is an error.
 */
Status check_ID3(Mp3EditInfo *mp3Edit)
{
    // Read 3 bytes from source and check if its ID3 or not
    char buffer[3];
    fread(buffer, 3, 1, mp3Edit->fptr_src);
    buffer[3] = '\0';      
    if (strcmp(buffer, "ID3") != 0)
    {
        return failure;
    }
    return success;
}

/**
 * Function: check_mp3version
 * Description: Checks if the MP3 file has a valid ID3 version.
 * Input: mp3Edit - pointer to the Mp3EditInfo struct.
 * Output: Returns success if the version is valid, or failure if there is an error.
 */
Status check_mp3version(Mp3EditInfo *mp3Edit)
{
    // Read 2 bytes from source file and check for its version
    short version;
    fread(&version, 2, 1, mp3Edit->fptr_src);
    if (version != 3)
    {
        return failure;
    }
    return success;
}

/**
 * Function: copy_header
 * Description: Copies the header from the source file to the duplicate file.
 * Input: fptr_dest - the file pointer of the duplicate file, fptr_src - the file pointer of the source file.
 * Output: Returns success if the header is copied successfully, or failure if there is an error.
 */
Status copy_header(FILE *fptr_dest, FILE *fptr_src)
{
    // Rewind both pointers to file start position
    rewind(fptr_dest);
    rewind(fptr_src);
    // Read and write 10 bytes from source to dest file
    char header[10];
    fread(header, 10, 1, fptr_src);
    fwrite(header, 10, 1, fptr_dest);
    return success;
}

/**
 * Function: do_change
 * Description: Performs the modification of the specified frame in the MP3 file.
 * Input: mp3Edit - pointer to the Mp3EditInfo struct, str - the frame ID, frame - the frame option, flag - pointer to the flag indicating whether the modification is completed.
 * Output: Returns success if the modification is performed successfully, or failure if there is an error.
 */
Status do_change(Mp3EditInfo *mp3Edit, char str[], char frame[], int *flag)
{
    // Check frame is matching with source file
    if (check_frame(mp3Edit, str) == failure)
    {
        printf("Frame Matching Error\n");
        return failure;
    }
    // Check user need to modify the particular frame data or not
    if (strcmp(mp3Edit->frame, frame) == 0)
    {
        // Modify the data
        modify_data(mp3Edit);
        // Seek the source file pointer to old data times
        fseek(mp3Edit->fptr_src, mp3Edit->size - 1, SEEK_CUR);
        // Copy the remaning data from source to duplicate file
        copy_remaining(mp3Edit->fptr_out, mp3Edit->fptr_src);
        // Set flag to indicate modification is done
        *flag = 1;
        return success;
    }
    // If user dont need to modify this frame , copy the same from source to duplicate
    if (copy_same(mp3Edit) == failure)
    {
        printf("Error in copying title\n");
        return failure;
    }
    return success;
}

/**
 * Function: check_frame
 * Description: Checks if the specified frame exists in the MP3 file.
 * Input: mp3Edit - pointer to the Mp3EditInfo struct, str - the frame ID.
 * Output: Returns success if the frame exists, or failure if there is an error.
 */
Status check_frame(Mp3EditInfo *mp3Edit, char str[])
{
    // Read 4 bytes from source
    char buffer[4];
    fread(buffer, 4, 1, mp3Edit->fptr_src);
    // Check frame is matching or not
    if (strcmp(buffer, str) != 0)
    {
        return failure;
    }
    // Write frame to duplicate file
    fwrite(buffer, 4, 1, mp3Edit->fptr_out);
    // Read existing data size from source
    fread(&mp3Edit->size, 4, 1, mp3Edit->fptr_src);
    // Convert to big endian as it is stored in little endian
    convert_endianess((char *)&mp3Edit->size, sizeof(int));
    return success;
}

/**
 * Function: modify_data
 * Description: Modifies the data of the specified frame in the MP3 file.
 * Input: mp3Edit - pointer to the Mp3EditInfo struct.
 * Output: Returns success if the data is modified successfully, or failure if there is an error.
 */
Status modify_data(Mp3EditInfo *mp3Edit)
{
    // Convert new data size endianess before storing
    convert_endianess((char *)&mp3Edit->data_length, sizeof(int));
    // Write new data size to duplicate file
    fwrite(&mp3Edit->data_length, 4, 1, mp3Edit->fptr_out);
    // Copy flags from source to duplicate file
    char flag[3];
    fread(flag, 3, 1, mp3Edit->fptr_src);
    fwrite(flag, 3, 1, mp3Edit->fptr_out);
    // Write new data to duplicate file
    fwrite(mp3Edit->modify_data, strlen(mp3Edit->modify_data), 1, mp3Edit->fptr_out);
    return success;
}

/**
 * Function: copy_remaining
 * Description: Copies the remaining data from the source file to the duplicate file.
 * Input: fptr_dest - the file pointer of the duplicate file, fptr_src - the file pointer of the source file.
 * Output: Returns success if the data is copied successfully, or failure if there is an error.
 */
Status copy_remaining(FILE *fptr_dest, FILE *fptr_src)
{
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fptr_src)) > 0)
    {
        fwrite(buffer, 1, bytesRead, fptr_dest);
    }
    return success;
}

/**
 * Function: copy_same
 * Description: Copies the same data from the source file to the duplicate file.
 * Input: mp3Edit - pointer to the Mp3EditInfo struct.
 * Output: Returns success if the data is copied successfully, or failure if there is an error.
 */
Status copy_same(Mp3EditInfo *mp3Edit)
{
    // Copy the old size stored in structure
    int size = mp3Edit->size;
    // Convert endianess and write to duplicate file
    convert_endianess((char *)&size, sizeof(int));
    fwrite(&size, 4, 1, mp3Edit->fptr_out);
    // Copy the 2 flags and null character from source to duplicate
    char flag[3];
    fread(flag, 3, 1, mp3Edit->fptr_src);
    fwrite(flag, 3, 1, mp3Edit->fptr_out);
    // Copy the same data from source to duplicate file
    char data[mp3Edit->size];
    fread(data, mp3Edit->size - 1, 1, mp3Edit->fptr_src);
    fwrite(data, mp3Edit->size - 1, 1, mp3Edit->fptr_out);
    return success;
}

/**
 * Function: file_copy
 * Description: Copies the modified file to the original file.
 * Input: mp3Edit - pointer to the Mp3EditInfo struct.
 * Output: Returns success if the file is copied successfully, or failure if there is an error.
 */
Status file_copy(Mp3EditInfo *mp3Edit)
{
    // Open both original file and duplicate file
    mp3Edit->fptr_src = fopen(mp3Edit->src_fname, "w");
    mp3Edit->fptr_out = fopen(mp3Edit->out_fname, "r");
    rewind(mp3Edit->fptr_src);
    rewind(mp3Edit->fptr_out);
    char ch;
    // Copy the Duplicate file to Original file, So the changes will be affected on original file
    while (fread(&ch, 1, 1, mp3Edit->fptr_out) > 0)
    {
        fwrite(&ch, 1, 1, mp3Edit->fptr_src);
    }
    return success;
}

/**
 * Function: convert_endianess
 * Description: Converts the byte order of the data from little-endian to big-endian.
 * Input: ptr - pointer to the data to be reversed, size - size of the data.
 * Output: Reverses the byte order of the data in-place.
 */
void convert_endianess(char *ptr, int size)
{
    char temp;
    for (int i = 0; i < size / 2; i++)
    {
        temp = ptr[i];
        ptr[i] = ptr[size - i - 1];
        ptr[size - i - 1] = temp;
    }
}