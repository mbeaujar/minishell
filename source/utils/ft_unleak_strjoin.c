#include "minishell.h"

void	ft_unleak_strjoin(char **dst, char *src)
{
	char *tmp;

	if (!*dst)
	{
		*dst = ft_strdup(src);
		return ;
	}
	tmp = ft_strdup(*dst);
	free(*dst);
	*dst = ft_strjoin(tmp, src);
	free(tmp);
}
