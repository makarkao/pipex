/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:00:25 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/26 18:10:07 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_herdoc(t_pipex *p, int ac, char **av)
{
	if (!ft_strcmp(av[1], "here_doc"))
	{
		p->cmd_c = ac - 4;
		p->herdoc = 1;
	}
	else
	{
		p->cmd_c = ac - 3;
		p->herdoc = 0;
	}
	p->ll = NULL;
}

void	init_cmd_buff(t_pipex *p)
{
	int	i;

	p->cmd_path = malloc(sizeof(char *) * (p->cmd_c + 1));
	if (!p->cmd_path)
		exit((free_pip(p->pipefd, p->cmd_c - 1), free(p->pid), printf("ERROR"),
				1));
	i = 0;
	while (i < p->cmd_c + 1)
	{
		p->cmd_path[i] = NULL;
		i++;
	}
	p->cmd = malloc(sizeof(char **) * (p->cmd_c + 1));
	if (!p->cmd)
		exit((free_pip(p->pipefd, p->cmd_c - 1), free(p->pid),
				ft_freestrs(p->cmd_path), printf("ERROR"), 1));
	i = 0;
	while (i < p->cmd_c + 1)
	{
		p->cmd[i] = NULL;
		i++;
	}
}

void	init_pip(t_pipex *p, int ac, char **av)
{
	int	i;

	i = 0;
	init_herdoc(p, ac, av);
	p->pid = malloc(sizeof(pid_t) * p->cmd_c);
	if (!p->pid)
		exit((printf("ERROR"), 1));
	p->pipefd = malloc(sizeof(int *) * (p->cmd_c - 1));
	if (!p->pipefd)
		exit((free(p->pid), printf("ERROR"), 1));
	i = 0;
	while (i < p->cmd_c - 1)
	{
		p->pipefd[i] = malloc(sizeof(int) * 2);
		if (!p->pipefd[i])
			exit((free_pip(p->pipefd, i), free(p->pid), printf("ERROR"), 1));
		i++;
	}
	init_cmd_buff(p);
}

void	global_init(int ac, char **av, char **ev, t_pipex *p)
{
	int	i;

	init_pip(p, ac, av);
	if (p->herdoc)
		fill_herefoc(av, p);
	i = 0;
	while (i < p->cmd_c - 1)
	{
		if (pipe(p->pipefd[i]) == -1)
			exit((cleanpip(p), perror("pipe"), 1));
		i++;
	}
	cmds_handler(av, ev, p);
}
