/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_flow_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:59:21 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/26 20:55:11 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_c - 1)
	{
		close(p->pipefd[i][0]);
		close(p->pipefd[i][1]);
		i++;
	}
	if (p->herdoc)
	{
		close(p->piphdc[0]);
		close(p->piphdc[1]);
	}
}

void	first_pipe(t_pipex *p, char **av)
{
	if (p->herdoc)
	{
		if (dup2(p->piphdc[0], 0) == -1)
			exit((cleanpip(p), perror("dup2 herdoc infile"), errnov()));
		if (dup2(p->pipefd[0][1], 1) == -1)
			exit((cleanpip(p), perror("dup2 infile herdoc"), errnov()));
		close_pipes(p);
	}
	else
	{
		p->infilefd = open(av[1], O_RDONLY);
		if (p->infilefd == -1)
			exit((cleanpip(p), perror("open infile"), 1));
		if (dup2(p->infilefd, 0) == -1)
			exit((cleanpip(p), perror("dup2 infile"), errnov()));
		close(p->infilefd);
		if (dup2(p->pipefd[0][1], 1) == -1)
			exit((cleanpip(p), perror("dup2 pipe write end"), errnov()));
		close_pipes(p);
	}
}

void	last_pipe(t_pipex *p, char **av)
{
	if (p->herdoc)
		p->outfilefd = open(av[p->cmd_c + 2 + p->herdoc],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		p->outfilefd = open(av[p->cmd_c + 2 + p->herdoc],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->outfilefd == -1)
		exit((cleanpip(p), perror("open p.outfilefd"), 1));
	if (dup2(p->pipefd[p->cmd_c - 2][0], 0) == -1)
		exit((cleanpip(p), perror("dup2 pipe read end"), errnov()));
	close_pipes(p);
	if (dup2(p->outfilefd, 1) == -1)
		exit((cleanpip(p), perror("dup2 p.outfilefd"), errnov()));
	close(p->outfilefd);
}

void	manage_flow(t_pipex *p, char **av, int i)
{
	if (i == 0)
		first_pipe(p, av);
	else if (i == p->cmd_c - 1)
		last_pipe(p, av);
	else
	{
		if (dup2(p->pipefd[i - 1][0], 0) == -1)
		{
			exit((cleanpip(p), perror("dup2 p.infilefd"), errnov()));
		}
		if (dup2(p->pipefd[i][1], 1) == -1)
		{
			exit((cleanpip(p), perror("dup2 pipe write end"), errnov()));
		}
		close_pipes(p);
	}
}
