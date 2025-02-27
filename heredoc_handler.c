/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makarkao <makarkao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:56:57 by makarkao          #+#    #+#             */
/*   Updated: 2025/02/26 20:57:28 by makarkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*filepath(t_pipex *p)
{
	int		pid;
	char	*filepath;
	char	*piditoa;

	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
		exit((cleanpip(p), 0));
	piditoa = ft_itoa(pid);
	if (!piditoa)
		return (NULL);
	filepath = ft_strjoin("/tmp/pipextmpfile-", piditoa);
	free(piditoa);
	if (!filepath)
		return (NULL);
	return (filepath);
}

char	*ft_nljoin(char *s1)
{
	char	*c;
	int		i;

	i = 0;
	c = malloc(ft_strlen(s1) + 2);
	if (!c)
		return (NULL);
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	c[i++] = '\n';
	c[i] = '\0';
	return (c);
}

void	fill_herefoc(char **av, t_pipex *p)
{
	char	*line;
	char	*fp;

	fp = filepath(p);
	if (!fp)
		exit((cleanpip(p), perror("filepath"), 1));
	p->ll = ft_nljoin(av[2]);
	if (!p->ll)
		exit((cleanpip(p), free(fp), 1));
	p->piphdc[1] = open(fp, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (p->piphdc[1] == -1)
		exit((cleanpip(p), free(fp), perror("p->piphdc[1]"), 1));
	p->piphdc[0] = open(fp, O_RDONLY);
	if (p->piphdc[0] == -1)
		exit((cleanpip(p), free(fp), perror("p->piphdc[0]"), 1));
	(unlink(fp), free(fp));
	line = get_next_line(0, p);
	while (ft_strcmp(line, p->ll) || !line)
	{
		(write(p->piphdc[1], line, ft_strlen(line)), free(line));
		line = get_next_line(0, p);
	}
	if (line)
		free(line);
	close(p->piphdc[1]);
}
