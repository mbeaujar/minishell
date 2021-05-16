#include "minishell.h"

char *ft_secure_strdup(const char *str)
{
    int i;
    int len;
    char *new;

    i = 0;
    len = 0;
    if(!str)
        return (NULL);
    while(str[i])
    {
        if(str[i] > 0)
            len++;
        i++;
    }
    if((new = malloc(sizeof(char) * (len + 1))) == NULL)
        return (NULL);
    i = 0;
    len = 0;
    while(str[i])
    {
        if(str[i] > 0)
        {
            new[len] = str[i];
            len++;
        }
        i++;
    }
    new[len] = '\0';
    return (new);
}