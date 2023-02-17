#include "../include/include.h"

char *my_readline()
{
    char *buffer = NULL;
    buffer = malloc(sizeof(char) * MAX_STR_LEN);
    memset(buffer, '\0', MAX_STR_LEN);

    int read_input = STDIN_FILENO;

    int last = read(read_input, buffer, MAX_STR_LEN);
    buffer[last - 1] = '\0';

    return buffer;
}
