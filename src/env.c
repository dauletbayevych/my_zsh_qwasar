#include "../include/include.h"

status_t env(argument *table)
{
    for (int i = 0; i < table->env_length-1; i++)
    {
        printf("%s\n", table->env[i]);
    }

    return SUCCESS;
}

int env_length(char **env)
{
    int i = 0;

    for (; *env; env++)
        i++;

    return i+1;
}

char **get_env(argument *table, char **env)
{
    if(*env == NULL){
        table->env_length = 0;
        return NULL;
    }

    table->env_length = env_length(env);

    int i = 0;
    table->env = malloc(sizeof(char *) * table->env_length);
    
    for (; *env; env++, i++)
    {
        table->env[i] = malloc(sizeof(char) * my_strlen(*env));
        my_strcpy(table->env[i], *env);
    }

    table->env[i] = NULL;
    return table->env;
}

int correct_char(char c)
{
    if (((is_char(c) == 1) && c != '\0') || is_digit(c) == 1 || c == '_')
    {
        return 1;
    }
    return 0;
}

char *get_variable(char *str)
{
    int index = 0;

    if(str == NULL)
        return NULL;

    char *variable = malloc(sizeof(char) * MAX_STR_LEN);

    while (str[index] != '=')
    {
        variable[index] = str[index];
        index++;
    }

    variable[index] = '\0';

    return variable;
}

int check_variable(char *str)
{
    int index = 0;

    while (str[index])
    {
        if (correct_char(str[index]) == 1)
            index++;
        else
        {
            return 0;
        }
    }

    return 1;
}

char *get_value(char *str)
{
    int index = 0,
        cur = 0;

    char *value = malloc(sizeof(char) * MAX_STR_LEN);

    while (str[index] != '=' && str[index])
        index++;

    index++;
    if (str[index] == '\0')
    {
        my_putstr("Values must not be empty.\n");
        return NULL;
    }

    while (str[index])
    {
        value[cur] = str[index];
        cur++;
        index++;
    }
    value[cur] = '\0';

    return value;
}

int check_variable_exist(char *new, char *exist)
{
    char *exist_var = get_variable(exist);

    if (!(my_strcmp(new, exist_var))){
        free(exist_var);
        return 1;
    }

    free(exist_var);
    return 0;
}

char **modify_variable(argument *table, int index)
{
    table->env[index] = malloc(sizeof(char) * my_strlen(table->args[2]));

    my_strcpy(table->env[index], table->args[2]);

    return table->env;
}

char **add_variable(argument *table)
{
    table->env_length += 1;

    char **ret = malloc(sizeof(char *) * table->env_length);

    for (int i = 0; i < table->env_length; i++)
    {
        if (i < table->env_length - 2)
        {
            ret[i] = malloc(sizeof(char) * my_strlen(table->env[i]));
            my_strcpy(ret[i], table->env[i]);
        }
        else if(i == table->env_length -1){
            ret[i] = NULL;
        }
        else
        {
            ret[i] = malloc(sizeof(char) * (my_strlen(table->args[2]) + my_strlen(table->args[1]) + 1));
            my_strcpy(ret[i], table->args[1]);
            my_strcat(ret[i], "=");
            my_strcat(ret[i], table->args[2]);
        }
    }

    free_env(table);

    return ret;
}

char **delete_variable(argument *table, int index)
{
    char **ret = malloc(sizeof(char *) * (table->env_length-1));

    for (int i = 0, j = 0; i < table->env_length-1; i++, j++)
    {
        if (i == index)
        {
            j++;
        }
        if(i == table->env_length -2){
            ret[i] = NULL;
            break;
    }
        ret[i] = malloc(sizeof(char) * my_strlen(table->env[j]));
        my_strcpy(ret[i], table->env[j]);
    }

    free_env(table);
    table->env_length -= 1;
    return ret;
}

status_t my_setenv(argument *table)
{
    if (table->size != 4)
    {
        my_putstr("setenv usage: setenv NEWVALUE value.\n");
        return ERROR;
    }

    if (check_variable(table->args[1]) == 0)
    {
        my_putstr("Variable name should have capital letters only.\n");
        my_putstr("setenv usage: setenv NEWVALUE value\n");
        return ERROR;
    }
    int i = 0;

    while (i < table->env_length)
    {
        if (check_variable_exist(table->args[1], table->env[i]) == 1)
        {
            table->env = modify_variable(table, i);
            my_putstr("Variable successfuly changed.\n");
            return SUCCESS;
        }
        i++;
    }

    table->env = add_variable(table);

    return SUCCESS;
}

status_t my_unsetenv(argument *table)
{
    if (table->size != 3)
    {
        my_putstr("unsetenv usage: unsetenv NEWVALUE.\n");
        return ERROR;
    }

    if (check_variable(table->args[1]) == 0)
    {
        my_putstr("Incorrect variable name.\n");
        return ERROR;
    }

    int i = 0;

    while (table->env[i])
    {
        if (check_variable_exist(table->args[1], table->env[i]) == 1)
        {
            table->env = delete_variable(table, i);
            my_putstr("Variable successfuly deleted.\n");
            return SUCCESS;
        }
        i++;
    }

    my_putstr("Variable was not found.\n");
    return ERROR;
}
