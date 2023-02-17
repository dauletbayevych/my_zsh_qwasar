#include "../include/include.h"

size_t my_strlen(char *str)
{
    size_t size = 0;
    if(!str)
        return size;

    while (str[size])
        size++;

    return size + 1;
}

int is_exec(char *str)
{
    if(!str)
        return 0;

    if (str[0] == '.' && str[1] == '/')
        return 1;
    return 0;
}

char *my_strcpy(char *dest, char *src)
{
    if(!src)
        return NULL;

    while (*src != '\0')
    {
        *dest++ = *src++;
    }
    *dest = '\0';

    return dest;
}

int my_strcmp(char *ptr1, char *ptr2)
{
    int i = 0;

    if(!ptr1 || !ptr2)
        return -1;

    while ((ptr1[i] != '\0') || (ptr2[i] != '\0'))
    {
        if (ptr1[i] > ptr2[i])
            return 1;
        if (ptr1[i] < ptr2[i])
            return -1;
        i++;
    }

    return 0;
}

int is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return 1;

    return 0;
}

int is_char(char c)
{
    if (c >= 'A' && c <= 'Z')
        return 1;

    return 0;
}

int arg_count(char *str)
{

    int index = 0,
        size = 1;

    while (str[index])
    {
        if (str[index] == ' ')
            size++;
        
        index++;
    }

    return size;
}

int my_getchar()
{
    static char buff[MAX_STR_LEN],
        *buff_ptr = buff;
    static int index = 0;

    if (index == 0)
    {
        index = read(0, buff, 1);
        buff_ptr = buff;
    }

    if (--index >= 0)
        return *buff_ptr++;

    return EOF;
}

void my_putstr(char *str)
{
    write(0, str, my_strlen(str));
}

void my_putchar(int fd, char *str)
{
    int index = 0;

    while (str[index])
    {
        if (str[index] != '"')
        {
            write(fd, &str[index], 1);
        }
        index++;
    }
}

char *my_strcat(char *dest, char *src)
{
    char *ptr = dest + strlen(dest);

    while (*src != '\0')
    {
        *ptr++ = *src++;
    }
    *ptr = '\0';

    return dest;
}
