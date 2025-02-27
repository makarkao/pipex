/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:37:23 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/24 14:37:24 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	errnov(void)
{
	int	n;

	n = 1;
	if (errno == ENOENT)
		n = 127;
	else if (errno == EACCES)
		n = 126;
	else if (errno == 0)
		n = 0;
	return (n);
}

char	*ft_slashjoin(char *s1, char *s3)
{
	char	*c;
	int		i;
	int		j;

	i = 0;
	c = malloc(ft_strlen(s1) + ft_strlen(s3) + 2);
	if (!c)
		return (NULL);
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	c[i++] = '/';
	j = 0;
	while (s3[j])
	{
		c[i + j] = s3[j];
		j++;
	}
	c[i + j] = '\0';
	return (c);
}

char	*cmds_paths(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (!ft_strncmp(ev[i], "PATH=", 5))
			return (ev[i] + 5);
		i++;
	}
	return (NULL);
}
