/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_clean_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:59:53 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/26 18:10:50 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pip(int **pid, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(pid[i++]);
	free(pid);
}

void	ft_freestrs(char **strs)
{
	int	i;

	i = 0;
	if (strs == NULL)
		return ;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	ft_freepcmds(char **pcmds, int cmd_c)
{
	int	i;

	i = 0;
	while (i < cmd_c)
	{
		if (pcmds[i])
			free(pcmds[i]);
		i++;
	}
	free(pcmds);
}

void	ft_freecmds(char ***cmds, int cmd_c)
{
	int	i;

	i = 0;
	while (i < cmd_c)
	{
		if (cmds[i])
			ft_freestrs(cmds[i]);
		i++;
	}
	free(cmds);
}

void	cleanpip(t_pipex *p)
{
	ft_freecmds(p->cmd, p->cmd_c);
	ft_freepcmds(p->cmd_path, p->cmd_c);
	free(p->pid);
	free_pip(p->pipefd, p->cmd_c - 1);
	if (p->ll)
		free(p->ll);
}
