/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:38:14 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/25 15:27:38 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	evp_null(char **av, t_pipex *p)
{
	char	*c;
	char	**s;

	int (j), (k);
	(1) && (j = p->herdoc, k = 0);
	while (k < p->cmd_c)
	{
		s = ft_split(av[2 + j], ' ');
		if (!s)
			exit((cleanpip(p), perror("cmds_handler"), errnov()));
		if (ft_chrinstr(s[0], '/'))
		{
			c = ft_strdup(s[0]);
			if (!c)
				exit((cleanpip(p), ft_freestrs(s), perror("cmds_handler"),
						errnov()));
			if (access(c, F_OK | X_OK) == 0)
				(1) && (p->cmd_path[k] = c, p->cmd[k] = s);
			else
				(free(c), ft_freestrs(s));
		}
		else
			ft_freestrs(s);
		(1) && (j++, k++);
	}
}

void	handle_path(char **s2, char **s, t_pipex *p, int k)
{
	char	*c;
	int		i;

	i = 0;
	while (s2[i])
	{
		if (ft_chrinstr(s[0], '/'))
			c = ft_strdup(s[0]);
		else
			c = ft_slashjoin(s2[i], s[0]);
		if (!c)
			exit((cleanpip(p), ft_freestrs(s2), ft_freestrs(s),
					perror("cmds_handler"), errnov()));
		if (access(c, F_OK | X_OK) == 0)
		{
			(1) && (p->cmd_path[k] = c, p->cmd[k] = s);
			return ;
		}
		(free(c), i++);
	}
	ft_freestrs(s);
}

void	evp_exist(char **av, t_pipex *p, char **s2)
{
	char	**s;

	int (j), (k);
	(1) && (j = p->herdoc, k = 0);
	while (k < p->cmd_c)
	{
		s = ft_split(av[2 + j], ' ');
		if (!s)
			exit((cleanpip(p), ft_freestrs(s2), perror("cmds_handler"),
					errnov()));
		if (s[0])
			handle_path(s2, s, p, k);
		else
			ft_freestrs(s);
		(1) && (j++, k++);
	}
}

void	cmds_handler(char **av, char **ev, t_pipex *p)
{
	char	*evp;
	char	**s2;

	evp = cmds_paths(ev);
	if (!evp)
		evp_null(av, p);
	else
	{
		s2 = ft_split(evp, ':');
		if (!s2)
			exit((cleanpip(p), perror("cmds_handler"), errnov()));
		evp_exist(av, p, s2);
		ft_freestrs(s2);
	}
}
