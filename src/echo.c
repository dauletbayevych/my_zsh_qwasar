#include "../include/include.h"

int check_insert_file(argument *table)
{
    int index = 1;

    while (index < table->size)
    {
        if (my_strcmp(table->args[index], ">>") == 0)
            return index;
        index++;
    }

    return 0;
}

status_t write_to_file(argument *table, int where)
{
    if (table->args[where + 1] != NULL)
    {
        my_putstr("Echo to only one file allowed.\n");
        return ERROR;
    }

    int fd = open(table->args[where], O_CREAT | O_RDWR | O_APPEND, S_IRWXU),
        index = 1;

    if (fd < 0)
    {
        my_putstr("Error File open.\n");
        return ERROR;
    }

    while (index < where - 1)
    {
        my_putchar(fd, table->args[index]);
        if (index + 1 != where - 1)
            write(fd, " ", my_strlen(" "));
        index++;
    }

    write(fd, "\n", my_strlen("\n"));

    return SUCCESS;
}

char *cut_dollar(char *str)
{
    int i = 1;

    while (str[i])
    {
        str[i - 1] = str[i];
        i++;
    }
    str[i - 1] = '\0';

    return str;
}

char *cut_variable(char *str)
{

    int index = 0,
        cur = 0;
    char *ret = malloc(sizeof(char) * MAX_STR_LEN);

    while (str[index] != '=')
        index++;

    index++;
    while (str[index])
    {
        if (str[index] != ':')
        {
            ret[cur] = str[index];
            cur++;
        }
        else
        {
            ret[cur] = ' ';
            cur++;
        }
        index++;
    }
    ret[cur] = '\0';

    return ret;
}

status_t find_in_env(argument *table)
{
    if (table->size != 3)
    {
        my_putstr("Can check one variable in ENV at a time.\n");
        return ERROR;
    }

    table->args[1] = cut_dollar(table->args[1]);

    int index = 0;

    while (index < table->env_length)
    {
        if (check_variable_exist(table->args[1], table->env[index]) == 1)
        {
            char *var = cut_variable(table->env[index]);
            my_putstr(var);
            my_putstr("\n");
            free(var);
            return SUCCESS;
        }
        index++;
    }

    my_putstr("No match found.");
    my_putstr("\n");
    return ERROR;
}

status_t echo(argument *table)
{
    int where = check_insert_file(table),
        index = 1;

    if (table->args[1][0] == '$')
    {
        return find_in_env(table);
    }

    if (where == 0)
    {
        while (table->args[index])
        {
            my_putchar(0, table->args[index]);
            if (table->args[index + 1] != NULL)
                my_putstr(" ");
            index++;
        }
    }
    else
    {
        if (write_to_file(table, where + 1) == ERROR)
            return ERROR;
    }
    my_putstr("\n");
    return SUCCESS;
}
