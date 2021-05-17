#include "minishell.h"


char *ft_strfrom_tab(char **argv, char *sep)
{
    int len;
    int i;
    char *str = NULL;
    int len_g;

    len = 0;
    i = 0;
    len_g = ft_strlen_tab(argv);
    while(i < len_g)
        len += ft_strlen(argv[i++]);
    if((str = malloc(sizeof(char) * (len + i))) == NULL)
        return (NULL);
    len = 0;
    while(len < i)
    {
        if(len + 1 < i)
            ft_argv_strjoin(&str, 2, argv[len], sep);
        else
            ft_unleak_strjoin(&str, argv[len]);
        len++;
    }
    return (str);
}
