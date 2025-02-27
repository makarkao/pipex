/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:01:31 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/26 21:04:15 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handl_exit(t_pipex *p)
{
	int	status2;
	int	i;

	close_pipes(p);
	status2 = 0;
	i = 0;
	while (i < p->cmd_c - 1)
		waitpid(p->pid[i++], NULL, 0);
	waitpid(p->pid[p->cmd_c - 1], &status2, 0);
	cleanpip(p);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	else
		return (1);
}

int	main(int ac, char **av, char **ev)
{
	t_pipex	p;
	int		i;

	if (ac < 5)
		return (1);
	global_init(ac, av, ev, &p);
	i = 0;
	while (i < p.cmd_c)
	{
		p.pid[i] = fork();
		if (p.pid[i] == -1)
			exit((cleanpip(&p), perror("fork"), 1));
		if (p.pid[i] == 0)
		{
			manage_flow(&p, av, i);
			if (p.cmd_path[i])
				execve(p.cmd_path[i], p.cmd[i], ev);
			exit((cleanpip(&p), perror("execve cmd"), errnov()));
		}
		i++;
	}
	exit(handl_exit(&p));
}
