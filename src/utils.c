#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void __dats_raise_error(const char *message, const char *filename, int line)
{
    fprintf(stderr, "[ERROR]: %s in file: %s at line: %d.\n", message, filename, line);
    exit(EXIT_FAILURE);
}

void *__dats_oom_guard(void *ptr, const char *filename, int line)
{
    if (ptr == NULL)
    {
        __dats_raise_error("Unable to get memory from system.", filename, line);
    }
    return ptr;
}
