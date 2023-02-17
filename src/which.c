#include "../include/include.h"

builtins_t is_builtins(char *str)
{
    builtins_t ret = UNKNOWN;
    if (my_strcmp(str, "echo") == 0)
        ret = ECHO;
    if (my_strcmp(str, "cd") == 0)
        ret = CD;
    if (my_strcmp(str, "setenv") == 0)
        ret = SETENV;
    if (my_strcmp(str, "unsetenv") == 0)
        ret = UNSETENV;
    if (my_strcmp(str, "env") == 0)
        ret = ENV;
    if (my_strcmp(str, "exit") == 0)
        ret = EXIT;
    if (my_strcmp(str, "pwd") == 0)
        ret = PWD;
    if (my_strcmp(str, "which") == 0)
        ret = WHICH;

    if(ret != UNKNOWN){
        char ret_msg[MAX_STR_LEN];
        my_strcpy(ret_msg, str);
        my_strcat(ret_msg, ": shell built-in command\n");
        my_putstr(ret_msg);
    }

    return ret;
}

status_t which(argument *table)
{

    int index = 1, i = 0;
    char ret_msg[MAX_STR_LEN];
    DIR *dir;

    if(is_builtins(table->args[index]) != UNKNOWN)
        return SUCCESS;

    while (i < table->paths_size)
    {
        dir = opendir(table->paths[i]);

        if (!dir)
        {
            perror("dir");
            return ERROR;
        }

        while (table->args[index])
        {
            struct dirent *current_file;
            current_file = readdir(dir);
            for (; current_file;)
            {
                if (!my_strcmp(table->args[index], current_file->d_name))
                {
                    my_strcpy(ret_msg, table->paths[i]);
                    my_strcat(ret_msg, "/");
                    my_strcat(ret_msg, current_file->d_name);
                    my_strcat(ret_msg, "\n");
                    my_putstr(ret_msg);
                    goto found;
                }
                current_file = readdir(dir);
            }
            index++;
        }
        index = 1;
        i++;
        closedir(dir);
    }
    my_strcpy(ret_msg, table->args[index]);
    my_strcat(ret_msg, " not found.\n");
    my_putstr(ret_msg);
    return ERROR;

found:
    closedir(dir);
    return SUCCESS;
}
