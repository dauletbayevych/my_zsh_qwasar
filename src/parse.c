#include "../include/include.h"

int get_input_size(char *str, int index)
{
    int size = 0;

    while (str[index] && str[index] != ' ')
    {
        size++;
        index++;
    }

    return size;
}

char *store_arg(char *str, int index, int size)
{
    int cur = 0;

    if(!str[index])
        return NULL;

    size++;
    char *arg = malloc(sizeof(char) * size);

    while (cur < size-1)
    {
        arg[cur] = str[index];
        cur++;
        index++;
    }
    arg[cur] = '\0';
    return arg;
}

void print_argument(argument *table)
{
    printf("%d\n", table->command);
    for (int i = 0; i < table->size; i++)
        printf("%s ", table->args[i]);

    printf("\n");
}

builtins_t get_command(argument *table)
{
    if (my_strcmp(table->args[0], "echo") == 0)
        return ECHO;
    if (my_strcmp(table->args[0], "cd") == 0)
        return CD;
    if (my_strcmp(table->args[0], "setenv") == 0)
        return SETENV;
    if (my_strcmp(table->args[0], "unsetenv") == 0)
        return UNSETENV;
    if (my_strcmp(table->args[0], "env") == 0)
        return ENV;
    if (my_strcmp(table->args[0], "exit") == 0)
        return EXIT;
    if (my_strcmp(table->args[0], "pwd") == 0)
        return PWD;
    if (my_strcmp(table->args[0], "which") == 0)
        return WHICH;
    if (is_exec(table->args[0]) == 1)
        return RUN;

    return EXECUTE;
}

void free_argument(argument *table)
{
    for (int i = 0; i < table->size-1; i++)
        free(table->args[i]);

    free(table->args);
}

void free_env(argument *table){

    for (int i = 0; i < table->env_length-1; i++)
        free(table->env[i]);

    free(table->env);
}

void free_paths(argument *table){
    
    for (int i = 0; i < table->paths_size; i++)
        free(table->paths[i]);

    free(table->paths);
}

void free_table(argument *table){

    free_paths(table);
    free_env(table);
    free(table);
}

int get_paths_amount(char *str)
{
    int index = 0,
        count = 1;

    while (str[index])
    {
        if (str[index] == ' ')
            count++;
        index++;
    }
    return count;
}

char *add_paths(char *path)
{
    static int index = 0;
    int cur = 0;

    char *ret = malloc(sizeof(char) * MAX_STR_LEN);

    while (path[index] != ' ' && path[index] != '\0')
    {
        ret[cur] = path[index];
        cur++;
        index++;
    }

    ret[cur] = '\0';
    index++;

    return ret;
}

char **get_paths(argument *table)
{
    if(table->env_length == 0)
        return NULL;

    int index = 0;
    char *paths;

    while (index < table->env_length)
    {
        if (check_variable_exist("PATH", table->env[index]) == 1)
        {
            paths = cut_variable(table->env[index]);
        }
        index++;
    }

    table->paths_size = get_paths_amount(paths);
    char **ret = malloc(sizeof(char *) * table->paths_size);

    for (int i = 0; i < table->paths_size; i++)
    {
        ret[i] = add_paths(paths);
    }
    free(paths);
    return ret;
}

char **parse_input(argument *table, char *input)
{
    int index = 0,
        size = 0;

    if(!input)
        return NULL;
    
    table->size++;
    table->args = malloc(sizeof(char *) * (table->size));

    for (int i = 0; i < table->size; i++)
    {
        size = get_input_size(input, index);
        index += size + 1;
        table->args[i] = store_arg(input, index - size - 1, size);
    }

    table->command = get_command(table);
    /* print_argument(table); */
    return table->args;
}
