#include "minishell.h"

void	ft_argv_strjoin(char **dst, int count, ...)
{
	va_list	list;
	int		i;

	i = 0;
	va_start(list, count);
	while (i < count)
	{
		ft_unleak_strjoin(dst, va_arg(list, char *));
		i++;
	}
    va_end(list);
}
