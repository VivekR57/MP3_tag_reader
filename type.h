#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define BUFFER_SIZE 4096 // 4KB buffer

// Enum to represent the type of operation being performed
typedef enum
{
    edit,   // Operation to edit MP3 metadata
    view,   // Operation to view MP3 metadata
    help,   // Operation to display help/usage information
    failure // Indicates an invalid or failed operation
} OperationType;

// Enum to represent the status of a function or operation
typedef enum
{
    success,  // Indicates that the operation was successful
    e_failure // Indicates that the operation failed
} Status;

#endif // TYPE_H