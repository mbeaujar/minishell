/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfrom_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeaujar <mbeaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:06:13 by mbeaujar          #+#    #+#             */
/*   Updated: 2021/06/01 20:06:42 by mbeaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strfrom_tab(char **argv, char *sep)
{
	int		len;
	int		i;
	char	*str;
	int		len_g;

	len = 0;
	i = 0;
	str = NULL;
	len_g = ft_strlen_tab(argv);
	while (i < len_g)
		len += ft_strlen(argv[i++]);
	str = malloc(sizeof(char) * (len + i));
	if (!str)
		return (NULL);
	len = 0;
	while (len < i)
	{
		if (len + 1 < i)
			ft_argv_strjoin(&str, 2, argv[len], sep);
		else
			ft_unleak_strjoin(&str, argv[len]);
		len++;
	}
	return (str);
}
